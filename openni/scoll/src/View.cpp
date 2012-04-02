#include "View.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "Log.h"

template<class T>
struct SortBy_SharedPtr_Content
{
   bool operator()(const std::shared_ptr<T>& lhs, const std::shared_ptr<T>& rhs) const
   {
      return *lhs < *rhs;
   }
};

View::View(std::shared_ptr<Renderer> renderer)
   : mRenderer(renderer)
{

}

View::~View()
{

}

void View::Update(const int elapsed_time)
{
   for (auto& obj : mSceneObjects)
   {
       obj->Update(elapsed_time);
   }
}

void View::Render()
{
   mSceneObjects.sort(SortBy_SharedPtr_Content<SceneObject>());

   mRenderer->PreRender();
   mRenderer->Render(mSceneObjects);
   mRenderer->PostRender();
}

void View::AddObject(std::shared_ptr<SceneObject> obj)
{
   mSceneObjects.push_front(obj);
}

void View::RemoveObject(std::shared_ptr<SceneObject> obj)
{
   mSceneObjects.remove(obj);
}
