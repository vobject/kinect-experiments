#include "View.h"
#include "Renderer.h"
#include "SceneObject.h"
#include "Log.h"

#include <algorithm>

template<class T>
struct SortBy_SharedPtr_Content
{
   bool operator()(const std::shared_ptr<T>& lhs, const std::shared_ptr<T>& rhs) const
   {
      return *lhs < *rhs;
   }
};

View::View(const std::shared_ptr<Renderer>& renderer)
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

//void View::SetBackground(const std::shared_ptr<SceneObject>& obj)
//{
//   mBackground = obj;
//}
//
//void View::RemoveBackground()
//{
//   mBackground = nullptr;
//}
//
//void View::SetActor(const std::shared_ptr<SceneObject>& obj)
//{
//   mActor = obj;
//}
//
//void View::RemoveActor()
//{
//   mActor = nullptr;
//}

void View::AddObject(const std::shared_ptr<SceneObject>& obj)
{
   mSceneObjects.push_front(obj);
}

void View::RemoveObject(const std::shared_ptr<SceneObject>& obj)
{
   mSceneObjects.remove(obj);
}
