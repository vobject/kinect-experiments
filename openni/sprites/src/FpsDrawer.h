#ifndef FPS_DRAWER_H
#define FPS_DRAWER_H

#include "Observer.h"
#include "KinectWrapper.h"

#include <SDL/SDL.h>

#include <sstream>

class SdlWindow;

class FpsDrawer : public Observer
{
public:
   FpsDrawer(KinectWrapper* subject, const SdlWindow& wnd);
   virtual ~FpsDrawer();

   virtual void Update(const Subject* updated_subject);

private:
   static Uint32 FrameTimerCallback(Uint32 interval, void *param);

   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;

   SDL_TimerID mFrameTimer;
   int mFrameCount;
   int mFPS;
   SDL_Color mTextColor;
   std::ostringstream mTextBuf;

   FpsDrawer& operator=(const FpsDrawer&);
};

#endif // FPS_DRAWER_H
