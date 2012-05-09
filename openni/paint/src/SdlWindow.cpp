#include "SdlWindow.hpp"

#include <iostream>

SdlWindow::SdlWindow(const Size& res, const std::string& text)
   : Window(res)
   , mScreen(nullptr)
   , mSurface(nullptr)
   , mFont(nullptr)
   , mFrameTimer(nullptr)
   , mFrameCount(0)
   , mFPS(0)
{
   // Bring up SDL's video system...
#ifdef WIN32
   if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
#else
   if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER)) {
#endif
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit); // ...make sure everything gets cleaned up at exit...

   // ...and finally create the window.
   mScreen = SDL_SetVideoMode(mRes.Width,
                              mRes.Height,
                              32,
                              SDL_ANYFORMAT |
                                 SDL_SWSURFACE |
                                 SDL_DOUBLEBUF);
   if (!mScreen) {
      throw "SDL_SetVideoMode() failed.";
   }

   // This is the surface that we will write to.
   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   mRes.Width, mRes.Height,
                                   32, 0, 0, 0, 0);
   if (!mSurface) {
      throw "SDL_CreateRGBSurface() failed.";
   }

   if (0 > TTF_Init()) {
      throw "Cannot init SDL ttf feature.";
   }

   mFont = TTF_OpenFont("res/font/VeraMono.ttf", 16);
   if (!mFont) {
      TTF_Quit();
      throw "TTF_OpenFont() failed!";
   }
   SDL_WM_SetCaption(text.c_str(), NULL);

   mTextColor.r = 0xff;
   mTextColor.g = 0xff;
   mTextColor.b = 0xff;

   mFrameTimer = SDL_AddTimer(1000_ms, FrameTimerCallback, this);
}

SdlWindow::~SdlWindow()
{
   SDL_RemoveTimer(mFrameTimer);

   SDL_FreeSurface(mSurface);
   SDL_FreeSurface(mScreen);

   TTF_CloseFont(mFont);
   TTF_Quit();
}

void SdlWindow::Blit(const void* data, const Size& data_size, const Point& dest)
{
   // HACK: haha, very funny...
   SDL_Surface* surface = const_cast<SDL_Surface*>
                              (static_cast<const SDL_Surface*>(data));

   SDL_Rect rect = { static_cast<Sint16>(dest.X),
                     static_cast<Sint16>(dest.Y),
                     static_cast<Uint16>(data_size.Width),
                     static_cast<Uint16>(data_size.Height) };
   SDL_BlitSurface(surface, NULL, mSurface, &rect);
}

void SdlWindow::Clear()
{
   const auto black = SDL_MapRGB(mSurface->format, 0x00, 0x00, 0x00);
   SDL_FillRect(mSurface, NULL, black);
}

void SdlWindow::Flip()
{
   mTextBuf.str("");
#ifdef NDEBUG
   mTextBuf << "Release | ";
#else
   mTextBuf << "Debug | ";
#endif
   mTextBuf << mFPS << " FPS";
   WriteText(mTextBuf.str(), { 0, 0 });
   mFrameCount++;

//   SDL_Surface* tmp = zoomSurface(mSurface, 2.0, 2.0, 0);
   SDL_BlitSurface(mSurface, NULL, mScreen, NULL);
//   SDL_FreeSurface(tmp);
   SDL_Flip(mScreen);
}

void SdlWindow::DrawRect(const Point& pos, const int size)
{
   SDL_Rect rect = { (Sint16)(pos.X - (size / 2)),
                     (Sint16)(pos.Y - (size / 2)),
                     (Uint16)size,
                     (Uint16)size };

   SDL_FillRect(mSurface, &rect, 0xffffffff);
}

void SdlWindow::DrawLine(const Point& src_pos, const Point& dest_pos)
{
   // based on http://alawibaba.com/projects/whiteboard/drawing-SDL.c

#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
#define ABS(x) ((x)>0 ? (x) : (-x))

   int x1 = src_pos.X;
   int y1 = src_pos.Y;
   int x2 = dest_pos.X;
   int y2 = dest_pos.Y;

   int lg_delta;
   int sh_delta;
   int cycle;
   int lg_step;
   int sh_step;

   lg_delta = x2 - x1;
   sh_delta = y2 - y1;
   lg_step = SGN(lg_delta);
   lg_delta = ABS(lg_delta);
   sh_step = SGN(sh_delta);
   sh_delta = ABS(sh_delta);

   if (sh_delta < lg_delta)
   {
      cycle = lg_delta >> 1;
      while (x1 != x2)
      {
         DrawPixel(x1, y1);

         cycle += sh_delta;
         if (cycle > lg_delta)
         {
            cycle -= lg_delta;
            y1 += sh_step;
         }
         x1 += lg_step;
      }
      DrawPixel(x1, y1);
   }

   cycle = sh_delta >> 1;
   while (y1 != y2)
   {
      DrawPixel(x1, y1);

      cycle += lg_delta;
      if (cycle > sh_delta)
      {
         cycle -= sh_delta;
         x1 += lg_step;
      }
      y1 += sh_step;
   }
   DrawPixel(x1, y1);
}

void SdlWindow::WriteText(const std::string& text, const Point& point)
{
   SDL_Surface* surface = TTF_RenderText_Blended(mFont, text.c_str(), mTextColor);
   SDL_Rect rect = { (Sint16)point.X, (Sint16)point.Y, 0, 0 };

   SDL_BlitSurface(surface, NULL, mSurface, &rect);
   SDL_FreeSurface(surface);
}

void SdlWindow::DrawPixel(const int x_pos, const int y_pos)
{
   const size_t bpp = mSurface->format->BytesPerPixel;
   const size_t offset = (mSurface->pitch * y_pos) + (x_pos * bpp);
   const unsigned int color = 0xffffffff;

   SDL_LockSurface(mSurface);
   memcpy(static_cast<char*>(mSurface->pixels) + offset, &color, bpp);
   SDL_UnlockSurface(mSurface);
}

Uint32 SdlWindow::FrameTimerCallback(const Uint32 interval, void* param)
{
   SdlWindow* obj = static_cast<SdlWindow*>(param);

   obj->mFPS = (int)((obj->mFrameCount / (float)interval) * 1000_ms);
   obj->mFrameCount = 0;

   LOG(logDEBUG) << "FPS: " << obj->mFPS;

   return interval;
}
