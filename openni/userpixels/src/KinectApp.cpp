#include "KinectApp.h"
#include "Log.h"
#include "SdlWindow.h"
#include "VlcPlayer.h"
#include "VlcRemote.h"
#include "SdlWindowDrawer.h"
#include "UserDrawer.h"
#include "DebugOverlayDrawer.h"
#include "FpsDrawer.h"

#include <SDL.h>

#include <iostream>

KinectApp::KinectApp(const std::string& path)
   : mPath(path)
{
   Log::ReportingLevel() = logDEBUG;
}

KinectApp::~KinectApp()
{

}

void KinectApp::PrintCommands() const
{
   std::cout << "Commands:\n"
             << "\tSPACE - Toggle playback/pause\n"
             << "\tm - Toggle image/depth mode\n"
             << "\tf - Seek 100 frames forward\n"
             << "\tb - Seek 100 frames backward\n"
             << "\ti - Increase depth by 20cm\n"
             << "\to - Decrease depth by 20cm\n"
             << "\tu - Toggle user tracking mode\n"
             << "\td - Toggle debug overlay mode\n"
             << "\th - Print this help message\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

void KinectApp::EventLoop()
{
   if (mPath.empty()) {
      mKinect.Init();
   }
   else {
      mKinect.InitPlayback(mPath);
   }

   SdlWindow wnd(mKinect.GetXRes(), mKinect.GetYRes());

   // FIXME: Stupid VLC does not seem to like forward slashed in its
   //  plugin path on windows.
   VlcPlayer video_player(wnd, "..\\..\\..\\..\\external\\vlc-1.1.11\\plugins", "screen://");
   VlcRemote video_remote(&mKinect, wnd, video_player);

   // Several observers.
   SdlWindowDrawer wnd_observer(&mKinect, wnd);
   UserDrawer user_observer(&mKinect, wnd);
   FpsDrawer fps_observer(&mKinect, wnd);
   DebugOverlayDrawer debug_observer(&mKinect, wnd);

   bool play_video = false;

   SDL_Event ev; // Catch incoming SDL events in this variable.

   // The message pump:
   //  1. Process the SDL event if there is one present.
   //  2. Grab the next frame from the generators and display it.
   for(;;)
   {
      if (SDL_PollEvent(&ev))
      {
         // Quit the message pump if the user closed the window or pressed ESC.
         if((SDL_QUIT == ev.type) || (SDLK_ESCAPE == ev.key.keysym.sym))
         {
            break;
         }
         else if (SDL_KEYDOWN == ev.type)
         {
            switch (ev.key.keysym.sym)
            {
            case SDLK_h:
               PrintCommands();
               break;
            case SDLK_SPACE: // Toggle pause/resume.
               play_video = !play_video;

               if (play_video) {
                  mKinect.Unsubscribe(&wnd_observer);
                  video_player.Play();
               }
               else {
                  video_player.Pause();
                  // HACK: Freakingly ugly...
                  //  The SdlWindowDrawer observer must be at to first observer
                  //  in the Subjects list. Otherwise all image alternations of
                  //  the other observers would be lost.

                  mKinect.Unsubscribe(&user_observer);
                  mKinect.Unsubscribe(&fps_observer);
                  mKinect.Unsubscribe(&debug_observer);

                  mKinect.Subscribe(&wnd_observer);
                  mKinect.Subscribe(&user_observer);
                  mKinect.Subscribe(&fps_observer);
                  mKinect.Subscribe(&debug_observer);
               }

               LOG(logDEBUG) << "Pause = " << !play_video;
               break;
            case SDLK_m: // Switch to the next DisplayMode.
               LOG(logDEBUG) << "Switching display mode to "
                             << wnd_observer.SwitchDisplayMode();
               break;
            case SDLK_u: // Switch to the next UserPaintMode.
               LOG(logDEBUG) << "Switching user paint mode to "
                             << user_observer.SwitchUserPaintMode();
               break;
            case SDLK_i: // Increase depth by 20cm.
               LOG(logDEBUG) << "Setting depth to "
                              << wnd_observer.IncreaseDepth();
               break;
            case SDLK_o: // Decrease depth by 20cm.
               LOG(logDEBUG) << "Setting depth to "
                             << wnd_observer.DecreaseDepth();
               break;
            case SDLK_f: // Seek forward.
               mKinect.SeekForward();
               break;
            case SDLK_b: // Seek backward.
               mKinect.SeekBackward();
               break;
            case SDLK_d: // Switch to the next DebugOverlayMode.
               LOG(logDEBUG) << "Switching debug overlay mode to "
                             << debug_observer.SwitchOverlayMode();
               break;
            default:
               break;
            }
         }
      }

      if (play_video) {
         video_player.Blit();
      }

      // Request new frame from OpenNI.
      mKinect.NextFrame();

      // Show the result.
      wnd.Flip();
   }
}
