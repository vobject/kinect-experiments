#include "SdlKinectBackground.hpp"
#include "Nui.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

SdlKinectBackground::SdlKinectBackground(
   const std::shared_ptr<Nui>& kinect,
   const Size& res
)
   : KinectBackground(kinect)
   , mZoomRes(res)
{
   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   mKinect->GetSize().Width,
                                   mKinect->GetSize().Height,
                                   32,
                                   0, 0, 0, 0);
   if (!mSurface) {
      throw "Unable to create KinectBackground because SDL_CreateRGBSurface() failed.";
   }
}

SdlKinectBackground::~SdlKinectBackground()
{
   if (mZoomedSurface) {
      SDL_FreeSurface(mZoomedSurface);
   }
   SDL_FreeSurface(mSurface);
}

const void* SdlKinectBackground::GetImage(Size& img_size)
{
   // TODO
   img_size = mKinect->GetSize();

   switch (mDisplayMode)
   {
      case BackgroundMode::None:
         SDL_FillRect(mSurface, NULL, SDL_MapRGB(mSurface->format, 0, 0, 0));
         break;
      case BackgroundMode::RgbImage:
         SelectRgbImage();
         break;
      case BackgroundMode::DepthImage:
         SelectDepthImage();
         break;
   }
   return ZoomSurface();
}

void SdlKinectBackground::SelectRgbImage()
{
   const auto bpp = mSurface->format->BytesPerPixel;
   const auto pixel_cnt = mSurface->w * mSurface->h;

   SDL_LockSurface(mSurface);
   auto surface_buf = static_cast<char*>(mSurface->pixels);
   auto rgb_buf = mKinect->GetImageData();

   for (auto i = 0; i < pixel_cnt; i++, rgb_buf++)
   {
       surface_buf[i * bpp]     = rgb_buf->nBlue;
       surface_buf[i * bpp + 1] = rgb_buf->nGreen;
       surface_buf[i * bpp + 2] = rgb_buf->nRed;
       surface_buf[i * bpp + 3] = 0;
   }
   SDL_UnlockSurface(mSurface);
}

void SdlKinectBackground::SelectDepthImage()
{
   const int bpp = mSurface->format->BytesPerPixel;
   const int pixel_cnt = mSurface->w * mSurface->h;

   SDL_LockSurface(mSurface);
   auto surface_buf = static_cast<char*>(mSurface->pixels);
   auto depth_buf = mKinect->GetDepthData();

   const int MAX_COLORS = 255;
   const int MAX_DEPTH = 3000_mm; // == 3 meters
   const int MAX_ZONES = (MAX_DEPTH / MAX_COLORS) + 1; // number of nuances

   for (auto i = 0; i < pixel_cnt; i++, depth_buf++)
   {
      if ((0 == *depth_buf) || (MAX_DEPTH < *depth_buf))
      {
         // Everything beyond maximum chosen depth is black.
         surface_buf[i * bpp]     = 0;
         surface_buf[i * bpp + 1] = 0;
         surface_buf[i * bpp + 2] = 0;
         surface_buf[i * bpp + 3] = 0;
      }
      else
      {
         surface_buf[i * bpp]     = 0;
         surface_buf[i * bpp + 1] = MAX_COLORS - *depth_buf / MAX_ZONES;
         surface_buf[i * bpp + 2] = 0;
         surface_buf[i * bpp + 3] = 0;
      }
   }
   SDL_UnlockSurface(mSurface);
}

const SDL_Surface* SdlKinectBackground::ZoomSurface()
{
   if ((mSurface->w == mZoomRes.Width) &&
       (mSurface->h == mZoomRes.Height))
   {
      // Do not try to zoom if we already got the right resolution.
      return mSurface;
   }

   if (mZoomedSurface) {
      // Stupid zoomSurface allocates a new surface for every call.
      SDL_FreeSurface(mZoomedSurface);
   }

   const double zoom_x = static_cast<double>(mZoomRes.Width) / mSurface->w;
   const double zoom_y = static_cast<double>(mZoomRes.Height) / mSurface->h;
   mZoomedSurface = zoomSurface(mSurface, zoom_x, zoom_y, 0);
   return mZoomedSurface;
}
