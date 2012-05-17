#ifndef NUI_BACKGROUND_HPP
#define NUI_BACKGROUND_HPP

#include <memory>
#include <vector>

namespace kinex {
   class Nui;
}
class Size;

class NuiBackground
{
public:
   NuiBackground(const std::shared_ptr<kinex::Nui>& kinect);
   ~NuiBackground();

   void SwitchMode();

   // Returns a 24Bit image.
   const void* GetImage(Size& img_size);

private:
   void SelectDepthImage();

   enum BackgroundMode
   {
      None,
      RgbImage,
      DepthImage,
      BACKGROUND_MODE_ITEM_COUNT
   } mDisplayMode = RgbImage;

   std::shared_ptr<kinex::Nui> mKinect;
   std::vector<unsigned char> mDepthBuf;
   std::vector<unsigned char> mEmptyBuf;
};

#endif // NUI_BACKGROUND_HPP
