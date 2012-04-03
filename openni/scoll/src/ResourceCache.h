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

   void AddDirectory(const std::string& dir);
   SDL_Surface* GetResource(const std::string& id);

private:
   void Load(const std::string& file, const std::string& id);

   std::string mResDir;
   std::map<std::string, SDL_Surface*> mCache;

   ResourceCache(const ResourceCache&);
   const ResourceCache& operator=(const ResourceCache&);
};

#endif // RESOURCE_CACHE_H
