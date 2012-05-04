#ifndef SDL_WINDOW_HPP
#define SDL_WINDOW_HPP

#include "Utils.hpp"

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>
#include <sstream>

//class SdlSurface
//{
//public:
//   SdlSurface(SDL_Surface* surface) : mSurface(surface)
//   {
//         SDL_LockSurface(mSurface);
//   }
//   ~SdlSurface()
//   {
//      SDL_UnlockSurface(mSurface);
//   }
//   SDL_Surface* operator->()
//   {
//      return mSurface;
//   }
//private:
//   SDL_Surface* mSurface;
//};

class SdlWindow
{
//   friend class Renderer;

public:
   SdlWindow(const Size& res, const std::string& text);
   virtual ~SdlWindow();

   SdlWindow(const SdlWindow&) = delete;
   SdlWindow& operator=(const SdlWindow&) = delete;

   Size GetSize() const;

//   SdlSurface GetSurface() const;
   void Blit(SDL_Surface* surface, const Point& dest);
   void Clear();
   void Flip();

   void DrawRect(int x_pos, int y_pos, unsigned int size, unsigned int color = 0xffffffff);
   void DrawLine(int x1, int y1, int x2, int y2, unsigned int color = 0xffffffff);
   void WriteText(int x_pos, int y_pos, SDL_Color color, const std::string& text);


private:
   static Uint32 FrameTimerCallback(Uint32 interval, void *param);

//   SDL_Surface *ScaleSurface(SDL_Surface *Surface, Uint16 Width, Uint16 Height);
   void DrawPixel(int x, int y, unsigned int color = 0xffffffff);

   const Size mRes;
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
