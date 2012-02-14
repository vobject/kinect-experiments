#ifndef SDL_WINDOW_H
#define SDL_WINDOW_H

#include <SDL.h>
#include <SDL_ttf.h>

#include <string>

class SdlSurface
{
public:
   SdlSurface(SDL_Surface* surface) : mSurface(surface)
   {
         SDL_LockSurface(mSurface);
   }
   ~SdlSurface()
   {
      SDL_UnlockSurface(mSurface);
   }
   SDL_Surface* operator->()
   {
      return mSurface;
   }
private:
   SDL_Surface* mSurface;
};

class SdlWindow
{
public:
   SdlWindow(int xres, int yres);
   virtual ~SdlWindow();

   int GetXRes() const;
   int GetYRes() const;

   SdlSurface GetSurface() const;
   void Blit(SDL_Surface* surface) const;
   void Flip() const;

   void DrawRect(Sint16 x_pos, Sint16 y_pos, Uint16 size, Uint32 color = 0xffffffff) const;
   void DrawLine(Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color = 0xffffffff) const;
   void WriteText(Sint16 x_pos, Sint16 y_pos, SDL_Color color, const std::string& text) const;

private:
   void DrawPixel(Uint32 x, Uint32 y, Uint32 color = 0xffffffff) const;

   const int mXRes;
   const int mYRes;
   SDL_Surface* mScreen;
   SDL_Surface* mSurface;

   TTF_Font* mFont;

   // Stuff we do not need atm.
   SdlWindow(const SdlWindow&);
   SdlWindow& operator=(const SdlWindow&);
};

#endif // SDL_WINDOW_H
