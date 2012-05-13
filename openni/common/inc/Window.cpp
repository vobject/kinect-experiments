#include "Window.hpp"

#include <sstream>
#include <iostream>

namespace kinex {

Window::Window(const std::string& title)
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
   mFrameTimer = SDL_AddTimer(1000_ms, DefaultFrameTimerCallback, this);
}

Window::~Window()
{
   SDL_RemoveTimer(mFrameTimer);
}

void Window::FrameDone()
{
   mFrameCount++;
}

Uint32 Window::DefaultFrameTimerCallback(const Uint32 interval, void* param)
{
   Window* obj = static_cast<Window*>(param);

   obj->mFPS = (int)((obj->mFrameCount / (float)interval) * 1000_ms);
   obj->mFrameCount = 0;

   std::ostringstream caption;
   caption << obj->mTitle;
#ifdef NDEBUG
   caption << " (Release) - ";
#else
   caption << " (Debug) - ";
#endif
   caption << obj->mFPS << " FPS";

   SDL_WM_SetCaption(caption.str().c_str(), NULL);
   LOG(logDEBUG) << caption.str();

   return interval;
}

} // namespace kinex
