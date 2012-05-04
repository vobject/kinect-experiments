#ifndef KINENOID_APP_HPP
#define KINENOID_APP_HPP

#include <memory>
#include <string>
#include <vector>
#include <list>

class Kinect;
class KinectBackground;
class SdlWindow;
class Point;

struct Status
{
   bool drawing = false;
   std::vector<std::vector<Point>> lines;
   std::vector<Point> active_line;
};

class KinectApp
{
public:
   KinectApp();
   virtual ~KinectApp();

   KinectApp(const KinectApp&) = delete;
   KinectApp& operator=(const KinectApp&) = delete;

   void Start(const std::string& path);

protected:
   virtual void Initialize(const std::string& path);
   virtual void Mainloop();

   virtual void UpdateScene(int app_time, int elapsed_time);
   virtual void RenderScene();

   void ProcessInput();
   void ProcessKinectInput();

private:
   bool mQuitRequested = false;
   bool mKinectConnected = false;
   std::shared_ptr<Kinect> mKinect;
   std::shared_ptr<KinectBackground> mKinectBackground;
   std::shared_ptr<SdlWindow> mWindow;
   Status mState;
};

#endif // KINENOID_APP_HPP
