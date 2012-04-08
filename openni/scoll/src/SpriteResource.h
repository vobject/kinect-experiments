#ifndef SPRITE_RESOURCE_H
#define SPRITE_RESOURCE_H

#include <SDL.h>

#include <string>
#include <vector>

class SpriteResource
{
public:
   SpriteResource();
   ~SpriteResource();

   int GetWidth() const;
   int GetHeight() const;
   void SetSize(int width, int height);

   void AddFrame(SDL_Surface* frame);
   SDL_Surface* GetFrame(int n) const;
   int GetFrameCount() const;

private:
   int mWidth;
   int mHeight;
   std::vector<SDL_Surface*> mFrames;

   SpriteResource(const SpriteResource&);
   const SpriteResource& operator=(const SpriteResource&);
};

#endif // SPRITE_RESOURCE_H
