#ifndef NUI_BACKGROUND_HPP
#define NUI_BACKGROUND_HPP

#include <memory>
#include <vector>

class Nui;
class Size;

class NuiBackground
{
public:
   NuiBackground(const std::shared_ptr<Nui>& kinect);
   ~NuiBackground();

   void SwitchMode();
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

   std::shared_ptr<Nui> mKinect;
   std::vector<char> mDepthBuf;
};

#endif // NUI_BACKGROUND_HPP
