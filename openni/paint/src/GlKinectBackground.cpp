#include "GlKinectBackground.hpp"
#include "Nui.hpp"
#include "Utils.hpp"

GlKinectBackground::GlKinectBackground(const std::shared_ptr<Nui>& kinect)
   : KinectBackground(kinect)
   , mDepthBuf(mKinect->GetSize().Width *
               mKinect->GetSize().Height *
               sizeof(XnRGB24Pixel))
{

}

GlKinectBackground::~GlKinectBackground()
{

}

const void* GlKinectBackground::GetImage(Size& img_size)
{
   // Always the same...
   img_size = mKinect->GetSize();

   switch (mDisplayMode)
   {
      case BackgroundMode::None:
         {
            // HACK: Use the depth buffer as 'empty background' buffer -> slow!
            std::fill(mDepthBuf.begin(), mDepthBuf.end(), 0);
            return mDepthBuf.data();
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

void GlKinectBackground::SelectDepthImage()
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
