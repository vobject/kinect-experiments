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

}

void SdlRenderer::Render(const std::shared_ptr<Cell>& cell)
{

}

void SdlRenderer::Render(const std::shared_ptr<Player>& player)
{

}

void SdlRenderer::Render(const std::shared_ptr<Bomb>& bomb)
{

}

void SdlRenderer::Render(const std::shared_ptr<Explosion>& explosion)
{

}

void SdlRenderer::Render(const std::shared_ptr<SceneObject>& obj)
{

}

//void SdlRenderer::Render(const std::shared_ptr<Match>& level)
//{
//   const Point level_pos = level->GetPosition();
//   const Size level_size = level->GetSize();
//
//   SDL_Rect level_rect = { level_pos.X, level_pos.Y,
//                           level_size.Width, level_size.Height};
//   SDL_FillRect(mScreen, &level_rect, 0xefefef);
//
//   Point cell_pos(level_pos);
//   for (const auto& row : level->mField->mCells)
//   {
//      for (const auto& cell : row)
//      {
//         SDL_Rect cell_rect = { cell_pos.X + 1,
//                                cell_pos.Y + 1,
//                                level->GetCellWidth() - 2,
//                                level->GetCellHeight() - 2};
//
//         int cell_color = 0;
//         if (CellType::Floor == cell->GetType()) { cell_color = 0x7f7f00; }
//         else if (CellType::IndestructibleWall == cell->GetType()) { cell_color = 0x4f4f4f; }
//         else if (CellType::DestructibleWall == cell->GetType()) { cell_color = 0x7f7f7f; }
//
//         SDL_FillRect(mScreen, &cell_rect, cell_color);
//
//         cell_pos.X += level->GetCellWidth();
//      }
//
//      cell_pos.X = level_pos.X; // carriage return
//      cell_pos.Y += level->GetCellHeight(); // line feed
//   }
//
//   for (const auto& player : level->mPlayers)
//   {
//      SDL_Rect player_rect = { level_pos.X + player->GetPosition().X,
//                               level_pos.Y + player->GetPosition().Y,
//                               player->GetSize().Width,
//                               player->GetSize().Height};
//      SDL_FillRect(mScreen, &player_rect, 0x00afaf);
//   }
//
//   for (const auto& bomb : level->mBombs)
//   {
//      SDL_Rect bomb_rect = { level_pos.X + bomb->GetPosition().X,
//                             level_pos.Y + bomb->GetPosition().Y,
//                             bomb->GetSize().Width,
//                             bomb->GetSize().Height};
//      SDL_FillRect(mScreen, &bomb_rect, 0x000000);
//   }
//
//   for (const auto& explosion : level->mExplosions)
//   {
//      SDL_Rect explosion_rect = { level_pos.X + explosion->GetPosition().X,
//                                  level_pos.Y + explosion->GetPosition().Y,
//                                  explosion->GetSize().Width,
//                                  explosion->GetSize().Height};
//      SDL_FillRect(mScreen, &explosion_rect, 0xffff00);
//   }
//}

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
