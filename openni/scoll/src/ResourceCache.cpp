#include "ResourceCache.h"
#include "Log.h"

#include <SDL.h>
#include <SDL_image.h>

//#include <boost/filesystem.hpp>
//namespace boostfs = boost::filesystem;

ResourceCache::ResourceCache()
   : mResDir("res")
{
   if (0 == IMG_Init(IMG_INIT_JPG | IMG_INIT_PNG)) {
       throw "Failed to initialize SDL_image";
   }

   // FIXME:
//   Load("res/background/smw.jpg", "smw");
//   Load("res/background/2zxr32b.png", "smw");
   LoadSprite({mResDir + "/sprite/aaa2.jpg"}, "background");
   LoadSprite({mResDir + "/sprite/explode1.jpg"}, "arcanister");
   LoadSprite({mResDir + "/sprite/blood_b/1.png",
               mResDir + "/sprite/blood_b/2.png",
               mResDir + "/sprite/blood_b/3.png",
               mResDir + "/sprite/blood_b/4.png",
               mResDir + "/sprite/blood_b/5.png",
               mResDir + "/sprite/blood_b/6.png",}, "blood_b");
}

ResourceCache::~ResourceCache()
{

}

//void ResourceCache::AddDirectory(const std::string& dir)
//{
//   boostfs::path path(dir);
//
//   try
//   {
//      if (!boostfs::exists(path) || !boostfs::is_directory(path)) {
//         LOG(logDEBUG) << "Resource directory does not exist: " << path;
//         return;
//      }
//
//      boostfs::directory_iterator dir_iter(path);
//      boostfs::directory_iterator end_iter;
//
//      for (; dir_iter != end_iter; dir_iter++)
//      {
//         if (boostfs::is_directory(*dir_iter)) {
//            continue;
//         }
//
//         Load(dir_iter->path().c_str(), dir_iter->path().filename().c_str());
//      }
//   }
//   catch (const boostfs::filesystem_error& ex)
//   {
//      LOG(logERROR) << "File system exception while adding resource directory.";
//   }
//}

std::vector<SDL_Surface*> ResourceCache::GetSpriteFrames(const std::string& id)
{
   return mSpriteFrames[id];
}

void ResourceCache::LoadSprite(const std::vector<std::string>& files, const std::string& id)
{
   std::vector<SDL_Surface*> frames;

   for (const auto& file : files)
   {
      SDL_Surface* img_loaded = IMG_Load(file.c_str());
      if (!img_loaded) {
         throw "Failed to load animation frame";
      }

      SDL_Surface* img_compat = SDL_DisplayFormat(img_loaded);
      if (!img_compat) {
         throw "Failed to convert animation frame to display format";
      }
      SDL_FreeSurface(img_loaded);
      img_loaded = nullptr;

//      const Uint32 colorkey = SDL_MapRGB(img_compat->format, 0, 0, 0);
//      SDL_SetColorKey(img_compat, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey);

      frames.push_back(img_compat);
   }

   mSpriteFrames[id] = frames;
}
