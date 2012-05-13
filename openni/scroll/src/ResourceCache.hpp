#ifndef RESOURCE_CACHE_HPP
#define RESOURCE_CACHE_HPP

#include "BackgroundResource.h"
#include "SpriteResource.h"
#include "Utils.hpp"

#include <SDL.h>

#include <memory>
#include <string>
#include <vector>
#include <map>

class Kinect;

class ResourceCache
{
public:
   ResourceCache();
   ~ResourceCache();

   ResourceCache(const ResourceCache&) = delete;
   ResourceCache& operator=(const ResourceCache&) = delete;

   BackgroundResource GetBackground(const std::string& id);
   SpriteResource GetSprite(const std::string& id);
//   Texture GetPlayer(const Kinect& kinect);
   // std::shared_ptr<...> GetAudioSample(const std::string& id);

//   void AddDirectory(const std::string& dir);
//   SDL_Surface* GetResource(const std::string& id);

private:
   void LoadBackground(const std::string& file, const std::string& id);
   void LoadSprite(const std::vector<std::string>& files, const std::string& id);
   SDL_Surface* LoadTexture(const std::string& file);

   std::string mResDir;
   std::map<const std::string, BackgroundResource> mBackgrounds;
   std::map<const std::string, SpriteResource> mSprites;
   std::vector<SDL_Surface*> mSurfaceCache;
//   SDL_Surface* mPlayer;
};

#endif // RESOURCE_CACHE_HPP
