#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Utils.hpp"

#include <SDL.h>

#include <string>

namespace kinex {

class Window
{
public:
   Window(const std::string& title);
   virtual ~Window();

   virtual void FrameDone();

protected:
   static Uint32 DefaultFrameTimerCallback(Uint32 interval, void *param);

   std::string mTitle;

   SDL_TimerID mFrameTimer = nullptr;
   int mFrameCount = 0;
   int mFPS = 0;
};

} // namespace kinex

#endif // WINDOW_HPP
