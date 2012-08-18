#include "WindowFrame.hpp"

#include <sstream>
#include <iostream>

WindowFrame::WindowFrame(const std::string& title)
   : mTitle(title)
{
   SDL_WM_SetCaption(mTitle.c_str(), NULL);

#ifdef WIN32
   if (0 > SDL_Init(SDL_INIT_TIMER)) {
#else
   if (0 > SDL_Init(SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER)) {
#endif
      throw "Cannot init SDL timer subsystem.";
   }
   mFrameTimer = SDL_AddTimer(FRAME_TIMER_UPDATE_RATE,
                              DefaultFrameTimerCallback,
                              this);
}

WindowFrame::~WindowFrame()
{
   SDL_RemoveTimer(mFrameTimer);
}

void WindowFrame::UpdateDone()
{
   mUpdateCount++;
}

void WindowFrame::FrameDone()
{
   mFrameCount++;
}

Uint32 WindowFrame::DefaultFrameTimerCallback(const Uint32 interval, void* param)
{
   WindowFrame* obj = static_cast<WindowFrame*>(param);

   obj->mUPS = (obj->mUpdateCount / static_cast<float>(interval)) * obj->FRAME_TIMER_UPDATE_RATE;
   obj->mUpdateCount = 0;

   obj->mFPS = (obj->mFrameCount / static_cast<float>(interval)) * obj->FRAME_TIMER_UPDATE_RATE;
   obj->mFrameCount = 0;

   std::ostringstream caption;
   caption << obj->mTitle;
#ifdef NDEBUG
   caption << " (Release) - ";
#else
   caption << " (Debug) - ";
#endif
   caption << obj->mUPS << " UPS";
   caption << " - ";
   caption << obj->mFPS << " FPS";

   SDL_WM_SetCaption(caption.str().c_str(), NULL);
//   LOG(logDEBUG) << caption.str();

   return interval;
}
