#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include "Window.hpp"
#include "Utils.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <sstream>

class SdlWindow : public Window
{
public:
   SdlWindow(const Size& res, const std::string& text);
   virtual ~SdlWindow();

   SdlWindow(const SdlWindow&) = delete;
   SdlWindow& operator=(const SdlWindow&) = delete;

   void Blit(const void* data, const Size& data_size, const Point& dest) override;
   void Clear() override;
   void Flip() override;

   void DrawRect(const Point& pos, int size) override;
   void DrawLine(const Point& src_pos, const Point& dest_pos) override;
   void WriteText(const std::string& text, const Point& point) override;

private:
   static Uint32 FrameTimerCallback(Uint32 interval, void *param);

   void DrawPixel(int x, int y);

   SDL_Surface* mScreen;
   SDL_Surface* mSurface;

   TTF_Font* mFont;

   SDL_TimerID mFrameTimer;
   mutable int mFrameCount;
   int mFPS;
   SDL_Color mTextColor;
   std::ostringstream mTextBuf;
};

#endif // SDL_WINDOW_HPP
