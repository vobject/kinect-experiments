#include "ScrollApp.hpp"
#include "Nui.hpp"
#include "Window.hpp"
#include "ResourceCache.hpp"
#include "GlRenderer.hpp"
#include "SdlRenderer.hpp"
#include "Logic.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <X11/Xlib.h>

ScrollApp::ScrollApp()
{
   Log::ReportingLevel() = logDEBUG;
}

ScrollApp::~ScrollApp()
{

}

void ScrollApp::Initialize()
{
   // HACK for ubuntu1024: https://github.com/DrMcCoy/xoreos/commit/9a6c84d5458256ac5a0ff7525055ef2d8761e683
   if (!XInitThreads()) {
      throw "Failed to initialize Xlib muti-threading support";
   }

   InitGlVideo({1024_px, 768_px});
   InitKinect("");

   mWindow = std::make_shared<kinex::Window>("scroll");
   mResCache = std::make_shared<ResourceCache>();
   mRenderer = std::make_shared<GlRenderer>(mResCache);
   mLogic = std::make_shared<Logic>(mRenderer, mResCache, mKinect);
}

void ScrollApp::UpdateScene(const int app_time, const int elapsed_time)
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

   // Poll for Kinect input on every update cycle.
   mKinect->NextFrame();
   mLogic->Update(app_time, elapsed_time);
}

void ScrollApp::RenderScene()
{
   mLogic->Render();
   mWindow->FrameDone();
}