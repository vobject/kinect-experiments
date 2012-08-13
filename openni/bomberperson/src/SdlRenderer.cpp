#include "SdlRenderer.hpp"
#include "Field.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"
#include "Nui.hpp"
#include "Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

SdlRenderer::SdlRenderer(const kinex::Nui& kinect)
{
//   const Size kinect_res = kinect.GetSize();

////   if ((mScreen->w != kinect_res.Width) ||
////       (mScreen->h != kinect_res.Height))
////   {
//      mBgSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
//                                        kinect_res.Width,
//                                        kinect_res.Height,
//                                        24, 0x0000ff, 0x00ff00, 0xff0000, 0);
//      if (!mBgSurface) {
//         throw "SDL_CreateRGBSurface() failed.";
//      }
////   }
//   // mBgSurface will stay nullptr if window and kinect image resolution match.
}

SdlRenderer::~SdlRenderer()
{
//   if (mBgSurface) {
//      SDL_FreeSurface(mBgSurface);
//   }
}

void SdlRenderer::PreRender()
{
   // Screen size might have changed.
   mScreen = SDL_GetVideoSurface();

   const auto black = SDL_MapRGB(mScreen->format, 0x00, 0x00, 0x00);
   SDL_FillRect(mScreen, NULL, black);
}

void SdlRenderer::PostRender()
{
   SDL_Flip(mScreen);
}

void SdlRenderer::Render(const std::shared_ptr<Field>& field)
{
   const Point pos = field->GetPosition();
   const Size size = field->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0xefefef);
}

void SdlRenderer::Render(const std::shared_ptr<Cell>& cell)
{
   const Point pos = cell->GetPosition();
   const Size size = cell->GetSize();
   const CellType type = cell->GetType();

   SDL_Rect rect = { static_cast<Sint16>(pos.X + 1),
                     static_cast<Sint16>(pos.Y + 1),
                     static_cast<Uint16>(size.Width - 2),
                     static_cast<Uint16>(size.Height - 2) };

   int color = 0;
   if (CellType::Floor == type) { color = 0x7f7f00; }
   else if (CellType::IndestructibleWall == type) { color = 0x4f4f4f; }
   else if (CellType::DestructibleWall == type) { color = 0x7f7f7f; }

   SDL_FillRect(mScreen, &rect, color);
}

void SdlRenderer::Render(const std::shared_ptr<Player>& player)
{
   const Point pos = player->GetPosition();
   const Size size = player->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0x00afaf);
}

void SdlRenderer::Render(const std::shared_ptr<Bomb>& bomb)
{
   const Point pos = bomb->GetPosition();
   const Size size = bomb->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0x000000);
}

void SdlRenderer::Render(const std::shared_ptr<Explosion>& explosion)
{
   const Point pos = explosion->GetPosition();
   const Size size = explosion->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0xffff00);
}

void SdlRenderer::Render(const std::shared_ptr<SceneObject>& obj)
{
   const Point pos = obj->GetPosition();
   const Size size = obj->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0xffffff);
}

void SdlRenderer::DrawLine(const Point& src_pos, const Point& dest_pos, const unsigned int color)
{
   // based on http://alawibaba.com/projects/whiteboard/drawing-SDL.c

#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
#define ABS(x) ((x)>0 ? (x) : (-x))

   int x1 = src_pos.X;
   int y1 = src_pos.Y;
   int x2 = dest_pos.X;
   int y2 = dest_pos.Y;

   int lg_delta;
   int sh_delta;
   int cycle;
   int lg_step;
   int sh_step;

   lg_delta = x2 - x1;
   sh_delta = y2 - y1;
   lg_step = SGN(lg_delta);
   lg_delta = ABS(lg_delta);
   sh_step = SGN(sh_delta);
   sh_delta = ABS(sh_delta);

   if (sh_delta < lg_delta)
   {
      cycle = lg_delta >> 1;
      while (x1 != x2)
      {
         DrawPixel({x1, y1}, color);

         cycle += sh_delta;
         if (cycle > lg_delta)
         {
            cycle -= lg_delta;
            y1 += sh_step;
         }
         x1 += lg_step;
      }
      DrawPixel({x1, y1}, color);
   }

   cycle = sh_delta >> 1;
   while (y1 != y2)
   {
      DrawPixel({x1, y1}, color);

      cycle += lg_delta;
      if (cycle > sh_delta)
      {
         cycle -= sh_delta;
         x1 += lg_step;
      }
      y1 += sh_step;
   }
   DrawPixel({x1, y1}, color);
}

void SdlRenderer::DrawPixel(const Point& pos, const unsigned int color)
{
   const auto bpp = mScreen->format->BytesPerPixel;
   const auto offset = (mScreen->pitch * pos.Y) + (pos.X * bpp);

   SDL_LockSurface(mScreen);
   memcpy(static_cast<char*>(mScreen->pixels) + offset, &color, bpp);
   SDL_UnlockSurface(mScreen);
}
