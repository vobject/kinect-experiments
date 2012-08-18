#include "BomberPersonApp.hpp"
#include "nui/Kinect.hpp"
#include "nui/KinectDummy.hpp"
#include "video/WindowFrame.hpp"
#include "render/GlNoRes.hpp"
#include "render/SdlNoRes.hpp"
#include "game/Logic.hpp"

#include <SDL.h>

#include <X11/Xlib.h>

BomberPersonApp::BomberPersonApp()
{

}

BomberPersonApp::~BomberPersonApp()
{

}

void BomberPersonApp::Start()
{
   Initialize();
   Mainloop();
}

void BomberPersonApp::Mainloop()
{
   // TODO: Replace SDL times with sd::chonos classes.
//   auto sys = std::chrono::system_clock::now();
//   auto stead = std::chrono::steady_clock::now();
//   auto high = std::chrono::high_resolution_clock::now();

   const int delta_time = 15;
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
         ProcessInput();
         UpdateScene(game_time, delta_time);
         accumulator -= delta_time;
         game_time += delta_time;
      }

      RenderScene();
   }
}

void BomberPersonApp::Initialize()
{
   // HACK for ubuntu1204: https://github.com/DrMcCoy/xoreos/commit/9a6c84d5458256ac5a0ff7525055ef2d8761e683
   if (!XInitThreads()) {
      throw "Failed to initialize Xlib muti-threading support";
   }

   mVideoMode = VideoMode::Software;
   mVideoResolution = { 800_px, 600_px };

   InitNui();
   InitVideo(mVideoMode, mVideoResolution);

   mRenderer = std::make_shared<SdlNoRes>();
   mWndFrame = std::make_shared<WindowFrame>("BomberPerson");
   mLogic = std::make_shared<Logic>(mRenderer, mNui);
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
      case SDL_KEYDOWN:
      case SDL_KEYUP:
         {
            // TODO: Enable switching renderers with Strg-ANYKEY keys.

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

//   mKinect->NextFrame();
//   mLogic->ProcessInput(*mKinect);
}

void BomberPersonApp::UpdateScene(const int app_time, const int elapsed_time)
{
   mLogic->Update(app_time, elapsed_time);
   mWndFrame->UpdateDone();
}

void BomberPersonApp::RenderScene()
{
   mLogic->Render();
   mWndFrame->FrameDone();
}

void BomberPersonApp::InitNui()
{
   mNui = std::make_shared<Kinect>();
   try
   {
      LOG(logINFO) << "Connecting to Kinect device. Please stand by...";

      mNui->Init();
   }
   catch (...)
   {
      LOG(logINFO) << "Failed to initialize a connection to Kinect device.";

      mNui = std::make_shared<KinectDummy>();
      mNui->Init();
   }
}

void BomberPersonApp::InitVideo(const VideoMode mode, const Size res) const
{
   if (0 > SDL_Init(SDL_INIT_VIDEO)) {
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit);

   if (VideoMode::OpenGL == mode) {
      SelectGlVideo(res);
   }
   else if (VideoMode::Software == mode) {
      SelectSdlVideo(res);
   }
   else {
      throw "Invalid video mode.";
   }
}

void BomberPersonApp::SelectSdlVideo(const Size res) const
{
   const auto screen = SDL_SetVideoMode(res.Width,
                                        res.Height,
                                        32,
                                        SDL_ANYFORMAT |
                                           SDL_SWSURFACE |
                                           SDL_DOUBLEBUF |
                                           SDL_RESIZABLE);
   if (!screen) {
      throw "SDL_SetVideoMode() failed.";
   }

   // The return value of SDL_SetVideoMode() (-> screen) should not be freed
   //  by the caller. The man page tells us to rely on SDL_Quit() to do this.
}

void BomberPersonApp::SelectGlVideo(const Size res) const
{
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   const auto screen = SDL_SetVideoMode(res.Width,
                                        res.Height,
                                        32,
                                        SDL_OPENGL | SDL_RESIZABLE);
   if (!screen) {
      throw "SDL_SetVideoMode() failed.";
   }
}
