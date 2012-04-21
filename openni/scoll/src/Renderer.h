#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <list>

class SDL_Surface;

class Kinect;
class SdlWindow;
class ResourceCache;
class Sprite;
class Background;
class Player;

class Renderer
{
public:
   Renderer(const std::shared_ptr<SdlWindow>& window,
            const std::shared_ptr<ResourceCache>& res);
   virtual ~Renderer();

   Renderer(const Renderer&) = delete;
   Renderer& operator=(const Renderer&) = delete;

   virtual void PreRender();
   virtual void PostRender();
   virtual void Render(const std::shared_ptr<Background>& bg);
   virtual void Render(const std::shared_ptr<Player>& player);
   virtual void Render(const std::list<std::shared_ptr<Sprite>>& objects);

private:
//   bool ObjectOnScreen(const std::shared_ptr<Sprite>& obj) const;
   void RenderSprite(const std::shared_ptr<Sprite>& obj) const;

   std::shared_ptr<SdlWindow> mWindow;
   std::shared_ptr<ResourceCache> mResCache;
};

#endif // RENDERER_H
