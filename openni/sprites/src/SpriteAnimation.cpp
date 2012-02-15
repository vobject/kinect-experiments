#include "SpriteAnimation.h"
#include "SdlWindow.h"

#include <SDL.h>
#include <SDL_image.h>

SpriteAnimation::SpriteAnimation()
   : mCurrentFrame(0)
   , mUpdateRate(DEFAULT_UDATE_RATE)
   , mLastFrameTime(0)
{
   if (0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
      throw "Failed to initialize SDL_image";
   }
}

SpriteAnimation::~SpriteAnimation()
{
   for (std::vector<SDL_Surface*>::const_iterator it = mFrames.begin();
        it != mFrames.end();
        it++)
   {
      SDL_FreeSurface(*it);
   }
}

void SpriteAnimation::AddFrame(const std::string& file)
{
   SDL_Surface* img_load = IMG_Load(file.c_str());
   if (NULL == img_load) {
      throw "Failed to load animation frame";
   }

   SDL_Surface* img_compat = SDL_DisplayFormat( img_load );
   if (NULL == img_compat) {
      throw "Failed to convert animation frame to display format";
   }
   SDL_FreeSurface(img_load);

   const Uint32 colorkey = SDL_MapRGB( img_compat->format, 0, 0, 0);
   SDL_SetColorKey( img_compat, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);

   mFrames.push_back(img_compat);
}

void SpriteAnimation::Init(int update_rate /*=DEFAULT_UDATE_RATE*/)
{
   mCurrentFrame = 0;
   mUpdateRate = update_rate;
}

bool SpriteAnimation::IsPlaying() const
{
   return (mCurrentFrame != (mFrames.size() - 1));
}

void SpriteAnimation::Stop()
{
   mCurrentFrame = mFrames.size() - 1;
}

void SpriteAnimation::RenderFrame(const SdlWindow& wnd, SDL_Rect* const dest)
{
   if (!IsPlaying()) {
      return;
   }

   NextFrame();

   SDL_Surface* frame = mFrames.at(mCurrentFrame);
   SDL_Rect dest_rect = { dest->x - (frame->w / 2),
                          dest->y - (frame->h / 2),
                          dest->h,
                          dest->w };

   wnd.Blit(frame, NULL, &dest_rect);
}

void SpriteAnimation::NextFrame()
{
   const int currentTime = SDL_GetTicks();

   if ((currentTime - mLastFrameTime) > mUpdateRate)
   {
      mCurrentFrame = (mCurrentFrame + 1) % mFrames.size();
      mLastFrameTime = currentTime;
   }
}
