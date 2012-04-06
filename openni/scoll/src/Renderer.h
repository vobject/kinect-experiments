#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <list>

class Kinect;
class SdlWindow;
class ResourceCache;
class SceneObject;
class Background;
class Actor;

class Renderer
{
public:
   Renderer(std::shared_ptr<SdlWindow> window, std::shared_ptr<ResourceCache> resource, std::shared_ptr<Kinect> kinect);
   virtual ~Renderer();

   virtual void PreRender();
   virtual void Render(const std::shared_ptr<Background>& bg);
   virtual void Render(const std::shared_ptr<Actor>& actor);
   virtual void Render(const std::list<std::shared_ptr<SceneObject>>& objects);
   virtual void PostRender();

private:
   std::shared_ptr<SdlWindow> mWindow;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Kinect> mKinect;

   Renderer(const Renderer&);
   const Renderer& operator=(const Renderer&);
};

#endif // RENDERER_H
