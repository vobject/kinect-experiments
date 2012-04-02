#ifndef RENDERER_H
#define RENDERER_H

#include <memory>
#include <list>

class SdlWindow;
class SceneObject;

class Renderer
{
public:
   Renderer(std::shared_ptr<SdlWindow> window);
   virtual ~Renderer();

   virtual void PreRender();
   virtual void Render(const std::list<std::shared_ptr<SceneObject>>& objects);
   virtual void PostRender();

private:
   std::shared_ptr<SdlWindow> mWindow;

   Renderer(const Renderer&);
   const Renderer& operator=(const Renderer&);
};

#endif // RENDERER_H
