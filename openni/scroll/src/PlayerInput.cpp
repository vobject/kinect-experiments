#include "PlayerInput.hpp"
#include "Player.hpp"
#include "UserData.hpp"

PlayerInput::PlayerInput(const Player& player)
   : mPlayer(player)
{

}

PlayerInput::~PlayerInput()
{

}

void PlayerInput::Update(const kinex::UserData& user_data)
{
   auto joints = user_data.GetPerspectiveJoints();

   CheckHadouken(joints);
   if (!mHadouken.present) {
      CheckLeftPunch(joints);
      CheckRightPunch(joints);
   }
   else {
      mLeftPunch.present = false;
      mRightPunch.present = false;
   }

   CheckLeftKick(joints);
   CheckRightKick(joints);
}

//std::pair<bool, int> PlayerInput::WalkLeft() const
//{
//   return mWalkLeft;
//}
//
//bool PlayerInput::WalkRight() const
//{
//   return mWalkRight;
//}
//
//bool PlayerInput::Jump() const
//{
//   return mJump;
//}
//
//bool PlayerInput::Duck() const
//{
//   return mDuck;
//}

PlayerInputState PlayerInput::LeftPunch() const
{
   return mLeftPunch;
}

PlayerInputState PlayerInput::RightPunch() const
{
   return mRightPunch;
}

PlayerInputState PlayerInput::LeftKick() const
{
   return mLeftKick;
}

PlayerInputState PlayerInput::RightKick() const
{
   return mRightKick;
}

PlayerInputState PlayerInput::Hadouken() const
{
   return mHadouken;
}

void PlayerInput::CheckWalk()
{

}

void PlayerInput::CheckJump()
{

}

void PlayerInput::CheckDuck()
{

}

void PlayerInput::CheckLeftPunch(std::map<int, XnPoint3D>& joints)
{
   // FIXME: How to determine if a punch was thrown from one frame?

   // Simple attempt -> the fist must be:
   //    - below the head
   //    - above the hip
   //    - at least 160px from the torso (x-axis)

//   const auto head = joints[XN_SKEL_HEAD];
//   const auto torso = joints[XN_SKEL_TORSO];
//   const auto hip = joints[XN_SKEL_LEFT_HIP];
   const auto hand = joints[XN_SKEL_LEFT_HAND];
//   const auto punch_distance = 160;

//   if (
//         (head.Y < hand.Y) &&
//         (hip.Y > hand.Y) &&
//         ((hand.X - torso.X) > punch_distance)
//      )
//   {
      mLeftPunch.first = !mLeftPunch.present;
      mLeftPunch.pos = GetRelativePerspectiveJointPosition(hand);
      mLeftPunch.present = true;
      return;
//   }
//   else
//   {
//      mLeftPunch.present = false;
//   }
}

void PlayerInput::CheckRightPunch(std::map<int, XnPoint3D>& joints)
{
//   const auto head = joints[XN_SKEL_HEAD];
//   const auto torso = joints[XN_SKEL_TORSO];
//   const auto hip = joints[XN_SKEL_LEFT_HIP];
   const auto hand = joints[XN_SKEL_RIGHT_HAND];
//   const auto punch_distance = 160;

//   LOG(logDEBUG) << (head.Y < hand.Y) << ", " << (hip.Y > hand.Y) << ", " << ((hand.X - torso.X) > punch_distance) << ", " << mRightPunch.first;

//   if (
//         (head.Y < hand.Y) &&
//         (hip.Y > hand.Y) &&
//         ((hand.X - torso.X) > punch_distance)
//      )
//   {
      mRightPunch.first = !mRightPunch.present;
      mRightPunch.pos = GetRelativePerspectiveJointPosition(hand);
      mRightPunch.present = true;
      return;
//   }
//   else
//   {
//      mRightPunch.present = false;
//   }
}

void PlayerInput::CheckLeftKick(std::map<int, XnPoint3D>& joints)
{
   const auto foot = joints[XN_SKEL_LEFT_FOOT];
   mLeftKick.pos = GetRelativePerspectiveJointPosition(foot);
   mLeftKick.present = true;
}

void PlayerInput::CheckRightKick(std::map<int, XnPoint3D>& joints)
{
   const auto foot = joints[XN_SKEL_RIGHT_FOOT];
   mRightKick.pos = GetRelativePerspectiveJointPosition(foot);
   mRightKick.present = true;
}

void PlayerInput::CheckHadouken(std::map<int, XnPoint3D>& joints)
{
   const auto torso = joints[XN_SKEL_TORSO];
   const auto hand_l = joints[XN_SKEL_LEFT_HAND];
   const auto hand_r = joints[XN_SKEL_RIGHT_HAND];
   const auto torso_hand_distance = 180;
   const auto torso_y_delta = 60;

   if (
         ((hand_l.X - torso.X) > torso_hand_distance) &&
         ((hand_r.X - torso.X) > torso_hand_distance)
      )
   {
      mHadouken.first = !mHadouken.present;
      mHadouken.pos = GetRelativePerspectiveJointPosition(hand_r);
      mHadouken.present = true;
   }
   else
   {
      mHadouken.present = false;
   }

}

ScreenPos PlayerInput::GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const
{
   return {
      static_cast<float>(mPlayer.GetSize().Width) / 640 * pos.X + mPlayer.GetPosition().X,
      static_cast<float>(mPlayer.GetSize().Height) / 480 * pos.Y + mPlayer.GetPosition().Y
   };
}
