#ifndef VIEW_H
#define VIEW_H

#include <memory>
#include <list>

class Renderer;
class SceneObject;

class View
{
public:
   View(std::shared_ptr<Renderer> renderer);
   virtual ~View();

   virtual void Update(int elapsed_time);
   virtual void Render();

private:
   std::shared_ptr<Renderer> mRenderer;
   std::list<std::shared_ptr<SceneObject>> mSceneObjects;

   View(const View&);
   const View& operator=(const View&);
};

#endif // VIEW_H
