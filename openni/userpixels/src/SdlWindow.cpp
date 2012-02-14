#include "SdlWindow.h"

SdlWindow::SdlWindow( const int xres, const int yres )
   : mXRes(xres)
   , mYRes(yres)
   , mScreen(NULL)
   , mSurface(NULL)
   , mFont(NULL)
{
   // Bring up SDL's video system...
#ifdef WIN32
   if (0 > SDL_Init(SDL_INIT_VIDEO)) {
#else
   if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD)) {
#endif
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit); // ...make sure everything gets cleaned up at exit...

   // ...and finally create the window.
   mScreen = SDL_SetVideoMode(mXRes,
                              mYRes,
                              0,
                              SDL_ANYFORMAT |
                                 SDL_HWSURFACE |
                                 SDL_DOUBLEBUF);
   if (!mScreen) {
      throw "SDL_SetVideoMode() failed.";
   }

   // This is the surface that we will write to.
   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   mXRes, mYRes,
                                   24, 0, 0, 0, 0);

   if (!mSurface) {
      throw "SDL_CreateRGBSurface() failed.";
   }

   if (0 > TTF_Init()) {
      throw "Cannot init SDL ttf feature.";
   }

   mFont = TTF_OpenFont("VeraMono.ttf", 16);

   if (!mFont) {
      TTF_Quit();
      throw "TTF_OpenFont() failed!";
   }

   SDL_WM_SetCaption("userpixels", NULL);
}

SdlWindow::~SdlWindow()
{
   SDL_FreeSurface(mSurface);
   SDL_FreeSurface(mScreen);

   TTF_CloseFont(mFont);
   TTF_Quit();
}

int SdlWindow::GetXRes() const
{
   return mXRes;
}

int SdlWindow::GetYRes() const
{
   return mYRes;
}

SdlSurface SdlWindow::GetSurface() const
{
   return SdlSurface(mSurface);
}

void SdlWindow::Blit(SDL_Surface* surface) const
{
   SDL_BlitSurface(surface, NULL, mSurface, NULL);
}

void SdlWindow::Flip() const
{
   SDL_BlitSurface(mSurface, NULL, mScreen, NULL);
   SDL_Flip(mScreen);
//    SDL_Delay(10);
}

void SdlWindow::DrawRect(
   const Sint16 x_pos,
   const Sint16 y_pos,
   const Uint16 size,
   const Uint32 color /* = 0xffffffff */
) const
{
   SDL_Rect rect = { (Sint16)(x_pos - (size / 2)), (Sint16)(y_pos - (size / 2)), size, size };

   SDL_FillRect(mSurface, &rect, color);
}

void SdlWindow::DrawLine( Uint32 x1, Uint32 y1, Uint32 x2, Uint32 y2, Uint32 color /*= 0xffffffff*/ ) const
{
   // based on http://alawibaba.com/projects/whiteboard/drawing-SDL.c

#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
#define ABS(x) ((x)>0 ? (x) : (-x))

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
         DrawPixel(x1, y1, color);

         cycle += sh_delta;
         if (cycle > lg_delta)
         {
            cycle -= lg_delta;
            y1 += sh_step;
         }
         x1 += lg_step;
      }
      DrawPixel(x1, y1, color);
   }

   cycle = sh_delta >> 1;
   while (y1 != y2)
   {
      DrawPixel(x1, y1, color);

      cycle += lg_delta;
      if (cycle > sh_delta)
      {
         cycle -= sh_delta;
         x1 += lg_step;
      }
      y1 += sh_step;
   }
   DrawPixel(x1, y1, color);
}

void SdlWindow::WriteText(
   const Sint16 x_pos,
   const Sint16 y_pos,
   const SDL_Color color,
   const std::string& text
) const
{
   if ((x_pos >= mXRes) || (y_pos >= mYRes))
   {
      return;
   }

   SDL_Surface* surface = TTF_RenderText_Blended(mFont, text.c_str(), color);
   SDL_Rect rect = { x_pos, y_pos, 0, 0 };

   SDL_BlitSurface(surface, NULL, mSurface, &rect);
   SDL_FreeSurface(surface);
}

void SdlWindow::DrawPixel( Uint32 x_pos, Uint32 y_pos, Uint32 color /*= 0xffffffff*/ ) const
{
   if ((x_pos >= mXRes) || (y_pos >= mYRes))
   {
      return;
   }

   const size_t bpp = mSurface->format->BytesPerPixel;
   const size_t offset = (mSurface->pitch * y_pos) + (x_pos * bpp);

   SDL_LockSurface(mSurface);
   memcpy(static_cast<char*>(mSurface->pixels) + offset, &color, bpp);
   SDL_UnlockSurface(mSurface);
}
