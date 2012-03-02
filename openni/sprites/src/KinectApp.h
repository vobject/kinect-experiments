#ifndef KINENOID_APP_H
#define KINENOID_APP_H

#include "Kinect.h"

#include <memory>
#include <string>
#include <vector>
#include <list>
#include <map>

class ALLEGRO_DISPLAY;
class ALLEGRO_FONT;
class ALLEGRO_EVENT_QUEUE;
class ALLEGRO_TIMER;

class Background;
class KinectPlayer;
class SceneText;

//enum BackgroundMode
//{
//   bm_None,
//   bm_Kinect,
//   bm_Mario,
//   bm_Mario2,
//   BACKGROUND_MODE_COUNT
//};

//enum OverlayMode
//{
//   om_None,
//   om_Stars,
//   om_Planets,
//   om_StarsAndPlanets,
//   OVERLAY_MODE_COUNT
//};

class KinectApp
{
public:
   static const int FRAMES_PER_SECOND = 60;
   static const int WINDOW_WIDTH = 800;
   static const int WINDOW_HEIGHT = 600;

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
   void InitBackground();
   void InitOverlay();

   void ToggleBackgroundMode();
   void ToggleOverlayMode();

   std::string GetFpsMsg() const;

   const std::string mPath;

   bool mMainloopDone;
   int mFpsCount;

//   BackgroundMode mCurrentBackgroundMode;
//   OverlayMode mCurrentOverlayMode;

   ALLEGRO_DISPLAY* mDisplay;
   ALLEGRO_EVENT_QUEUE* mEventQueue;
   ALLEGRO_TIMER* mFpsTimer;
   Kinect mKinect;

   typedef std::vector<Background*> BackgroundVec;
//   typedef std::vector< std::pair<SceneOverlay*, bool> > OverlayVec;

   BackgroundVec mBackgrounds;
   BackgroundVec::iterator mCurrentBackground;

   std::auto_ptr<KinectPlayer> mKinectPlayer;

//   OverlayVec mOverlays;

   std::auto_ptr<SceneText> mFpsText;
//   std::list<SceneObject*> mSceneObjects;

   KinectApp(const KinectApp&);
   KinectApp& operator=(const KinectApp&);
};

#endif // KINENOID_APP_H
