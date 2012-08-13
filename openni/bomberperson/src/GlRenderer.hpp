#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include "Renderer.hpp"

struct SDL_Surface;

class GlRenderer : public Renderer
{
public:
   GlRenderer();
   virtual ~GlRenderer();

   GlRenderer(const GlRenderer&) = delete;
   GlRenderer& operator=(const GlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;

   void Render(const std::shared_ptr<Field>& field) override;
   void Render(const std::shared_ptr<Cell>& cell) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::shared_ptr<Bomb>& bomb) override;
   void Render(const std::shared_ptr<Explosion>& explosion) override;
   void Render(const std::shared_ptr<SceneObject>& obj) override;

private:
   SDL_Surface* mScreen = nullptr;
};

#endif // GL_RENDERER_HPP
