#ifndef RESOURCE_CACHE_HPP
#define RESOURCE_CACHE_HPP

#include "SpriteResource.hpp"
#include "DirectedSpriteResource.hpp"
#include "../utils/Utils.hpp"

#include <string>
#include <vector>
#include <map>

struct SDL_Surface;

class ResourceCache
{
public:
   ResourceCache();
   ~ResourceCache();

   ResourceCache(const ResourceCache&) = delete;
   ResourceCache& operator=(const ResourceCache&) = delete;

   // TODO:
   // SetTheme();

//   BackgroundResource GetBackground(const std::string& id);
   SpriteResource GetSprite(const std::string& id);
   DirectedSpriteResource GetDirectedSprite(const std::string& id);
//   Texture GetPlayer(const Kinect& kinect);
   // std::shared_ptr<...> GetAudioSample(const std::string& id);

//   void AddDirectory(const std::string& dir);
//   SDL_Surface* GetResource(const std::string& id);

private:
//   void LoadBackground(const std::string& file, const std::string& id);
   void LoadSprite(const std::string& id,
                   const std::vector<std::string>& files);
   void LoadDirectedSprite(const std::string& id,
                           const std::vector<std::string>& files_up,
                           const std::vector<std::string>& files_down,
                           const std::vector<std::string>& files_left,
                           const std::vector<std::string>& files_right);

   SDL_Surface* LoadTexture(const std::string& file);

   std::string mResDir;
//   std::map<const std::string, BackgroundResource> mBackgrounds;
   std::map<std::string, SpriteResource> mSprites;
   std::map<std::string, DirectedSpriteResource> mDirectedSprites;
   std::vector<SDL_Surface*> mSurfaceCache;
//   SDL_Surface* mPlayer;
};

#endif // RESOURCE_CACHE_HPP
