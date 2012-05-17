#include "SdlRenderer.hpp"
#include "Nui.hpp"
#include "NuiBackground.hpp"
#include "PaintApp.hpp"
#include "Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

SdlRenderer::SdlRenderer(const Nui& kinect)
{
   const Size kinect_res = kinect.GetSize();

//   if ((mScreen->w != kinect_res.Width) ||
//       (mScreen->h != kinect_res.Height))
//   {
      mBgSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                        kinect_res.Width,
                                        kinect_res.Height,
                                        24, 0x0000ff, 0x00ff00, 0xff0000, 0);
      if (!mBgSurface) {
         throw "SDL_CreateRGBSurface() failed.";
      }
//   }
   // mBgSurface will stay nullptr if window and kinect image resolution match.
}

SdlRenderer::~SdlRenderer()
{
   if (mBgSurface) {
      SDL_FreeSurface(mBgSurface);
   }
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

void SdlRenderer::Render(const std::shared_ptr<NuiBackground>& bg)
{
   Size img_size = {0, 0};
   auto img = bg->GetImage(img_size);

//   if ((mScreen->w == img_size.Width) && (mScreen->h == img_size.Height))
//   {
//      // The window has the same resolution as the camera image from Kinect.
//      SDL_LockSurface(mScreen);
//      memcpy(mScreen->pixels, img, img_size.Width * img_size.Height);
//      SDL_UnlockSurface(mScreen);
//   }
//   else
//   {
      // Window and Kinect resolution differ - we have to scale the image -> slow!

      SDL_LockSurface(mBgSurface);
      memcpy(mBgSurface->pixels, img, img_size.Width * img_size.Height * 3);
      SDL_UnlockSurface(mBgSurface);

      const double x_zoom = static_cast<double>(mScreen->w) / mBgSurface->w;
      const double y_zoom = static_cast<double>(mScreen->h) / mBgSurface->h;
      SDL_Surface* zoomed_img = zoomSurface(mBgSurface, x_zoom, y_zoom, 1);

      SDL_Rect rect = { 0,
                        0,
                        static_cast<Uint16>(mScreen->w),
                        static_cast<Uint16>(mScreen->h) };

      SDL_BlitSurface(zoomed_img, NULL, mScreen, &rect);
      SDL_FreeSurface(zoomed_img);
//   }
}

void SdlRenderer::Render(const std::shared_ptr<PaintStatus>& status)
{
   constexpr auto line_color = 0xffffff00;
   constexpr auto rect_color = 0xffffffff;
   constexpr auto rect_size = 8_px;

   // Redraw the previous drawings.
   for (const auto& line : status->lines)
   {
      if (line.empty()) {
         continue;
      }

      Point src_pos = line.at(0);
      for (const auto& dest_pos : line)
      {
         DrawLine(src_pos, dest_pos, line_color);
         src_pos = dest_pos;
      }
   }

   // Show the currently active drawing.
   for (const auto& pos : status->active_line)
   {
      SDL_Rect rect = { static_cast<Sint16>(pos.X - (rect_size / 2)),
                        static_cast<Sint16>(pos.Y - (rect_size / 2)),
                        static_cast<Uint16>(rect_size),
                        static_cast<Uint16>(rect_size) };

      SDL_FillRect(mScreen, &rect, rect_color);
   }
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
