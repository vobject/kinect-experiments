#include "ResourceCache.h"
#include "Log.h"

#include <SDL.h>
#include <SDL_image.h>

#include <boost/filesystem.hpp>
namespace boostfs = boost::filesystem;

ResourceCache::ResourceCache()
{
   if (0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
       throw "Failed to initialize SDL_image";
    }
}

ResourceCache::~ResourceCache()
{
   for (auto& obj : mCache)
   {
      SDL_FreeSurface(obj.second);
   }
   mCache.clear();
}

void ResourceCache::AddDirectory(const std::string& dir)
{
   boostfs::path path(dir);

   try
   {
      if (!boostfs::exists(path) || !boostfs::is_directory(path)) {
         LOG(logDEBUG) << "Resource directory does not exist: " << path;
         return;
      }

      boostfs::directory_iterator dir_iter(path);
      boostfs::directory_iterator end_iter;

      for (; dir_iter != end_iter; dir_iter++)
      {
         if (boostfs::is_directory(*dir_iter)) {
            continue;
         }

         Load(dir_iter->path().c_str(), dir_iter->path().filename().c_str());
      }
   }
   catch (const boostfs::filesystem_error& ex)
   {
      LOG(logERROR) << "File system exception while adding resource directory.";
   }
}

SDL_Surface* ResourceCache::GetResource(const std::string& id)
{
   return mCache[id];
}

void ResourceCache::Load(const std::string& file, const std::string& id)
{
   SDL_Surface* img_loaded = IMG_Load(file.c_str());
   if (NULL == img_loaded) {
      throw "Failed to load animation frame";
   }

   SDL_Surface* img_compat = SDL_DisplayFormat(img_loaded);
   if (NULL == img_compat) {
      throw "Failed to convert animation frame to display format";
   }
   SDL_FreeSurface(img_loaded);

   const Uint32 colorkey = SDL_MapRGB( img_compat->format, 0, 0, 0);
   SDL_SetColorKey( img_compat, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);

   mCache[id] = img_compat;
}
