#ifndef KINECT_BACKGROUND_HPP
#define KINECT_BACKGROUND_HPP

#include <memory>

class Kinect;

class KinectBackground
{
public:
   KinectBackground(const std::shared_ptr<Kinect>& kinect) : mKinect(kinect) { }
   virtual ~KinectBackground() { }

   virtual void SwitchMode() { mDisplayMode = static_cast<BackgroundMode>((mDisplayMode + 1) % BACKGROUND_MODE_ITEM_COUNT); }
   virtual const void* GetImage() = 0;

protected:
   enum BackgroundMode
   {
      None,
      RgbImage,
      DepthImage,
      BACKGROUND_MODE_ITEM_COUNT
   } mDisplayMode = RgbImage;

   std::shared_ptr<Kinect> mKinect;
};

#endif // KINECT_BACKGROUND_HPP
