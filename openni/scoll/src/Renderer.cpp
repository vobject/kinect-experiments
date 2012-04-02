#include "Renderer.h"
#include "SdlWindow.h"
#include "SceneObject.h"
#include "Log.h"

#include <string>

Renderer::Renderer(std::shared_ptr<SdlWindow> window)
   : mWindow(window)
{

}

Renderer::~Renderer()
{

}

void Renderer::PreRender()
{
   SDL_FillRect(mWindow->mSurface, NULL, 0x00ff0000);

   // TODO: Lock mSurface?
}

void Renderer::Render(const std::list<std::shared_ptr<SceneObject>>& objects)
{
   for (auto& obj : objects)
   {
      if (obj->IsVisible())
      {
         // TODO: Get objects resources from resource manager
         // TODO: Draw the objects resources in its current state to mSurface

         const std::string resource = obj->GetResource();

         if (resource == "Rectangle")
         {
            SDL_Rect rect = { (Sint16)(obj->GetXPos() - (obj->GetWidth() / 2)),
                              (Sint16)(obj->GetYPos() - (obj->GetHeight() / 2)),
                              (Uint16)obj->GetWidth(),
                              (Uint16)obj->GetHeight() };

            SDL_FillRect(mWindow->mSurface, &rect, 0);
         }
      }
   }
}

void Renderer::PostRender()
{
   // TODO: Unlock mSurface?
}
