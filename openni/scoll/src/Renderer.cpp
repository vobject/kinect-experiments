#include "Renderer.h"
#include "Kinect.h"
#include "SdlWindow.h"
#include "ResourceCache.h"
#include "SceneObject.h"
#include "Log.h"

#include <SDL.h>

#include <string>

Renderer::Renderer(
   std::shared_ptr<SdlWindow> window,
   std::shared_ptr<ResourceCache> resource,
   std::shared_ptr<Kinect> kinect
)
   : mWindow(window)
   , mResCache(resource)
   , mKinect(kinect)
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
      if (!obj->IsVisible()) {
         continue;
      }

      // TODO: Get objects resources from resource manager
      // TODO: Draw the objects resources in its current state to mSurface

      SDL_Rect rect = { (Sint16)obj->GetXPos(), (Sint16)obj->GetYPos(),
                        (Uint16)obj->GetWidth(), (Uint16)obj->GetHeight() };
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

   const auto users = mKinect->GetUsers();
   if (users.empty()) {
      return;
   }

   const auto scene_meta = mKinect->GetUserPixels(users[0]);

   SDL_LockSurface(mWindow->mSurface);
   XnRGB24Pixel* screen_buf = (XnRGB24Pixel*)mWindow->mSurface->pixels;
   const XnRGB24Pixel* rgb_buf = mKinect->GetImageData();
   const XnLabel* label_buf = scene_meta->Data();

   const int pixel_cnt = mKinect->GetYRes() * mKinect->GetXRes();
   const XnUserID current_id = users[0].GetId();

   for (int i = 0; i < pixel_cnt; i++, screen_buf++, rgb_buf++, label_buf++)
   {
      if (*label_buf == current_id)
      {
         screen_buf->nRed = rgb_buf->nBlue;
         screen_buf->nGreen = rgb_buf->nGreen;
         screen_buf->nBlue = rgb_buf->nRed;
      }
   }
   SDL_UnlockSurface(mWindow->mSurface);
}

void Renderer::PostRender()
{
   // TODO: Unlock mSurface?
}
