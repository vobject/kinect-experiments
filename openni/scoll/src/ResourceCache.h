#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H

#include "SpriteResource.h"

#include <SDL.h>

#include <memory>
#include <string>
#include <vector>
#include <map>

class ResourceCache
{
public:
   ResourceCache();
   ~ResourceCache();

   std::shared_ptr<SpriteResource> GetSprite(const std::string& id);
   // std::shared_ptr<...> GetSound(const std::string& id);

//   void AddDirectory(const std::string& dir);
//   SDL_Surface* GetResource(const std::string& id);

private:
   void LoadSprite(const std::vector<std::string>& files, const std::string& id);

   std::string mResDir;
   std::map<std::string, std::shared_ptr<SpriteResource>> mSprites;

   ResourceCache(const ResourceCache&);
   const ResourceCache& operator=(const ResourceCache&);
};

#endif // RESOURCE_CACHE_H
