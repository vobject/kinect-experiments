#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <list>

class Kinect;
class SdlWindow;
class ResourceCache;
class Sprite;
class Background;
class Actor;

class Renderer
{
public:
   Renderer(const std::shared_ptr<SdlWindow>& window,
             const std::shared_ptr<ResourceCache>& res,
             const std::shared_ptr<Kinect>& kinect);
   virtual ~Renderer();

   virtual void PreRender();
   virtual void PostRender();
   virtual void Render(const std::shared_ptr<Background>& bg);
   virtual void Render(const std::shared_ptr<Actor>& actor);
   virtual void Render(const std::list<std::shared_ptr<Sprite>>& objects);

private:
//   bool ObjectOnScreen(const std::shared_ptr<Sprite>& obj) const;
   void RenderSprite(const std::shared_ptr<Sprite>& obj) const;

   std::shared_ptr<SdlWindow> mWindow;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Kinect> mKinect;

   Renderer(const Renderer&);
   const Renderer& operator=(const Renderer&);
};

#endif // RENDERER_H
