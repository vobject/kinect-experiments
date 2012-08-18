#ifndef GL_NORES_RENDERER_HPP
#define GL_NORES_RENDERER_HPP

#include "Renderer.hpp"

struct Size;
struct SDL_Surface;

class GlNoRes : public Renderer
{
public:
   GlNoRes(Size res);
   virtual ~GlNoRes();

   GlNoRes(const GlNoRes&) = delete;
   GlNoRes& operator=(const GlNoRes&) = delete;

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

#endif // GL_NORES_RENDERER_HPP
