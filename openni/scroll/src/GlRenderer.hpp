#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include "Renderer.hpp"

class ResourceCache;

class SDL_Surface;

class GlRenderer : public Renderer
{
public:
   GlRenderer(const std::shared_ptr<ResourceCache>& res);
   virtual ~GlRenderer();

   GlRenderer(const GlRenderer&) = delete;
   GlRenderer& operator=(const GlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;
   void Render(const std::shared_ptr<Background>& bg) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::list<std::shared_ptr<Sprite>>& objects) override;

private:
//   bool ObjectOnScreen(const std::shared_ptr<Sprite>& obj) const;
   void RenderSprite(const std::shared_ptr<Sprite>& obj) const;

   std::shared_ptr<ResourceCache> mResCache;

   SDL_Surface* mScreen;
};

#endif // GL_RENDERER_HPP
