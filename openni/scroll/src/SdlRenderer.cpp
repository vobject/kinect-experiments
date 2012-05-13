#include "SdlRenderer.hpp"
#include "Kinect.hpp"
#include "ResourceCache.hpp"
#include "Sprite.h"
#include "Background.h"
#include "Player.h"
#include "Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

#include <string>

SdlRenderer::SdlRenderer(const std::shared_ptr<ResourceCache>& res)
   : mResCache(res)
   , mScreen(SDL_GetVideoSurface())
{
   // This is the surface that we will write to before swapping it.
   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   mScreen->w, mScreen->h,
                                   mScreen->format->BitsPerPixel,
                                   0, 0, 0, 0);
   if (!mSurface) {
      throw "SDL_CreateRGBSurface() failed.";
   }
}

SdlRenderer::~SdlRenderer()
{
   SDL_FreeSurface(mSurface);
}

void SdlRenderer::PreRender()
{
   const auto black = SDL_MapRGB(mSurface->format, 0x00, 0x00, 0x00);
   SDL_FillRect(mSurface, NULL, black);
}

void SdlRenderer::PostRender()
{

   SDL_BlitSurface(mSurface, NULL, mScreen, NULL);
   SDL_Flip(mScreen);
}

void SdlRenderer::Render(const std::shared_ptr<Background>& bg)
{
   if (!bg->IsVisible()) {
      return;
   }

   const auto frame = mResCache->GetBackground(bg->GetResourceId()).GetFrame();
   if (!frame) {
      throw "No texture associated with background";
   }

   SDL_Rect rect = { (Sint16)bg->GetPosition().X,
                     (Sint16)bg->GetPosition().Y,
                     (Uint16)bg->GetSize().Width,
                     (Uint16)bg->GetSize().Height };

   SDL_BlitSurface(frame, NULL, mSurface, &rect);
}

void SdlRenderer::Render(const std::shared_ptr<Player>& player)
{
   //  TODO: Center the Actor with its XCenter to the middle of the window

   if (!player->IsVisible()) {
      return;
   }

   const auto frame = player->GetFrame();
   if (!frame) {
      throw "No frame associated with player";
   }

   const double x_zoom = static_cast<double>(player->GetSize().Width) / frame->w;
   const double y_zoom = static_cast<double>(player->GetSize().Height) / frame->h;
   SDL_Surface* zoomed_frame = zoomSurface(frame, x_zoom, y_zoom, 0);

   const auto colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   SDL_Rect rect = { (Sint16)player->GetPosition().X,
                     (Sint16)player->GetPosition().Y,
                     (Uint16)player->GetSize().Width,
                     (Uint16)player->GetSize().Height };

   SDL_BlitSurface(zoomed_frame, NULL, mSurface, &rect);
   SDL_FreeSurface(zoomed_frame);
}

void SdlRenderer::Render(const std::list<std::shared_ptr<Sprite>>& objects)
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
//         SDL_Rect rect = { (Sint16)obj->GetPosition().X, (Sint16)obj->GetPosition().Y,
//                           (Uint16)obj->GetSize().Width, (Uint16)obj->GetSize().Height };
//         SDL_FillRect(mWindow->mSurface, &rect, 0xff55ff);
      }
      else
      {
         RenderSprite(obj);
      }
   }
}

void SdlRenderer::RenderSprite(const std::shared_ptr<Sprite>& obj) const
{
   const auto frame = mResCache->GetSprite(obj->GetResourceId()).GetFrame(obj->GetCurrentFrame());
   if (!frame) {
      throw "No frame associated with sprite";
   }

   const double x_zoom = static_cast<double>(obj->GetSize().Width) / frame->w;
   const double y_zoom = static_cast<double>(obj->GetSize().Height) / frame->h;
   SDL_Surface* zoomed_frame = zoomSurface(frame, x_zoom, y_zoom, 0);

   const auto colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   SDL_Rect rect = { (Sint16)obj->GetPosition().X,
                     (Sint16)obj->GetPosition().Y,
                     (Uint16)obj->GetSize().Width,
                     (Uint16)obj->GetSize().Height };

   SDL_BlitSurface(zoomed_frame, NULL, mSurface, &rect);
   SDL_FreeSurface(zoomed_frame);
}
