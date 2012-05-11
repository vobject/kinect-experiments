#ifndef SPRITERESOURCE_H
#define SPRITERESOURCE_H

#include "Texture.h"
#include "Utils.hpp"

#include <SDL.h>

#include <memory>
#include <string>
#include <vector>

class SpriteResource
{
public:
   SpriteResource();
   SpriteResource(const std::string& id, const std::vector<std::shared_ptr<Texture>>& textures);
   ~SpriteResource();

   SpriteResource(const SpriteResource&) = default;
   SpriteResource& operator=(const SpriteResource&) = default;

   std::string GetId() const;
   int GetFrameCount() const;
   std::shared_ptr<Texture> GetFrame(int n) const;
   Size GetSize() const;

private:
   std::string mId;
   std::vector<std::shared_ptr<Texture>> mFrames;
};

#endif // SPRITERESOURCE_H
