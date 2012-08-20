#include "SdlRenderer.hpp"
#include "../game/Match.hpp"
#include "../game/Arena.hpp"
#include "../game/Cell.hpp"
#include "../game/Wall.hpp"
#include "../game/Extra.hpp"
#include "../game/Bomb.hpp"
#include "../game/Explosion.hpp"
#include "../game/Player.hpp"
#include "../resource/ResourceCache.hpp"
#include "../utils/Utils.hpp"

#include <SDL.h>
#include <SDL_rotozoom.h>

SdlRenderer::SdlRenderer(const Size res)
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
   mClearColor = SDL_MapRGB(screen->format, 0, 0, 0);

   // The return value of SDL_SetVideoMode() (-> screen) should not be freed
   //  by the caller. The man page tells us to rely on SDL_Quit() to do this.

   // TODO: Calculate the size for each renderable object type and
   //  pass the sizes into ResourceCache, so it can scale the resources
   //  at load time.
   // ---> This idea does not work! Instead introduce some sort of
   //  scaled-texture-cache inside the renderer class!

   mResCache = std::make_shared<ResourceCache>();
}

SdlRenderer::~SdlRenderer()
{
   for (auto& kev_value : mScaledSurfaces) {
      SDL_FreeSurface(kev_value.second);
   }
}

void SdlRenderer::PreRender()
{
   // Screen size might have changed.
   mScreen = SDL_GetVideoSurface();

   SDL_FillRect(mScreen, NULL, mClearColor);
}

void SdlRenderer::PostRender()
{
   SDL_Flip(mScreen);
}

void SdlRenderer::Render(const std::shared_ptr<Match>& match)
{
   // FIXME: Match is not a SceneObject! Is that a design problem?
   // Who should orchestrate the rendering of the various objects?
   // Currently the renderer is responsible for it.

   // TODO: Get Match statistics and render them to the screen.

   Render(match->GetArena());

   for (const auto& player : match->GetPlayers())
   {
      Render(player);
   }
}

void SdlRenderer::Render(const std::shared_ptr<Arena>& arena)
{
   // Use the generic render method for SceneObjects.
   Render(std::static_pointer_cast<SceneObject>(arena));

   for (const auto& cell : arena->GetCells())
   {
      Render(cell);
   }
}

void SdlRenderer::Render(const std::shared_ptr<Cell>& cell)
{
   Render(std::static_pointer_cast<SceneObject>(cell));

   if (cell->HasWall()) {
      Render(cell->GetWall());
      return;
   }

   if (cell->HasExtra()) {
      Render(cell->GetExtra());
   }

   if (cell->HasBomb()) {
      Render(cell->GetBomb());
   }

   if (cell->HasExplosion()) {
      Render(cell->GetExplosion());
   }
}

void SdlRenderer::Render(const std::shared_ptr<Wall>& wall)
{
   Render(std::static_pointer_cast<SceneObject>(wall));
}

void SdlRenderer::Render(const std::shared_ptr<Extra>& extra)
{
   Render(std::static_pointer_cast<SceneObject>(extra));
}

void SdlRenderer::Render(const std::shared_ptr<Bomb>& bomb)
{
   Render(std::static_pointer_cast<SceneObject>(bomb));
}

void SdlRenderer::Render(const std::shared_ptr<Explosion>& explosion)
{
   Render(std::static_pointer_cast<SceneObject>(explosion));
}

void SdlRenderer::Render(const std::shared_ptr<Player>& player)
{
   Render(std::static_pointer_cast<SceneObject>(player));
}

void SdlRenderer::Render(const std::shared_ptr<SceneObject>& obj)
{
   const auto pos = obj->GetPosition();
   const auto size = obj->GetSize();
   const auto frame = GetScaledSurface(*obj);

   SDL_Rect rect = { static_cast<Sint16>(pos.X),
                     static_cast<Sint16>(pos.Y),
                     static_cast<Uint16>(size.Width),
                     static_cast<Uint16>(size.Height) };
   SDL_BlitSurface(frame, NULL, mScreen, &rect);
}

SDL_Surface* SdlRenderer::GetScaledSurface(const SceneObject& obj)
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

   // Stretch the image to the appropriate size.
   const double x_zoom = static_cast<double>(obj.GetSize().Width) / frame->w;
   const double y_zoom = static_cast<double>(obj.GetSize().Height) / frame->h;
   const auto zoomed_frame = zoomSurface(frame, x_zoom, y_zoom, 1);

   const auto colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
      throw "SDL_SetColorKey failed";
   }

   mScaledSurfaces[obj.GetResourceId()] = zoomed_frame;
   return zoomed_frame;
}
