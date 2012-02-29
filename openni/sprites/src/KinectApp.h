#ifndef KINENOID_APP_H
#define KINENOID_APP_H

#include "Kinect.h"

#include <string>
#include <vector>
#include <list>

class ALLEGRO_DISPLAY;
class ALLEGRO_FONT;
class ALLEGRO_EVENT_QUEUE;
class ALLEGRO_TIMER;

class SceneObject;

class KinectApp
{
public:
   explicit KinectApp(const std::string& path);
   virtual ~KinectApp();

   void PrintCommands() const;
   void Start();

protected:
   virtual void Setup();
   virtual void UpdateScene();
   virtual void RenderScene();
   virtual void Mainloop();

private:
   const std::string mPath;

   bool mMainloopDone;

   ALLEGRO_DISPLAY* mDisplay;
   ALLEGRO_FONT* mFont18;
   ALLEGRO_EVENT_QUEUE* mEventQueue;
   ALLEGRO_TIMER* mFpsTimer;
   Kinect mKinect;

   std::list<SceneObject*> mSceneObjects;

   KinectApp(const KinectApp&);
   KinectApp& operator=(const KinectApp&);
};

#endif // KINENOID_APP_H
