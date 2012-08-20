#ifndef DIRECTED_SPRITE_RESOURCE_HPP
#define DIRECTED_SPRITE_RESOURCE_HPP

//#include "Texture.h"
#include "SpriteResource.hpp"
#include "../utils/Utils.hpp"

#include <string>
#include <vector>

struct SDL_Surface;

class DirectedSpriteResource
{
public:
   DirectedSpriteResource();
   DirectedSpriteResource(const std::string& id,
                          const std::vector<SDL_Surface*>& textures_up,
                          const std::vector<SDL_Surface*>& textures_down,
                          const std::vector<SDL_Surface*>& textures_left,
                          const std::vector<SDL_Surface*>& textures_right);
   ~DirectedSpriteResource();

   DirectedSpriteResource(const DirectedSpriteResource&) = default;
   DirectedSpriteResource& operator=(const DirectedSpriteResource&) = default;

   std::string GetId() const;
   int GetFrameCount(Direction dir) const;
   SDL_Surface* GetFrame(Direction dir, int n) const;
   Size GetSize(Direction dir) const;

private:
   std::string mId;
   std::vector<SDL_Surface*> mFramesUp;
   std::vector<SDL_Surface*> mFramesDown;
   std::vector<SDL_Surface*> mFramesLeft;
   std::vector<SDL_Surface*> mFramesRight;
};

#endif // DIRECTED_SPRITE_RESOURCE_HPP
