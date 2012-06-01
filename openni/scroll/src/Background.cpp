#include "Background.h"
#include "BackgroundResource.h"
#include "Utils.hpp"

Background::Background(const BackgroundResource& res)
   : mXScreen(SDL_GetVideoSurface()->w)
   , mYScreen(SDL_GetVideoSurface()->h)
{
   SetResourceId(res.GetId());
   SetSize(res.GetSize());
   SetZOrder(ZOrder::zo_Background);

   // TODO: Background must have a "buttom" coordinate.
}

Background::~Background()
{

}

void Background::Update(const int elapsed_time)
{
   mElapsedTimeSinceLastScroll += elapsed_time;

//   if ((game_time - mLastBgUpdateTime) < BACKGROUND_UPDATE_DELTA) {
//      return;
//   }
//
//   mLastBgUpdateTime = game_time;
}

void Background::ScrollLeft(const int speed)
{
   if (mElapsedTimeSinceLastScroll < MILLISECONDS_PER_SCROLL) {
      return;
   }
   mElapsedTimeSinceLastScroll = 0_ms;

   // Scrolling right means walking backward.

   if ((GetPosition().X + speed) >= 0) {
      return;
   }

   SetPosition({ GetPosition().X + speed, GetPosition().Y });
}

void Background::ScrollRight(const int speed)
{
   if (mElapsedTimeSinceLastScroll < MILLISECONDS_PER_SCROLL) {
      return;
   }
   mElapsedTimeSinceLastScroll = 0_ms;

   // Scrolling left means walking forward.

   if (std::abs(GetPosition().X - mXScreen - speed) >= GetSize().Width) {
      return;
   }

   SetPosition({ GetPosition().X - speed, GetPosition().Y });
}
