#ifndef GL_RENDERER_HPP
#define GL_RENDERER_HPP

#include "Renderer.hpp"

class SDL_Surface;

class GlRenderer : public Renderer
{
public:
   GlRenderer();
   virtual ~GlRenderer();

   GlRenderer(const GlRenderer&) = delete;
   GlRenderer& operator=(const GlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;
   void Render(const std::shared_ptr<KinectBackground>& bg) override;
   void Render(const std::shared_ptr<PaintStatus>& status) override;

private:
   SDL_Surface* mScreen;
};

#endif // GL_RENDERER_HPP
