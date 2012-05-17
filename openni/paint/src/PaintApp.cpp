#include "PaintApp.hpp"
#include "Nui.hpp"
#include "Window.hpp"
#include "GlRenderer.hpp"
#include "GlKinectBackground.hpp"
#include "SdlRenderer.hpp"
#include "SdlKinectBackground.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <X11/Xlib.h>

#include <chrono>
#include <iostream>

static void print_commands()
{
   std::cout << "Commands:\n"
             << "\th - print available commands\n"
             << "\tb - toggle background modes\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

PaintApp::PaintApp()
{

}

PaintApp::~PaintApp()
{

}

void PaintApp::Initialize()
{
   // HACK for ubuntu1024: https://github.com/DrMcCoy/xoreos/commit/9a6c84d5458256ac5a0ff7525055ef2d8761e683
   if (!XInitThreads()) {
      throw "Failed to initialize Xlib muti-threading support";
   }

   InitSdlVideo({640_px, 480_px});
   InitKinect("");

   mWindow = std::make_shared<kinex::Window>("paint");
   mRenderer = std::make_shared<SdlRenderer>();
   mKinectBg = std::make_shared<GlKinectBackground>(mKinect);
   mState = std::make_shared<PaintStatus>();
}

void PaintApp::UpdateScene(const int app_time, const int elapsed_time)
{
   ProcessInput();

   mKinect->NextFrame();
   ProcessKinectInput();
}

void PaintApp::RenderScene()
{
   mRenderer->PreRender();
   mRenderer->Render(mKinectBg);
   mRenderer->Render(mState);
   mRenderer->PostRender();

   mWindow->FrameDone();
}

void PaintApp::ProcessInput()
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
         {
            if (SDLK_h == event.key.keysym.sym) {
               print_commands();
            }
            else if (SDLK_b == event.key.keysym.sym) {
               mKinectBg->SwitchMode();
            }
         }
         break;
      case SDL_MOUSEBUTTONDOWN:
         {
            if (event.button.button == SDL_BUTTON_LEFT) {
               mState->drawing = true;
               mState->active_line.push_back({event.button.x, event.button.y});
            }
            else if (event.button.button == SDL_BUTTON_RIGHT) {
               mState->lines.clear();
            }
         }
         break;
      case SDL_MOUSEBUTTONUP:
         mState->lines.push_back(mState->active_line);
         mState->active_line.clear();
         mState->drawing = false;
         break;
      case SDL_MOUSEMOTION:
         {
            if (mState->drawing) {
               mState->active_line.push_back({event.motion.x, event.motion.y});
            }
         }
         break;
      default:
         break;
   }
}

void PaintApp::ProcessKinectInput()
{
   const auto users = mKinect->GetUsers();
   if (users.empty()) {
      return;
   }

   auto joints = users[0].GetPerspectiveJoints();
   const auto torso_z = joints[XN_SKEL_TORSO].Z;
   const auto lhand_z = joints[XN_SKEL_LEFT_HAND].Z;

   // Draw only with outstreched arm.
   if ((torso_z - lhand_z) < 400.0)
   {
      if (!mState->active_line.empty())
      {
         // Drawing mode just stopped.
         mState->lines.push_back(mState->active_line);
         mState->active_line.clear();
      }
      return;
   }

   const auto screen = SDL_GetVideoSurface();
   const float x_factor = static_cast<float>(screen->w) / mKinect->GetSize().Width;
   const float y_factor = static_cast<float>(screen->h) / mKinect->GetSize().Height;
   const int lhand_x = joints[XN_SKEL_LEFT_HAND].X * x_factor;
   const int lhand_y = joints[XN_SKEL_LEFT_HAND].Y * y_factor;
   mState->active_line.push_back({lhand_x, lhand_y});
}
