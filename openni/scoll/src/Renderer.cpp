#include "Renderer.h"
#include "Kinect.h"
#include "SdlWindow.h"
#include "ResourceCache.h"
#include "Sprite.h"
#include "Background.h"
#include "Player.h"
#include "Utils.h"

#include <SDL.h>
#include <SDL_rotozoom.h>

#include <string>
#include <cassert>

Renderer::Renderer(
   const std::shared_ptr<SdlWindow>& window,
   const std::shared_ptr<ResourceCache>& res
)
   : mWindow(window)
   , mResCache(res)
{

}

Renderer::~Renderer()
{

}

void Renderer::PreRender()
{
   SDL_FillRect(mWindow->mSurface, NULL, 0x0000b5);

   // TODO: Lock mSurface?
}

void Renderer::PostRender()
{
   // TODO: Unlock mSurface?
}

void Renderer::Render(const std::shared_ptr<Background>& bg)
{
   if (!bg->IsVisible()) {
      return;
   }

   SDL_Rect rect = { (Sint16)bg->GetPosition().X, (Sint16)bg->GetPosition().Y,
                     (Uint16)bg->GetSize().Width, (Uint16)bg->GetSize().Height };

   const auto texture = mResCache->GetBackground(bg->GetResourceId()).GetFrame();
   if (!texture) {
      throw "No texture associated with background";
   }

   const auto bg_frame = (SDL_Surface*)texture->GetData();
   SDL_BlitSurface(bg_frame, NULL, mWindow->mSurface, &rect);
}

void Renderer::Render(const std::shared_ptr<Player>& player)
{
   //  TODO: Center the Actor with its XCenter to the middle of the window

   if (!player->IsVisible()) {
      return;
   }

   const auto orig_frame = player->GetFrame();
   const double x_zoom = static_cast<double>(player->GetSize().Width) / orig_frame->GetSize().Width;
   const double y_zoom = static_cast<double>(player->GetSize().Height) / orig_frame->GetSize().Height;
   SDL_Surface* zoomed_frame = zoomSurface(static_cast<SDL_Surface*>(orig_frame->GetData()), x_zoom, y_zoom, 0);

   const Uint32 colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   SDL_Rect rect = { (Sint16)player->GetPosition().X, (Sint16)player->GetPosition().Y,
                     (Uint16)player->GetSize().Width, (Uint16)player->GetSize().Height };
   SDL_BlitSurface(zoomed_frame, NULL, mWindow->mSurface, &rect);


//   const auto users = mKinect->GetUsers();
//   if (users.empty()) {
//      return;
//   }
//
//   const auto scene_meta = mKinect->GetUserPixels(users[0]);
//
//   SDL_LockSurface(mWindow->mSurface);
//   XnRGB24Pixel* screen_buf = (XnRGB24Pixel*)mWindow->mSurface->pixels;
//   const XnRGB24Pixel* rgb_buf = mKinect->GetImageData();
//   const XnLabel* label_buf = scene_meta->Data();
//
//   const int pixel_cnt = mKinect->GetYRes() * mKinect->GetXRes();
//   const XnUserID current_id = users[0].GetId();
//
//   for (int i = 0; i < pixel_cnt; i++, screen_buf++, rgb_buf++, label_buf++)
//   {
//      if (*label_buf == current_id)
//      {
//         screen_buf->nRed = rgb_buf->nBlue;
//         screen_buf->nGreen = rgb_buf->nGreen;
//         screen_buf->nBlue = rgb_buf->nRed;
//      }
//   }
//   SDL_UnlockSurface(mWindow->mSurface);
}

void Renderer::Render(const std::list<std::shared_ptr<Sprite>>& objects)
{
   for (const auto& obj : objects)
   {
      if (!obj->IsVisible()) {
         continue;
      }

      // TODO: Get objects resources from resource manager
      // TODO: Draw the objects resources in its current state to mSurface

      const auto res_id = obj->GetResourceId();

      if (res_id == "Rectangle")
      {
         SDL_Rect rect = { (Sint16)obj->GetPosition().X, (Sint16)obj->GetPosition().Y,
                           (Uint16)obj->GetSize().Width, (Uint16)obj->GetSize().Height };
         SDL_FillRect(mWindow->mSurface, &rect, 0xff55ff);
      }
      else
      {
         RenderSprite(obj);
      }
   }
}

void Renderer::RenderSprite(const std::shared_ptr<Sprite>& obj) const
{
   SDL_Rect rect = { (Sint16)obj->GetPosition().X, (Sint16)obj->GetPosition().Y,
                     (Uint16)obj->GetSize().Width, (Uint16)obj->GetSize().Height };
   const auto texture = mResCache->GetSprite(obj->GetResourceId()).GetFrame(obj->GetCurrentFrame());
   if (!texture) {
      throw "No texture associated with background";
   }

   const auto frame = (SDL_Surface*)texture->GetData();

   const double x_zoom = static_cast<double>(rect.w) / frame->w;
   const double y_zoom = static_cast<double>(rect.h) / frame->h;
   SDL_Surface* zoomed_frame = zoomSurface(frame, x_zoom, y_zoom, 0);

   const Uint32 colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   SDL_BlitSurface(zoomed_frame, NULL, mWindow->mSurface, &rect);
}

