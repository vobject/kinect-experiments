#include "SdlRenderer.hpp"
#include "KinectBackground.hpp"
#include "PaintApp.hpp"
#include "Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

SdlRenderer::SdlRenderer()
   : mScreen(SDL_GetVideoSurface())
{
//   // This is the surface that we will write to before swapping it.
//   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
//                                   mScreen->w, mScreen->h,
//                                   mScreen->format->BitsPerPixel,
//                                   0, 0, 0, 0);
//   if (!mSurface) {
//      throw "SDL_CreateRGBSurface() failed.";
//   }
}

SdlRenderer::~SdlRenderer()
{
//   SDL_FreeSurface(mSurface);
}

void SdlRenderer::PreRender()
{
   const auto black = SDL_MapRGB(mScreen->format, 0x00, 0x00, 0x00);
   SDL_FillRect(mScreen, NULL, black);
}

void SdlRenderer::PostRender()
{
//   SDL_BlitSurface(mSurface, NULL, mScreen, NULL);
   SDL_Flip(mScreen);
}

void SdlRenderer::Render(const std::shared_ptr<KinectBackground>& bg)
{
   Size img_size = {0, 0};
   auto img = bg->GetImage(img_size);

   SDL_LockSurface(mScreen);
   // TODO: Zoom original image which is always kinect-sized (640x480)
   memcpy(mScreen->pixels, img, img_size.Width * img_size.Height);
   SDL_UnlockSurface(mScreen);

//   SDL_LockSurface(mSurface);
//   // I will probably go to hell for doing this...
//   Size tmp_surface_size = {mSurface->w, mSurface->h};
//   const auto tmp_surface_data = mSurface->pixels;
//
//   // ...yeah, probably into the third or sixth circle.
//   mSurface->w = img_size.Width;
//   mSurface->h = img_size.Height;
//   mSurface->pixels = const_cast<void*>(img);
//   SDL_UnlockSurface(mSurface); // Blit should not be called on a locked surface.
//
//   SDL_Rect rect = { static_cast<Sint16>(0),
//                     static_cast<Sint16>(0),
//                     static_cast<Uint16>(mSurface->w),
//                     static_cast<Uint16>(mSurface->h) };
//
//   SDL_BlitSurface(mSurface, NULL, mScreen, &rect);
//
//   SDL_LockSurface(mSurface);
//   // And now reverse the madness...
//   mSurface->w = tmp_surface_size.Width;
//   mSurface->h = tmp_surface_size.Height;
//   mSurface->pixels = tmp_surface_data;
//   SDL_UnlockSurface(mSurface);
}

void SdlRenderer::Render(const std::shared_ptr<PaintStatus>& status)
{
   constexpr auto line_color = 0xffff00ff;
   constexpr auto rect_color = 0xffffffff;
   constexpr auto rect_size = 6_px;

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
   const size_t bpp = mScreen->format->BytesPerPixel;
   const size_t offset = (mScreen->pitch * pos.Y) + (pos.X * bpp);

   SDL_LockSurface(mScreen);
   memcpy(static_cast<char*>(mScreen->pixels) + offset, &color, bpp);
   SDL_UnlockSurface(mScreen);
}
