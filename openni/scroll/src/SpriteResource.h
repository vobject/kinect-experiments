#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

//#include "Texture.h"
#include "Utils.hpp"

#include <SDL.h>

#include <string>
#include <vector>

class SpriteResource
{
public:
   SpriteResource();
   SpriteResource(const std::string& id, const std::vector<SDL_Surface*>& textures);
   ~SpriteResource();

   SpriteResource(const SpriteResource&) = default;
   SpriteResource& operator=(const SpriteResource&) = default;

   std::string GetId() const;
   int GetFrameCount() const;
   SDL_Surface* GetFrame(int n) const;
   Size GetSize() const;

private:
   std::string mId;
   std::vector<SDL_Surface*> mFrames;
};

#endif // SPRITERESOURCE_H
