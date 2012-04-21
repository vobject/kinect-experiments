#ifndef TEXTURE_H
#define TEXTURE_H

#include "Utils.h"

#include <SDL.h>

class Texture
{
public:
   Texture(SDL_Surface* surface);
   ~Texture();

   void Blit(const Texture& tex, const Rect& rect);
   void* GetData() const;
   Size GetSize() const;

protected:
   SDL_Surface* mSurface;
};

#endif // TEXTURE_H