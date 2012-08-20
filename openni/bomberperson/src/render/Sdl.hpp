#ifndef SDL_RENDERER_HPP
#define SDL_RENDERER_HPP

#include "Renderer.hpp"

#include <map>
#include <memory>

class ResourceCache;
struct Size;
struct SDL_Surface;

class Sdl : public Renderer
{
public:
   Sdl(Size res);
   virtual ~Sdl();

   Sdl(const Sdl&) = delete;
   Sdl& operator=(const Sdl&) = delete;

   void PreRender() override;
   void PostRender() override;

   void Render(const std::shared_ptr<Field>& field) override;
   void Render(const std::shared_ptr<Cell>& cell) override;
   void Render(const std::shared_ptr<Player>& player) override;
   void Render(const std::shared_ptr<Bomb>& bomb) override;
   void Render(const std::shared_ptr<Explosion>& explosion) override;
   void Render(const std::shared_ptr<SceneObject>& obj) override;

private:
   SDL_Surface* GetScaledSurface(const SceneObject& obj);

   // Writing to the video surface is ok since we use double buffering.
   SDL_Surface* mScreen = nullptr;

   // Must be initialized after the video system has been set up.
   std::shared_ptr<ResourceCache> mResCache = nullptr;

   std::map<std::string, SDL_Surface*> mScaledSurfaces;
};

#endif // SDL_RENDERER_HPP
