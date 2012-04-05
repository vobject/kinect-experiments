#include "Actor.h"
#include "UserData.h"

#include <XnTypes.h>

Actor::Actor()
   : mXCenter(0)
   , mYCenter(0)
{
   SetResourceId("actor");
   SetPos(0, 0);
   SetSize(640, 480);
   SetZOrder(zo_Layer_2);
   SetVisible(false);
}

Actor::~Actor()
{

}

void Actor::Update(const int elapsed_time)
{

}

void Actor::Update(const UserData& user)
{
   const int x_center = user[XN_SKEL_TORSO].X;
   const int y_center = user[XN_SKEL_TORSO].Y;

   if ((x_center != 0) && (y_center != 0))
   {
      mXCenter = user[XN_SKEL_TORSO].X;
      mYCenter = user[XN_SKEL_TORSO].Y;
      SetVisible(true);
   }
}

int Actor::GetXCenter()
{
   return mXCenter;
}

int Actor::GetYCenter()
{
   return mYCenter;
}
