#ifndef KINENOID_APP_H
#define KINENOID_APP_H

#include <memory>
#include <string>
#include <vector>
#include <list>

class Kinect;
class ResourceCache;
class SdlWindow;
class Renderer;
class Logic;

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

   virtual void UpdateScene(int game_time, int elapsed_time);
   virtual void RenderScene();

private:
   std::string mPath;
   bool mQuitRequested;

   std::shared_ptr<Kinect> mKinect;

   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<SdlWindow> mWindow;
   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<Logic> mLogic;
//   std::shared_ptr<EventManager> mEventManager;

//   ALLEGRO_DISPLAY* mDisplay;
//   ALLEGRO_FONT* mFont18;
//   ALLEGRO_EVENT_QUEUE* mEventQueue;
//   ALLEGRO_TIMER* mFpsTimer;
//   Kinect mKinect;
};

#endif // KINENOID_APP_H
