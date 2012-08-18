#ifndef SDL_NORES_RENDERER_HPP
#define SDL_NORES_RENDERER_HPP

#include "Renderer.hpp"

struct Size;
struct SDL_Surface;

class SdlNoRes : public Renderer
{
public:
   SdlNoRes(Size res);
   virtual ~SdlNoRes();

   SdlNoRes(const SdlNoRes&) = delete;
   SdlNoRes& operator=(const SdlNoRes&) = delete;

   void PreRender() override;
   void PostRender() override;

   void Render(const std::shared_ptr<Field>& field) override;
   void Render(const std::shared_ptr<Cell>& cell) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::shared_ptr<Bomb>& bomb) override;
   void Render(const std::shared_ptr<Explosion>& explosion) override;
   void Render(const std::shared_ptr<SceneObject>& obj) override;

private:
//   void DrawLine(const Point& src_pos, const Point& dest_pos, unsigned int color);
//   void DrawPixel(const Point& pos, unsigned int color);

   // Writing to the video surface is ok since we use double buffering.
   SDL_Surface* mScreen = nullptr;
};

#endif // SDL_NORES_RENDERER_HPP
