#include "Background.h"

Background::Background()
{
   SetResourceId("smw");
   SetZOrder(zo_Background);
   SetVisible(true);
}

Background::~Background()
{

}

void Background::Update(const int elapsed_time)
{

}

void Background::SetScreenSize(const int x_res, const int y_res)
{
   mXScreen = x_res;
   mYScreen = y_res;
}

void Background::ScrollLeft(const int speed)
{
   // Scrolling left means walking forward.

   if (std::abs(GetXPos() - mXScreen - speed) >= GetWidth()) {
      return;
   }

   SetPos(GetXPos() - speed, GetYPos());
}

void Background::ScrollRight(const int speed)
{
   // Scrolling right means walking backward.

   if ((GetXPos() + speed) >= 0) {
      return;
   }

   SetPos(GetXPos() + speed, GetYPos());
}
