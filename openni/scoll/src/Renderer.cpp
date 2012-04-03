#include "Renderer.h"
#include "SdlWindow.h"
#include "ResourceCache.h"
#include "SceneObject.h"
#include "Log.h"

#include <SDL.h>

#include <string>

Renderer::Renderer(std::shared_ptr<SdlWindow> window, std::shared_ptr<ResourceCache> resource)
   : mWindow(window)
   , mResCache(resource)
{

}

Renderer::~Renderer()
{

}

void Renderer::PreRender()
{
   SDL_FillRect(mWindow->mSurface, NULL, 0xff0000);

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

         SDL_Rect rect = { (Sint16)(obj->GetXPos() - (obj->GetWidth() / 2)),
                           (Sint16)(obj->GetYPos() - (obj->GetHeight() / 2)),
                           (Uint16)obj->GetWidth(),
                           (Uint16)obj->GetHeight() };
         const std::string resource_id = obj->GetResourceId();

         if (resource_id == "Rectangle")
         {
            SDL_FillRect(mWindow->mSurface, &rect, 0);
         }
         else
         {
            SDL_Surface* res = mResCache->GetResource(resource_id);
            SDL_BlitSurface(res, NULL, mWindow->mSurface, &rect);
         }
      }
   }
}

void Renderer::PostRender()
{
   // TODO: Unlock mSurface?
}
