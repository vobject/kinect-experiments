#include "KinectApp.h"
#include "Log.h"
//#include "Kinect.h"
//#include "KinectBackground.h"
//#include "BloodAnimation.h"

#include <iostream>

KinectApp::KinectApp()
//   : mDisplay(NULL)
//   , mFont18(NULL)
//   , mEventQueue(NULL)
//   , mFpsTimer(NULL)
//   , mMainloopDone(false)
   : mQuitRequested(false)
{
   Log::ReportingLevel() = logDEBUG;
}

KinectApp::~KinectApp()
{
//   for(std::list<SceneObject*>::const_iterator it = mSceneObjects.begin();
//       it != mSceneObjects.end();
//       it++)
//   {
//      delete *it;
//   }
//
//   al_destroy_timer(mFpsTimer);
//   al_destroy_event_queue(mEventQueue);
//   al_destroy_font(mFont18);
//   al_destroy_display(mDisplay);
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

void KinectApp::Start(const std::string& path)
{
   Initialize(path);

//   mSceneObjects.push_back(new KinectBackground(mKinect));
//   mSceneObjects.push_back(new BloodAnimation(100, 100, al_current_time() + 3.0));
   Mainloop();
}

void KinectApp::Initialize(const std::string& path)
{
   mPath = path;
//   mKinect.Init();
//
//   if(!al_init()) {
//      throw "Failed to initialize allegro";
//   }
//
//   al_init_font_addon();
//   al_init_ttf_addon();
//   al_init_image_addon();
//
//   mDisplay = al_create_display(mKinect.GetXRes(), mKinect.GetYRes());
//   if (NULL == mDisplay) {
//      throw "Failed to create an allegro display";
//   }
//   al_set_window_title(mDisplay, "sprite - kinect-experiments");
//
//   mFont18 = al_load_font("VeraMono.ttf", 18, 0);
//   if (NULL == mFont18) {
//      throw "Failed to load VeraMono.ttf font";
//   }
//
//   al_install_keyboard();
//   mFpsTimer = al_create_timer(1.0 / 60);
//   mEventQueue = al_create_event_queue();
//
//   al_register_event_source(mEventQueue, al_get_display_event_source(mDisplay));
//   al_register_event_source(mEventQueue, al_get_keyboard_event_source());
//   al_register_event_source(mEventQueue, al_get_timer_event_source(mFpsTimer));
}

void KinectApp::UpdateScene()
{
//   for(std::list<SceneObject*>::iterator it = mSceneObjects.begin();
//       it != mSceneObjects.end();)
//   {
//      if ((*it)->IsDone())
//      {
//         delete *it;
//         it = mSceneObjects.erase(it);
//      }
//      else
//      {
//         it++;
//      }
//   }
//
//   for(std::list<SceneObject*>::const_iterator it = mSceneObjects.begin();
//       it != mSceneObjects.end();
//       it++)
//   {
//      (*it)->Update();
//   }
}

void KinectApp::RenderScene()
{
//   for(std::list<SceneObject*>::const_iterator it = mSceneObjects.begin();
//       it != mSceneObjects.end();
//       it++)
//   {
//      (*it)->Render();
//   }
//
//   al_flip_display();
}

void KinectApp::Mainloop()
{
//   al_start_timer(mFpsTimer);
//
//   float gameTime = al_current_time();
//   int frames = 0;
//   int gameFPS = 0;
//   bool render = false;
//   ALLEGRO_EVENT ev;
//
//   while(!mQuitRequested)
//   {
//      if (render && al_is_event_queue_empty(mEventQueue))
//      {
//         RenderScene();
//         render = false;
//      }
//
//      al_wait_for_event(mEventQueue, &ev);
//
//      if (ALLEGRO_EVENT_TIMER == ev.type)
//      {
//         frames++;
//
//         if(al_current_time() - gameTime >= 1)
//         {
//            gameTime = al_current_time();
//            gameFPS = frames;
//            frames = 0;
//         }
//
//         UpdateScene();
//         render = true;
//      }
//      else if (ALLEGRO_EVENT_KEY_DOWN == ev.type)
//      {
//         switch(ev.keyboard.keycode)
//         {
//         case ALLEGRO_KEY_ESCAPE:
//            mQuitRequested = true;
//            break;
//         }
//      }
//      else if (ALLEGRO_EVENT_DISPLAY_CLOSE == ev.type)
//      {
//         mQuitRequested = true;
//      }
//   }
//
//   al_stop_timer(mFpsTimer);
}
