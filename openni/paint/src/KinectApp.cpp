#include "KinectApp.hpp"
#include "Kinect.hpp"
#include "GlWindow.hpp"
#include "GlKinectBackground.hpp"
#include "SdlWindow.hpp"
#include "SdlKinectBackground.hpp"
#include "Utils.hpp"

#include <SDL.h>

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

KinectApp::KinectApp()
{

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
   mWindow = std::make_shared<GlWindow>(Size(1024_px, 768_px), "paint");
//   mWindow = std::make_shared<SdlWindow>(Size(1024_px, 768_px), "paint");

   mKinect = std::make_shared<Kinect>();
   try
   {
      mKinect->Init();
      mKinectBg = std::make_shared<GlKinectBackground>(mKinect);
//      mKinectBg = std::make_shared<SdlKinectBackground>(mKinect, mWindow->GetSize());
      mKinectConnected = true;
   }
   catch (...)
   {
      LOG(logWARNING) << "Failed to initialize a connection to Kinect.";
      mKinectConnected = false;
   }
}

void KinectApp::Mainloop()
{
   print_commands();

   // TODO: Replace SDL times with sd::chonos classes.
//   auto sys = std::chrono::system_clock::now();
//   auto stead = std::chrono::steady_clock::now();
//   auto high = std::chrono::high_resolution_clock::now();

   const int delta_time = 1;
   int current_time = SDL_GetTicks();
   int app_time = 0;
   int accumulator = 0;

   while(!mQuitRequested)
   {
      const int new_time = SDL_GetTicks();
      int frame_time = new_time - current_time;

      current_time = new_time;
      accumulator += frame_time;

      while (accumulator >= delta_time)
      {
         UpdateScene(app_time, delta_time);
         accumulator -= delta_time;
         app_time += delta_time;
      }

      RenderScene();
   }
}

void KinectApp::UpdateScene(const int app_time, const int elapsed_time)
{
   ProcessInput();

   if (mKinectConnected)
   {
      // Poll for Kinect input.
      mKinect->NextFrame();
      ProcessKinectInput();
   }
}

void KinectApp::RenderScene()
{
   if (mKinectConnected)
   {
      const auto bg = mKinectBg->GetImage();
      mWindow->Blit(bg, mKinect->GetSize(), {0, 0});
   }

   for (const auto& line : mState.lines)
   {
      if (line.empty()) {
         continue;
      }

      Point previous = line.at(0);
      for (const auto& pt : line)
      {
         mWindow->DrawLine({ previous.X, previous.Y }, { pt.X, pt.Y } );
         previous = pt;
      }
   }

   for (const auto& pt : mState.active_line)
   {
      mWindow->DrawRect({ pt.X, pt.Y }, 6_px);
   }

   mWindow->Flip();

   if (!mKinectConnected) {
      // Kinect background will repaint the whole screen content anyway.
      mWindow->Clear();
   }
}

void KinectApp::ProcessInput()
{
   SDL_Event event;

   if (SDL_PollEvent(&event))
   {
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
               else if (SDLK_b == event.key.keysym.sym && mKinectConnected) {
                  mKinectBg->SwitchMode();
               }
            }
            break;
         case SDL_MOUSEBUTTONDOWN:
            {
               if (event.button.button == SDL_BUTTON_LEFT) {
                  mState.drawing = true;
                  mState.active_line.push_back({event.button.x, event.button.y});
               }
               else if (event.button.button == SDL_BUTTON_RIGHT) {
                  mState.lines.clear();
               }
            }
            break;
         case SDL_MOUSEBUTTONUP:
            mState.lines.push_back(mState.active_line);
            mState.active_line.clear();
            mState.drawing = false;
            break;
         case SDL_MOUSEMOTION:
            {
               if (mState.drawing) {
                  mState.active_line.push_back({event.motion.x, event.motion.y});
               }
            }
            break;
         default:
            break;
      }
   }
}

void KinectApp::ProcessKinectInput()
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
      if (!mState.active_line.empty())
      {
         // Drawing mode just stopped.
         mState.lines.push_back(mState.active_line);
         mState.active_line.clear();
      }
      return;
   }

   const float x_factor = static_cast<float>(mWindow->GetSize().Width) / mKinect->GetSize().Width;
   const float y_factor = static_cast<float>(mWindow->GetSize().Height) / mKinect->GetSize().Height;
   const int lhand_x = joints[XN_SKEL_LEFT_HAND].X * x_factor;
   const int lhand_y = joints[XN_SKEL_LEFT_HAND].Y * y_factor;
   mState.active_line.push_back({lhand_x, lhand_y});
}
