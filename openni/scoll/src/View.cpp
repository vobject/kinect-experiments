#include "View.h"
#include "SceneObject.h"
#include "Log.h"

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
   // TODO: Sort by z-order
//   m_ScreenElements.sort(SortBy_SharedPtr_Content<IScreenElement>());

   for (auto& obj : mSceneObjects)
   {
      if (obj->IsVisible())
      {
         obj->Render();
      }
   }
}
