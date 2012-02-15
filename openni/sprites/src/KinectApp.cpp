#include "KinectApp.h"
#include "Log.h"
#include "SdlWindow.h"
#include "SdlWindowDrawer.h"
#include "UserDrawer.h"
#include "DebugOverlayDrawer.h"
#include "FpsDrawer.h"
#include "SpriteDrawer.h"

#include <SDL.h>
#include <SDL_image.h>

#include <iostream>

KinectApp::KinectApp(const std::string& path)
   : mPath(path)
   , mMainloopDone(false)
{
   Log::ReportingLevel() = logDEBUG;
}

KinectApp::~KinectApp()
{

}

void KinectApp::PrintCommands() const
{
   std::cout << "Commands:\n"
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

void KinectApp::Mainloop()
{
   if (mPath.empty()) {
      mKinect.Init();
   }
   else {
      mKinect.InitPlayback(mPath);
   }

   SdlWindow wnd(mKinect.GetXRes(), mKinect.GetYRes());

   SdlWindowDrawer wnd_observer(&mKinect, wnd);
   UserDrawer user_observer(&mKinect, wnd);
   SpriteDrawer sprite_observer(&mKinect, wnd);
   FpsDrawer fps_observer(&mKinect, wnd);
   DebugOverlayDrawer debug_observer(&mKinect, wnd);

   SDL_Event ev;

   // The message pump:
   //  1. Process the SDL event if there is one present.
   //  2. Grab the next frame from the generators and display it.
   while(!mMainloopDone)
   {
      while (SDL_PollEvent(&ev))
      {
         // Quit the message pump if the user closed the window or pressed ESC.
         if((SDL_QUIT == ev.type) || (SDLK_ESCAPE == ev.key.keysym.sym))
         {
            mMainloopDone = true;
            break;
         }

         if (SDL_KEYDOWN == ev.type)
         {
            switch (ev.key.keysym.sym)
            {
            case SDLK_h:
               PrintCommands();
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

      mKinect.NextFrame();
      wnd.Flip();
   }
}
