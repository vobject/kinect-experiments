#include "KinectApp.h"
#include "Log.h"
#include "Kinect.h"

#include "EmptyBackground.h"
#include "BitmapBackground.h"
#include "KinectBackground.h"

#include "SceneOverlay.h"
#include "SceneText.h"
//#include "BloodAnimation.h"

#include <allegro5/allegro.h>

#include <iostream>
#include <sstream>

KinectApp::KinectApp(const std::string& path)
   : mPath(path)
   , mMainloopDone(false)
   , mFpsCount(0)
   , mCurrentBackgroundMode(bm_Kinect)
   , mCurrentOverlayMode(om_None)
   , mDisplay(NULL)
   , mEventQueue(NULL)
   , mFpsTimer(NULL)
   , mFpsText(NULL)
{
   Log::ReportingLevel() = logDEBUG;
}

KinectApp::~KinectApp()
{
   for (BackgroundVec::const_iterator iter = mBackgrounds.begin();
        iter != mBackgrounds.end();
        iter++)
   {
      delete iter->first;
   }

   for (OverlayVec::const_iterator iter = mOverlays.begin();
        iter != mOverlays.end();
        iter++)
   {
      delete iter->first;
   }

//   for(std::list<SceneObject*>::const_iterator it = mSceneObjects.begin();
//       it != mSceneObjects.end();
//       it++)
//   {
//      delete *it;
//   }

   al_destroy_timer(mFpsTimer);
   al_destroy_event_queue(mEventQueue);
   al_destroy_display(mDisplay);
}

void KinectApp::PrintCommands() const
{
   std::cout << "Commands:\n"
//             << "\tm - Toggle image/depth mode\n"
//             << "\tf - Seek 100 frames forward\n"
//             << "\tb - Seek 100 frames backward\n"
//             << "\ti - Increase depth by 20cm\n"
//             << "\to - Decrease depth by 20cm\n"
//             << "\tu - Toggle user tracking mode\n"
//             << "\td - Toggle debug overlay mode\n"
//             << "\th - Print this help message\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

void KinectApp::Start()
{
   Setup();

   InitBackground();
   InitOverlay();
   mFpsText.reset(new SceneText(5, 5, 20));
//   mSceneObjects.push_back(new KinectBackground(mKinect));
//   mSceneObjects.push_back(new BloodAnimation(100, 100, al_current_time() + 3.0));
   Mainloop();
}

void KinectApp::Setup()
{
   mKinect.Init();

   if(!al_init()) {
      throw "Failed to initialize allegro";
   }

   mDisplay = al_create_display(mKinect.GetXRes(), mKinect.GetYRes());
   if (NULL == mDisplay) {
      throw "Failed to create an allegro display";
   }
   al_set_window_title(mDisplay, "sprite - kinect-experiments");

   al_install_keyboard();
   mFpsTimer = al_create_timer(1.0 / FRAMES_PER_SECOND);
   mEventQueue = al_create_event_queue();

   al_register_event_source(mEventQueue, al_get_display_event_source(mDisplay));
   al_register_event_source(mEventQueue, al_get_keyboard_event_source());
   al_register_event_source(mEventQueue, al_get_timer_event_source(mFpsTimer));
}

void KinectApp::UpdateScene()
{
   for (BackgroundVec::const_iterator iter = mBackgrounds.begin();
        iter != mBackgrounds.end();
        iter++)
   {
      if (iter->second) {
         iter->first->Update();
      }
   }

   for (OverlayVec::const_iterator iter = mOverlays.begin();
        iter != mOverlays.end();
        iter++)
   {
      if (iter->second) {
         iter->first->Update();
      }
   }
}

void KinectApp::RenderScene()
{
   al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));

   for (BackgroundVec::const_iterator iter = mBackgrounds.begin();
        iter != mBackgrounds.end();
        iter++)
   {
      if (iter->second) {
         iter->first->Render();
      }
   }

   for (OverlayVec::const_iterator iter = mOverlays.begin();
        iter != mOverlays.end();
        iter++)
   {
      if (iter->second) {
         iter->first->Render();
      }
   }

   mFpsText->SetText(GetFpsMsg());
   mFpsText->Render();

   al_flip_display();
}

void KinectApp::Mainloop()
{
   al_start_timer(mFpsTimer);

   float gameTime = al_current_time();
   int frames = 0;
   bool render = false;
   ALLEGRO_EVENT ev;

   while(!mMainloopDone)
   {
      if (render && al_is_event_queue_empty(mEventQueue))
      {
         RenderScene();
         render = false;
      }

      al_wait_for_event(mEventQueue, &ev);

      if (ALLEGRO_EVENT_TIMER == ev.type)
      {
         frames++;

         if(al_current_time() - gameTime >= 1)
         {
            gameTime = al_current_time();
            mFpsCount = frames;
            frames = 0;
         }

         UpdateScene();
         render = true;
      }
      else if (ALLEGRO_EVENT_KEY_DOWN == ev.type)
      {
         switch(ev.keyboard.keycode)
         {
         case ALLEGRO_KEY_ESCAPE:
            mMainloopDone = true;
            break;
         case ALLEGRO_KEY_B:
            ToggleBackgroundMode();
            break;
         case ALLEGRO_KEY_O:
            ToggleOverlayMode();
            break;
         }
      }
      else if (ALLEGRO_EVENT_DISPLAY_CLOSE == ev.type)
      {
         mMainloopDone = true;
      }
   }

   al_stop_timer(mFpsTimer);
}

std::string KinectApp::GetFpsMsg() const
{
   std::stringstream os;
   os << "FPS: " << mFpsCount;
   return os.str();
}

void KinectApp::InitBackground()
{
   mBackgrounds.push_back(std::make_pair(new EmptyBackground(), false));
   mBackgrounds.push_back(std::make_pair(new KinectBackground(mKinect), true));
   mBackgrounds.push_back(std::make_pair(new BitmapBackground("/home/pzy/Downloads/smw.jpg"), false));
   mBackgrounds.push_back(std::make_pair(new BitmapBackground("/home/pzy/Downloads/Super-Mario-World-Wallpaper.png"), false));
}

void KinectApp::InitOverlay()
{
   mOverlays.push_back(std::make_pair(
         new SceneOverlay("/home/pzy/Downloads/starBG.png", SceneOverlay::None, 2),
      false));

   mOverlays.push_back(std::make_pair(
         new SceneOverlay("/home/pzy/Downloads/starMG.png", SceneOverlay::None, 6),
      false));
}

void KinectApp::ToggleBackgroundMode()
{
   // HACK

   for (BackgroundVec::iterator iter = mBackgrounds.begin();
        iter != mBackgrounds.end();
        iter++)
   {
      iter->second = false;
   }

   mCurrentBackgroundMode = (BackgroundMode)((mCurrentBackgroundMode + 1) % BACKGROUND_MODE_COUNT);
   mBackgrounds[mCurrentBackgroundMode].second = true;
}

void KinectApp::ToggleOverlayMode()
{
   // HACK

   mCurrentOverlayMode = (OverlayMode)((mCurrentOverlayMode + 1) % OVERLAY_MODE_COUNT);

   switch (mCurrentOverlayMode)
   {
      case om_None:
      {
         for (OverlayVec::iterator iter = mOverlays.begin();
              iter != mOverlays.end();
              iter++)
         {
            iter->second = false;
         }
      }
      break;

      case om_Stars:
      {
         mOverlays[0].second = true;
         mOverlays[1].second = false;
      }
      break;

      case om_Planets:
      {
         mOverlays[0].second = false;
         mOverlays[1].second = true;
      }
      break;

      case om_StarsAndPlanets:
      {
         mOverlays[0].second = true;
         mOverlays[1].second = true;
      }
      break;

      default:
         break;
   }
}
