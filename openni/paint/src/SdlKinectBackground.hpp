#ifndef SDL_KINECT_BACKGROUND_HPP
#define SDL_KINECT_BACKGROUND_HPP

#include "KinectBackground.hpp"
#include "Utils.hpp"

#include <memory>

class Nui;
class SDL_Surface;

class SdlKinectBackground : public KinectBackground
{
public:
   SdlKinectBackground(const std::shared_ptr<Nui>& kinect, const Size& res);
   virtual ~SdlKinectBackground();

   SdlKinectBackground(const SdlKinectBackground&) = delete;
   SdlKinectBackground& operator=(const SdlKinectBackground&) = delete;

   const void* GetImage(Size& img_size) override;

private:
   void SelectRgbImage();
   void SelectDepthImage();
   const SDL_Surface* ZoomSurface();

   const Size mZoomRes;
   SDL_Surface* mSurface = nullptr;
   SDL_Surface* mZoomedSurface = nullptr;
};

#endif // SDL_KINECT_BACKGROUND_HPP
