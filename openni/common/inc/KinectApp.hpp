#ifndef KINECT_APP_HPP
#define KINECT_APP_HPP

#include "Utils.hpp"

#include <memory>
#include <string>

namespace kinex {

class Nui;

class KinectApp
{
public:
   KinectApp();
   virtual ~KinectApp();

   void Start();

protected:
   virtual void Initialize() = 0;
   virtual void UpdateScene(int app_time, int elapsed_time) = 0;
   virtual void RenderScene() = 0;

   virtual void Mainloop();

   virtual void InitKinect(const std::string& path);
   virtual void InitVideo();

   enum class VideoMode
   {
      Software,
      OpenGL
   } mCurrentVideoMode = VideoMode::OpenGL;
   Size mCurrentResolution = {640_px, 480_px};

   bool mQuitRequested = false;
   std::shared_ptr<Nui> mKinect;

private:
   void SelectSdlVideo();
   void SelectGlVideo();
};

} // namespace kinex

#endif // KINECT_APP_HPP
