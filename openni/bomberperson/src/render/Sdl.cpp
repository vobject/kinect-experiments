#include "Sdl.hpp"
#include "../game/Field.hpp"
#include "../game/Cell.hpp"
#include "../game/Player.hpp"
#include "../game/Bomb.hpp"
#include "../game/Explosion.hpp"
#include "../resource/ResourceCache.hpp"
#include "../utils/Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

Sdl::Sdl(const Size res)
{
   if (0 > SDL_Init(SDL_INIT_VIDEO)) {
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit);

   const auto screen = SDL_SetVideoMode(res.Width,
                                        res.Height,
                                        32,
                                        SDL_ANYFORMAT |
                                           SDL_SWSURFACE |
                                           SDL_DOUBLEBUF |
                                           SDL_RESIZABLE);
   if (!screen) {
      throw "SDL_SetVideoMode() failed.";
   }

   // The return value of SDL_SetVideoMode() (-> screen) should not be freed
   //  by the caller. The man page tells us to rely on SDL_Quit() to do this.

   // TODO: Calculate the size for each renderable object type and
   //  pass the sizes into ResourceCache, so it can scale the resources
   //  at load time.
   // ---> This idea does not work! Instead introduce some sort of
   //  scaled-texture-cache inside the renderer class!

   mResCache = std::make_shared<ResourceCache>();
}

Sdl::~Sdl()
{

}

void Sdl::PreRender()
{
   // Screen size might have changed.
   mScreen = SDL_GetVideoSurface();

   const auto black = SDL_MapRGB(mScreen->format, 0x00, 0x00, 0x00);
   SDL_FillRect(mScreen, NULL, black);
}

void Sdl::PostRender()
{
   SDL_Flip(mScreen);
}

void Sdl::Render(const std::shared_ptr<Field>& field)
{
   const auto pos = field->GetPosition();
   const auto size = field->GetSize();
   const auto frame = GetScaledSurface(*field);

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_BlitSurface(frame, NULL, mScreen, &rect);
}

void Sdl::Render(const std::shared_ptr<Cell>& cell)
{
   const auto pos = cell->GetPosition();
   const auto size = cell->GetSize();
   const auto type = cell->GetType();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };

   if ((CellType::IndestructibleWall == type) ||
       (CellType::DestructibleWall == type))
   {
      const auto frame = GetScaledSurface(*cell);
      SDL_BlitSurface(frame, NULL, mScreen, &rect);
      return;
   }

   if (!cell->HasItem()) {
      return;
   }

   SDL_Rect item_rect = { static_cast<Sint16>(pos.X),
                          static_cast<Sint16>(pos.Y),
                          static_cast<Uint16>(10),
                          static_cast<Uint16>(10) };
   int item_color = 0;

   switch (cell->GetItem())
   {
      case CellItem::Speed:
         item_color = 0xff0000;
         break;
      case CellItem::BombRange:
         item_color = 0x00ff00;
         break;
      case CellItem::BombSupply:
         item_color = 0x0000ff;
         break;
      default:
         break;
   }
   SDL_FillRect(mScreen, &item_rect, item_color);
}

void Sdl::Render(const std::shared_ptr<Player>& player)
{
   const auto pos = player->GetPosition();
   const auto size = player->GetSize();
   const auto frame = GetScaledSurface(*player);

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_BlitSurface(frame, NULL, mScreen, &rect);
}

void Sdl::Render(const std::shared_ptr<Bomb>& bomb)
{
   const auto pos = bomb->GetPosition();
   const auto size = bomb->GetSize();
   const auto frame = GetScaledSurface(*bomb);

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_BlitSurface(frame, NULL, mScreen, &rect);
}

void Sdl::Render(const std::shared_ptr<Explosion>& explosion)
{
   const auto pos = explosion->GetPosition();
   const auto size = explosion->GetSize();
   const auto frame = GetScaledSurface(*explosion);

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_BlitSurface(frame, NULL, mScreen, &rect);
}

void Sdl::Render(const std::shared_ptr<SceneObject>& obj)
{
   const Point pos = obj->GetPosition();
   const Size size = obj->GetSize();

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_FillRect(mScreen, &rect, 0xffffff);
}

SDL_Surface* Sdl::GetScaledSurface(const SceneObject& obj)
{
   const auto cached_surface = mScaledSurfaces[obj.GetResourceId()];
   if (cached_surface) {
      return cached_surface;
   }

   // TODO: fix frame index!
   const auto frame = mResCache->GetSprite(obj.GetResourceId()).GetFrame(0);
   if (!frame) {
      throw "No texture associated with resource id.";
   }

   const auto obj_size = obj.GetSize();
   auto zoomed_frame = frame;
   if ((obj_size.Width != frame->w) || (obj_size.Height != frame->h))
   {
      // Stretch the image to the appropriate size.
      const double x_zoom = static_cast<double>(obj.GetSize().Width) / frame->w;
      const double y_zoom = static_cast<double>(obj.GetSize().Height) / frame->h;
      zoomed_frame = zoomSurface(frame, x_zoom, y_zoom, 1);
   }

   const auto colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   mScaledSurfaces[obj.GetResourceId()] = zoomed_frame;
   return zoomed_frame;
}
