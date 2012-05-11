#include "KinectApp.hpp"
#include "ResourceCache.h"
#include "SdlWindow.h"
#include "Renderer.h"
#include "Logic.h"
#include "Kinect.h"
#include "Utils.hpp"

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

   mKinect = std::make_shared<Kinect>();
   mKinect->Init();

   // This has to go first to set the display format.
   mWindow = std::make_shared<SdlWindow>(1024_px, 768_px, "scroll");
   mResCache = std::make_shared<ResourceCache>();
   mRenderer = std::make_shared<Renderer>(mWindow, mResCache);
   mLogic = std::make_shared<Logic>(mRenderer, mResCache, mKinect);
   mLogic->SetScreenSize(mWindow->GetXRes(), mWindow->GetYRes());
}

void KinectApp::UpdateScene(const int game_time, const int elapsed_time)
{
   SDL_Event event;

   if (SDL_PollEvent(&event))
   {
      if((SDL_QUIT == event.type) || (SDLK_ESCAPE == event.key.keysym.sym))
      {
         // Quit if the user closed the window or pressed ESC.
         mQuitRequested = true;
         return;
      }

      switch (event.type)
      {
         case SDL_KEYDOWN:
         case SDL_KEYUP:
            mLogic->ProcessInput(event.key);
            break;
         case SDL_MOUSEBUTTONDOWN:
         case SDL_MOUSEBUTTONUP:
            mLogic->ProcessInput(event.button);
            break;
         default:
            break;
      }
   }

   // Poll for kinect input on every update cycle.
   mKinect->NextFrame();
   mLogic->Update(game_time, elapsed_time);
}

void KinectApp::RenderScene()
{
   mLogic->Render();
   mWindow->Flip();
}

void KinectApp::Mainloop()
{
   const int delta_time = 1;
   int current_time = SDL_GetTicks();
   int game_time = 0;
   int accumulator = 0;

   while(!mQuitRequested)
   {
      const int new_time = SDL_GetTicks();
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
