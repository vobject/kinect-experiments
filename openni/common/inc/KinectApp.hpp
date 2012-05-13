#ifndef KINECT_APP_HPP
#define KINECT_APP_HPP

#include <memory>
#include <string>

class Nui;
class Size;

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

   virtual void InitSdlVideo(const Size& res);
   virtual void InitGlVideo(const Size& res);
   virtual void InitKinect(const std::string& path);

   bool mQuitRequested = false;
   std::shared_ptr<Nui> mKinect;
};

#endif // KINECT_APP_HPP
