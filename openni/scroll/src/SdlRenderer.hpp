#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "Renderer.hpp"

class ResourceCache;

struct SDL_Surface;

class SdlRenderer : public Renderer
{
public:
   SdlRenderer(const std::shared_ptr<ResourceCache>& res);
   virtual ~SdlRenderer();

   SdlRenderer(const SdlRenderer&) = delete;
   SdlRenderer& operator=(const SdlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;
   void Render(const std::shared_ptr<Background>& bg) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::shared_ptr<Enemy>& enemy) override;
   void Render(const std::list<std::shared_ptr<Sprite>>& objects) override;

private:
//   bool ObjectOnScreen(const std::shared_ptr<Sprite>& obj) const;
   void RenderSprite(const std::shared_ptr<Sprite>& obj) const;

   std::shared_ptr<ResourceCache> mResCache;

   // Writing to the video surface is ok since we use double buffering.
   SDL_Surface* mScreen = nullptr;
};

#endif // SDL_RENDERER_HPP
