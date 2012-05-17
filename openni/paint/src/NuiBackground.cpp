#include "NuiBackground.hpp"
#include "Nui.hpp"
#include "Utils.hpp"

NuiBackground::NuiBackground(const std::shared_ptr<kinex::Nui>& kinect)
   : mKinect(kinect)
   , mDepthBuf(mKinect->GetSize().Width *
               mKinect->GetSize().Height *
               sizeof(XnRGB24Pixel))
   , mEmptyBuf(mKinect->GetSize().Width *
               mKinect->GetSize().Height *
               sizeof(XnRGB24Pixel))
{
   std::fill(mEmptyBuf.begin(), mEmptyBuf.end(), 128);
}

NuiBackground::~NuiBackground()
{

}

void NuiBackground::SwitchMode()
{
   mDisplayMode = static_cast<BackgroundMode>((mDisplayMode + 1) % BACKGROUND_MODE_ITEM_COUNT);
}

const void* NuiBackground::GetImage(Size& img_size)
{
   // Always the same...
   img_size = mKinect->GetSize();

   switch (mDisplayMode)
   {
      case BackgroundMode::None:
         {
            return mEmptyBuf.data();
         }
      case BackgroundMode::RgbImage:
         {
            return mKinect->GetImageData();
         }
      case BackgroundMode::DepthImage:
         {
            SelectDepthImage();
            return mDepthBuf.data();
         }
   }

   throw "Unknown background mode requested.";
}

void NuiBackground::SelectDepthImage()
{
   constexpr auto bpp = sizeof(XnRGB24Pixel); // Bytes per pixel
   const auto pixel_cnt = mKinect->GetSize().Width * mKinect->GetSize().Height;

   auto label_buf = mKinect->GetDepthData();

   constexpr int MAX_COLORS = 255;
   constexpr int MAX_DEPTH = 3000_mm; // == 3 meters
   constexpr int MAX_ZONES = (MAX_DEPTH / MAX_COLORS) + 1; // number of nuances

   for (auto i = 0; i < pixel_cnt; i++, label_buf++)
   {
      if ((0 == *label_buf) || (MAX_DEPTH < *label_buf))
      {
         // Everything beyond maximum chosen depth is black.
         mDepthBuf[i * bpp]     = 0;
         mDepthBuf[i * bpp + 1] = 0;
         mDepthBuf[i * bpp + 2] = 0;
      }
      else
      {
         mDepthBuf[i * bpp]     = 0;
         mDepthBuf[i * bpp + 1] = MAX_COLORS - *label_buf / MAX_ZONES;
         mDepthBuf[i * bpp + 2] = 0;
      }
   }
}
