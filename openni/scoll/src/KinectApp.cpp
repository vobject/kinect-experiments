#include "KinectApp.h"
#include "Renderer.h"
#include "Logic.h"
#include "Log.h"

#include <SDL.h>

#include <iostream>

KinectApp::KinectApp()
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
   Mainloop();
}

void KinectApp::Initialize(const std::string& path)
{
   mPath = path;
   mRenderer.reset(new Renderer());
   mLogic.reset(new Logic(mRenderer));
}

void KinectApp::UpdateScene(const int game_time, const int elapsed_time)
{
   SDL_Event ev;

   if (SDL_PollEvent(&ev))
   {
      if((SDL_QUIT == ev.type) || (SDLK_ESCAPE == ev.key.keysym.sym))
      {
         // Quit if the user closed the window or pressed ESC.
         mQuitRequested = true;
         return;
      }

      if (SDL_KEYDOWN == ev.type)
      {
         switch (ev.key.keysym.sym)
         {
         case SDLK_h:
            PrintCommands();
            break;
         default:
            break;
         }
      }
   }

   mLogic->Update(game_time, elapsed_time);
}

void KinectApp::RenderScene()
{
   mLogic->Render();
}

void KinectApp::Mainloop()
{
   const int delta_time = 1000 / 60;
   int current_time = SDL_GetTicks();
   int game_time = 0;
   int accumulator = 0;

   while(!mQuitRequested)
   {
      int new_time = SDL_GetTicks();
      int frame_time = new_time - current_time;

      current_time = new_time;
      accumulator += frame_time;

      while (accumulator >= delta_time)
      {
         UpdateScene(game_time, delta_time);
         accumulator -= delta_time;
         game_time += delta_time;
      }

      RenderScene();
   }
}
