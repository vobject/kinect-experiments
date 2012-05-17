#include "KinectApp.hpp"
#include "Kinect.hpp"
#include "KinectDummy.hpp"

#include <SDL.h>

KinectApp::KinectApp()
{

}

KinectApp::~KinectApp()
{

}

void KinectApp::Start()
{
   Initialize();
   Mainloop();
}

void KinectApp::Mainloop()
{
   // TODO: Replace SDL times with sd::chonos classes.
//   auto sys = std::chrono::system_clock::now();
//   auto stead = std::chrono::steady_clock::now();
//   auto high = std::chrono::high_resolution_clock::now();

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

void KinectApp::InitKinect(const std::string& path)
{
   (void) path; // TODO: enable playback mode

   mKinect = std::make_shared<Kinect>();
   try
   {
      mKinect->Init();
   }
   catch (...)
   {
      LOG(logINFO) << "Failed to initialize a connection to Kinect.";

      mKinect = std::make_shared<KinectDummy>();
      mKinect->Init();
   }
}

void KinectApp::InitVideo()
{
   if (0 > SDL_Init(SDL_INIT_VIDEO)) {
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit);

   if (VideoMode::OpenGL == mCurrentVideoMode) {
      SelectGlVideo();
   }
   else if (VideoMode::Software == mCurrentVideoMode) {
      SelectSdlVideo();
   }
   else {
      throw "Invalid video mode.";
   }
}

void KinectApp::SelectSdlVideo()
{
   const auto screen = SDL_SetVideoMode(mCurrentResolution.Width,
                                        mCurrentResolution.Height,
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

void KinectApp::SelectGlVideo()
{
   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   const auto screen = SDL_SetVideoMode(mCurrentResolution.Width,
                                        mCurrentResolution.Height,
                                        32,
                                        SDL_OPENGL | SDL_RESIZABLE);
   if (!screen) {
      throw "SDL_SetVideoMode() failed.";
   }
}
