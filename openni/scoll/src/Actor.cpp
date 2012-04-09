#include "Actor.h"
#include "Kinect.h"
#include "UserData.h"

Actor::Actor(const std::shared_ptr<Kinect>& kinect)
   : mXCenter(0)
   , mYCenter(0)
   , mFrame(nullptr)
{
   SetResourceId("actor");
   SetPos(0, 0);
   SetSize(kinect->GetXRes(), kinect->GetYRes());
   SetZOrder(ZOrder::zo_Layer_2);
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
   mJoints = user.GetPerspectiveJoints();

   const int x_center = mJoints[XN_SKEL_TORSO].X;
   const int y_center = mJoints[XN_SKEL_TORSO].Y;

   if (x_center && y_center)
   {
      mXCenter = mJoints[XN_SKEL_TORSO].X;
      mYCenter = mJoints[XN_SKEL_TORSO].Y;

      SetVisible(true);
   }
}

bool Actor::CheckCollision(const std::shared_ptr<SceneObject>& obj) const
{
   const auto left_hand = mJoints[XN_SKEL_LEFT_HAND];
   const auto right_hand = mJoints[XN_SKEL_RIGHT_HAND];

   if ((left_hand.X > obj->GetXPos()) &&
       (left_hand.X < obj->GetXPos() + obj->GetXRes()) &&
       (left_hand.Y > obj->GetYPos()) &&
       (left_hand.Y < obj->GetYPos() + obj->GetYRes()))
   {
      return true;
   }

   if ((right_hand.X > obj->GetXPos()) &&
       (right_hand.X < obj->GetXPos() + obj->GetXRes()) &&
       (right_hand.Y > obj->GetYPos()) &&
       (right_hand.Y < obj->GetYPos() + obj->GetYRes()))
   {
      return true;
   }

   return false;
}

int Actor::GetXCenter()
{
   return mXCenter;
}

int Actor::GetYCenter()
{
   return mYCenter;
}

SDL_Surface* Actor::GetFrame() const
{
   return mFrame;
}
