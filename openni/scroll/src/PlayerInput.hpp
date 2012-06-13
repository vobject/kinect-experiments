#ifndef PLAYER_INPUT_HPP
#define PLAYER_INPUT_HPP

#include "UserData.hpp"
#include "Utils.hpp"

#include <memory>
#include <map>

class Player;
namespace kinex {
   class UserData;
}

struct PlayerInputState
{
   bool present;
   bool first; // is this the first frame that the input was detected?
   float t; // how long does the input go on if valid and not first in ms.
   ScreenPos pos;
};

class PlayerInput
{
public:
   PlayerInput(const Player& player);
   ~PlayerInput();

   void Update(const kinex::UserData& user_data);

//   std::pair<bool, int> WalkLeft() const;
//   std::pair<bool, int> WalkRight() const;
//   bool Jump() const;
//   bool Duck() const;

   PlayerInputState LeftPunch() const;
   PlayerInputState RightPunch() const;
   PlayerInputState LeftKick() const;
   PlayerInputState RightKick() const;
   PlayerInputState Hadouken() const;
//   bool Kick() const;
//   bool Hadouken() const;

private:
   void CheckWalk();
   void CheckJump();
   void CheckDuck();
   void CheckLeftPunch(std::map<int, XnPoint3D>& joints);
   void CheckRightPunch(std::map<int, XnPoint3D>& joints);
   void CheckLeftKick(std::map<int, XnPoint3D>& joints);
   void CheckRightKick(std::map<int, XnPoint3D>& joints);
   void CheckHadouken(std::map<int, XnPoint3D>& joints);

   ScreenPos GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const;

   const Player& mPlayer;
//   std::pair<bool, int> mWalkLeft = {false, 0};
////   bool mWalkLeft = false;
//   bool mWalkRight = false;
//   bool mJump = false;
//   bool mDuck = false;
   PlayerInputState mLeftPunch = {false, false, 0.0f, {0.0f, 0.0f}};
   PlayerInputState mRightPunch = {false, false, 0.0f, {0.0f, 0.0f}};
   PlayerInputState mLeftKick = {false, false, 0.0f, {0.0f, 0.0f}};
   PlayerInputState mRightKick = {false, false, 0.0f, {0.0f, 0.0f}};
   PlayerInputState mHadouken = {false, false, 0.0f, {0.0f, 0.0f}};
};

#endif // PLAYER_INPUT_HPP
