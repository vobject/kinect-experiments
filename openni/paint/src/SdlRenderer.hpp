#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "Renderer.hpp"

class Point;

class SDL_Surface;

class SdlRenderer : public Renderer
{
public:
   SdlRenderer();
   virtual ~SdlRenderer();

   SdlRenderer(const SdlRenderer&) = delete;
   SdlRenderer& operator=(const SdlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;
   void Render(const std::shared_ptr<KinectBackground>& bg) override;
   void Render(const std::shared_ptr<PaintStatus>& status) override;

private:
   void DrawLine(const Point& src_pos, const Point& dest_pos, unsigned int color);
   void DrawPixel(const Point& pos, unsigned int color);

   SDL_Surface* mScreen;
//   SDL_Surface* mSurface = nullptr;
};

#endif // SDL_RENDERER_HPP
