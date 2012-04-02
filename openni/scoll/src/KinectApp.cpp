#include "KinectApp.h"
#include "SdlWindow.h"
#include "Renderer.h"
#include "Logic.h"
#include "Log.h"

#include <SDL.h>

KinectApp::KinectApp()
   : mQuitRequested(false)
{
   Log::ReportingLevel() = logDEBUG;
}

KinectApp::~KinectApp()
{

}

void KinectApp::Start(const std::string& path)
{
   Initialize(path);
   Mainloop();
}

void KinectApp::Initialize(const std::string& path)
{
   mPath = path;
   mWindow.reset(new SdlWindow(640, 480));
   mRenderer.reset(new Renderer(mWindow));
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

      switch (ev.type)
      {
         case SDL_KEYDOWN:
         case SDL_KEYUP:
            mLogic->ProcessInput(ev.key);
            break;
         default:
            break;
      }
   }

   mLogic->Update(game_time, elapsed_time);
}

void KinectApp::RenderScene()
{
   mLogic->Render();
   mWindow->Flip();
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
