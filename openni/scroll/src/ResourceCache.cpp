#include "ResourceCache.hpp"
#include "Kinect.hpp"
#include "Utils.hpp"

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

   LoadBackground(mResDir + "/sprite/bg0.jpg", "bg0");
   LoadBackground(mResDir + "/sprite/ken_big.jpg", "bg1");
   LoadBackground(mResDir + "/sprite/sf2_stage.png", "bg2");

   LoadSprite({mResDir + "/sprite/ex2scan-kairi.jpg"}, "enemy1");
   LoadSprite({mResDir + "/sprite/explode1.jpg"}, "arcanister");

   LoadSprite({mResDir + "/sprite/fb0.png",
               mResDir + "/sprite/fb1.png",
               mResDir + "/sprite/fb2.png",
               mResDir + "/sprite/fb3.png",
               mResDir + "/sprite/fb4.png",
               mResDir + "/sprite/fb5.png",
               mResDir + "/sprite/fb6.png",
               mResDir + "/sprite/fb7.png",}, "fireball");

   LoadSprite({mResDir + "/sprite/ken000.png",
               mResDir + "/sprite/ken001.png",
               mResDir + "/sprite/ken002.png",
               mResDir + "/sprite/ken003.png",
               mResDir + "/sprite/ken004.png",
               mResDir + "/sprite/ken005.png",}, "ken");

   LoadSprite({mResDir + "/sprite/hulk0.png",
               mResDir + "/sprite/hulk1.png",
               mResDir + "/sprite/hulk2.png",
               mResDir + "/sprite/hulk3.png",
               mResDir + "/sprite/hulk4.png",
               mResDir + "/sprite/hulk5.png",
               mResDir + "/sprite/hulk6.png",
               mResDir + "/sprite/hulk7.png",}, "hulk");

   LoadSprite({mResDir + "/sprite/blood_a/1.png",
               mResDir + "/sprite/blood_a/2.png",
               mResDir + "/sprite/blood_a/3.png",
               mResDir + "/sprite/blood_a/4.png",
               mResDir + "/sprite/blood_a/5.png",
               mResDir + "/sprite/blood_a/6.png",}, "blood_a");
   LoadSprite({mResDir + "/sprite/blood_b/1.png",
               mResDir + "/sprite/blood_b/2.png",
               mResDir + "/sprite/blood_b/3.png",
               mResDir + "/sprite/blood_b/4.png",
               mResDir + "/sprite/blood_b/5.png",
               mResDir + "/sprite/blood_b/6.png",}, "blood_b");
   LoadSprite({mResDir + "/sprite/blood_c/1.png",
               mResDir + "/sprite/blood_c/2.png",
               mResDir + "/sprite/blood_c/3.png",
               mResDir + "/sprite/blood_c/4.png",
               mResDir + "/sprite/blood_c/5.png",
               mResDir + "/sprite/blood_c/6.png",}, "blood_c");
   LoadSprite({mResDir + "/sprite/blood_d/1.png",
               mResDir + "/sprite/blood_d/2.png",
               mResDir + "/sprite/blood_d/3.png",
               mResDir + "/sprite/blood_d/4.png",
               mResDir + "/sprite/blood_d/5.png",
               mResDir + "/sprite/blood_d/6.png",}, "blood_d");
}

ResourceCache::~ResourceCache()
{
   for (auto& surface : mSurfaceCache) {
      SDL_FreeSurface(surface);
   }
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

BackgroundResource ResourceCache::GetBackground(const std::string& id)
{
   return mBackgrounds[id];
}

SpriteResource ResourceCache::GetSprite(const std::string& id)
{
   return mSprites[id];
}

//Texture ResourceCache::GetPlayer(const Kinect& kinect)
//{
//
//}

void ResourceCache::LoadBackground(const std::string& file, const std::string& id)
{
   mBackgrounds[id] = { id, LoadTexture(file) };
}

void ResourceCache::LoadSprite(const std::vector<std::string>& files, const std::string& id)
{
   std::vector<SDL_Surface*> textures;

   for (const auto& file : files)
   {
      textures.push_back(LoadTexture(file));
   }

   mSprites[id] = { id, textures };
}

SDL_Surface* ResourceCache::LoadTexture(const std::string& file)
{
   SDL_Surface* img_loaded = IMG_Load(file.c_str());
   if (!img_loaded) {
      throw "Failed to load texture";
   }

   SDL_Surface* img_compat = SDL_DisplayFormat(img_loaded);
   if (!img_compat) {
      throw "Failed to convert animation frame to display format";
   }
   SDL_FreeSurface(img_loaded);
   img_loaded = nullptr;

   mSurfaceCache.push_back(img_compat);
   return img_compat;
}
