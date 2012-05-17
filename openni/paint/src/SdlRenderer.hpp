#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "Renderer.hpp"

class Nui;
class Point;

class SDL_Surface;

class SdlRenderer : public Renderer
{
public:
   SdlRenderer(const Nui& kinect);
   virtual ~SdlRenderer();

   SdlRenderer(const SdlRenderer&) = delete;
   SdlRenderer& operator=(const SdlRenderer&) = delete;

   void PreRender() override;
   void PostRender() override;
   void Render(const std::shared_ptr<NuiBackground>& bg) override;
   void Render(const std::shared_ptr<PaintStatus>& status) override;

private:
   void DrawLine(const Point& src_pos, const Point& dest_pos, unsigned int color);
   void DrawPixel(const Point& pos, unsigned int color);

   // Writing directly to the video surface is ok since we use double buffering.
   SDL_Surface* mScreen = nullptr;
   // Will only be used if application window resolution != Kinect resolution.
   SDL_Surface* mBgSurface = nullptr;
};

#endif // SDL_RENDERER_HPP
