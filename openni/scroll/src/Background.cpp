#include "Background.h"
#include "BackgroundResource.h"
#include "Utils.hpp"

Background::Background(const BackgroundResource& res)
   : mXScreen(SDL_GetVideoSurface()->w)
   , mYScreen(SDL_GetVideoSurface()->h)
//, mLastBgUpdateTime(0) // TODO: Move this into Background class
{
   SetResourceId(res.GetId());
   SetSize(res.GetSize());
   SetZOrder(ZOrder::zo_Background);
}

Background::~Background()
{

}

void Background::Update(const int elapsed_time)
{
//   if ((game_time - mLastBgUpdateTime) < BACKGROUND_UPDATE_DELTA) {
//      return;
//   }
//
//   mLastBgUpdateTime = game_time;
}

//void Background::SetScreenResolution(const int x_res, const int y_res)
//{
//   mXScreen = x_res;
//   mYScreen = y_res;
//}

void Background::ScrollLeft(const int speed)
{
   // Scrolling left means walking forward.

   if (std::abs(GetPosition().X - mXScreen - speed) >= GetSize().Width) {
      return;
   }

   SetPosition({ GetPosition().X - speed, GetPosition().Y });
}

void Background::ScrollRight(const int speed)
{
   // Scrolling right means walking backward.

   if ((GetPosition().X + speed) >= 0) {
      return;
   }

   SetPosition({ GetPosition().X + speed, GetPosition().Y });
}
