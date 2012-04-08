#include "SpriteResource.h"
#include "Log.h"

SpriteResource::SpriteResource()
   : mWidth(0)
   , mHeight(0)
{

}

SpriteResource::~SpriteResource()
{
   for (auto& surface : mFrames)
   {
      SDL_FreeSurface(surface);
   }
   mFrames.clear();
}

int SpriteResource::GetWidth() const
{
   return mWidth;
}

int SpriteResource::GetHeight() const
{
   return mHeight;
}

void SpriteResource::SetSize(const int width, const int height)
{
   mWidth = width;
   mHeight = height;
}

void SpriteResource::AddFrame(SDL_Surface* frame)
{
   mFrames.push_back(frame);
}

SDL_Surface* SpriteResource::GetFrame(const int n) const
{
   return mFrames[n];
}

int SpriteResource::GetFrameCount() const
{
   return mFrames.size();
}
