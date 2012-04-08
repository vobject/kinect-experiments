#ifndef RESOURCE_CACHE_H
#define RESOURCE_CACHE_H

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

   std::vector<SDL_Surface*> GetSpriteFrames(const std::string& id);
   // std::shared_ptr<...> GetAudioSample(const std::string& id);

//   void AddDirectory(const std::string& dir);
//   SDL_Surface* GetResource(const std::string& id);

private:
   void LoadSprite(const std::vector<std::string>& files, const std::string& id);

   std::string mResDir;
   std::map<const std::string, std::vector<SDL_Surface*>> mSpriteFrames;

   ResourceCache(const ResourceCache&);
   const ResourceCache& operator=(const ResourceCache&);
};

#endif // RESOURCE_CACHE_H
