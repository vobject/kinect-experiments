#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "Renderer.hpp"

#include <map>
#include <memory>
#include <string>

class ResourceCache;
struct Size;
struct SDL_Surface;

class SdlRenderer : public Renderer
{
public:
   SdlRenderer(Size res);
   virtual ~SdlRenderer();

   SdlRenderer(const SdlRenderer&) = delete;
   SdlRenderer& operator=(const SdlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;

   void Render(const std::shared_ptr<Match>& match) override;
   void Render(const std::shared_ptr<Arena>& field) override;
   void Render(const std::shared_ptr<Cell>& cell) override;
   void Render(const std::shared_ptr<Wall>& explosion) override;
   void Render(const std::shared_ptr<Extra>& bomb) override;
   void Render(const std::shared_ptr<Bomb>& bomb) override;
   void Render(const std::shared_ptr<Explosion>& explosion) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::shared_ptr<SceneObject>& obj) override;

private:
   SDL_Surface* GetScaledSurface(const std::string& cache_name,
                                 const Size& size,
                                 SDL_Surface* frame);

   // The screen will be cleared to this color before each render cycle.
   int mClearColor; // Will be initilized after the screen was set up in ctor.

   // Writing to the video surface is ok since we use double buffering.
   SDL_Surface* mScreen = nullptr;

   // Must be initialized after the video system has been set up.
   std::shared_ptr<ResourceCache> mResCache = nullptr;

   std::map<std::string, SDL_Surface*> mScaledSurfaces;
};

#endif // SDL_RENDERER_HPP
