#ifndef KINENOID_APP_H
#define KINENOID_APP_H

//#include "Kinect.h"

#include <string>
#include <vector>
#include <list>

//class SceneObject;

class KinectApp
{
public:
   KinectApp();
   virtual ~KinectApp();

   void PrintCommands() const;
   void Start(const std::string& path);

protected:
   virtual void Initialize(const std::string& path);
   virtual void UpdateScene();
   virtual void RenderScene();
   virtual void Mainloop();

private:
   std::string mPath;
   bool mQuitRequested;

//   ALLEGRO_DISPLAY* mDisplay;
//   ALLEGRO_FONT* mFont18;
//   ALLEGRO_EVENT_QUEUE* mEventQueue;
//   ALLEGRO_TIMER* mFpsTimer;
//   Kinect mKinect;
//
//   std::list<SceneObject*> mSceneObjects;

   KinectApp(const KinectApp&);
   KinectApp& operator=(const KinectApp&);
};

#endif // KINENOID_APP_H
