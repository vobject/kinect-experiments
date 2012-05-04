#ifndef KINECT_BACKGROUND_HPP
#define KINECT_BACKGROUND_HPP

#include "Utils.hpp"

#include <memory>

class Kinect;

class SDL_Surface;

class KinectBackground
{
public:
   KinectBackground(const std::shared_ptr<Kinect>& kinect, const Size& res);
   ~KinectBackground();

   KinectBackground(const KinectBackground&) = delete;
   KinectBackground& operator=(const KinectBackground&) = delete;

   void SwitchMode();
   SDL_Surface* GetImage();

private:
   enum BackgroundMode
   {
      None,
      RgbImage,
      DepthImage,
      BACKGROUND_MODE_ITEM_COUNT
   } mDisplayMode = RgbImage;

   void SelectRgbImage();
   void SelectDepthImage();
   SDL_Surface* ZoomSurface();

   std::shared_ptr<Kinect> mKinect;
   const Size mZoomRes;
   SDL_Surface* mSurface = nullptr;
   SDL_Surface* mZoomedSurface = nullptr;
};

#endif // KINECT_BACKGROUND_HPP
