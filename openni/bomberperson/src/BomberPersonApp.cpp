#include "BomberPersonApp.hpp"
#include "Nui.hpp"
#include "Window.hpp"
#include "GlRenderer.hpp"
#include "SdlRenderer.hpp"
#include "Logic.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <X11/Xlib.h>

BomberPersonApp::BomberPersonApp()
{

}

BomberPersonApp::~BomberPersonApp()
{

}

void BomberPersonApp::Initialize()
{
   // HACK for ubuntu1024: https://github.com/DrMcCoy/xoreos/commit/9a6c84d5458256ac5a0ff7525055ef2d8761e683
   if (!XInitThreads()) {
      throw "Failed to initialize Xlib muti-threading support";
   }

   mCurrentVideoMode = VideoMode::Software;
   mCurrentResolution = {800_px, 600_px};

   InitVideo();
   InitKinect("");
   SelectRenderer(); // Kinect has to be set up for this!

   mWindow = std::make_shared<kinex::Window>("BomberPerson");
   mLogic = std::make_shared<Logic>(mRenderer, mKinect);
}

void BomberPersonApp::UpdateScene(const int app_time, const int elapsed_time)
{
   ProcessInput();

//   mKinect->NextFrame();
//   mLogic->ProcessInput(*mKinect);

   mLogic->Update(app_time, elapsed_time);
}

void BomberPersonApp::RenderScene()
{
   mLogic->Render();
   mWindow->FrameDone();
}

void BomberPersonApp::SelectRenderer()
{
//   if (VideoMode::OpenGL == mCurrentVideoMode) {
//      mRenderer = std::make_shared<GlRenderer>();
//   }
//   else
   if (VideoMode::Software == mCurrentVideoMode) {
      mRenderer = std::make_shared<SdlRenderer>(*mKinect);
   }
   else {
      throw "Invalid video mode.";
   }
}

void BomberPersonApp::ProcessInput()
{
   SDL_Event event;

   if (!SDL_PollEvent(&event)) {
      return;
   }

   if((SDL_QUIT == event.type) || (SDLK_ESCAPE == event.key.keysym.sym)) {
      // The user closed the window or pressed ESC.
      mQuitRequested = true;
      return;
   }

   switch (event.type)
   {
      case SDL_VIDEORESIZE:
         {
            // FIXME: SDL_VIDEORESIZE is buggy in SDL 1.2.15, see:
            //  http://bugzilla.libsdl.org/show_bug.cgi?id=1430
            mCurrentResolution = {event.resize.w, event.resize.h};
            InitVideo();
         }
         break;
      case SDL_KEYDOWN:
      case SDL_KEYUP:
         {
//            if (SDLK_s == event.key.keysym.sym) {
//               mCurrentVideoMode = VideoMode::Software;
//               InitVideo();
//               SelectRenderer();
//            }
//            else if (SDLK_o == event.key.keysym.sym) {
//               mCurrentVideoMode = VideoMode::OpenGL;
//               InitVideo();
//               SelectRenderer();
//            }

            mLogic->ProcessInput(event.key);
         }
         break;
      default:
         break;
   }
}
