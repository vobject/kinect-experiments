#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SceneObject.hpp"
#include "InputDevice.hpp"
#include "Utils.hpp"

#include <functional>
#include <memory>
#include <string>

class InputDevice;
class Cell;
class Bomb;

//enum class PlayerOrientation
//{
//   Up,
//   Down,
//   Left,
//   Right
//};

//// Determines where the Player will be placed on the map at startup.
//enum class PlayerId
//{
//   Player_1,
//   Player_2,
//   Player_3,
//   Player_4
//};

class Player : public SceneObject
{
public:
   Player(const std::string& name,
          const std::shared_ptr<InputDevice>& input,
          const std::shared_ptr<Cell>& cell);
   virtual ~Player();

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   std::shared_ptr<InputDevice> GetInputDevice() const;

   void SetCurrentCell(const std::shared_ptr<Cell>& cell);

   // TODO: Pass a reference to the owning Level object, so the player can
   //  directly plant bombs in the level/field/cell on Update() -> sensible?
   //  SetParentCell(Cell& cell);
   // ---> Also: On Update() the player may also check his collisions!
   // And check if his current cell has items the collect!

//   bool HasBomb() const;
//   std::shared_ptr<Bomb> GetBomb();

//   void IncreaseSpeed(int steps);
//   void DecreaseSpeed(int steps);
//   int GetSpeed() const;

//   void MoveUp();
//   void MoveDown();
//   void MoveLeft();
//   void MoveRight();

//   PlayerInput GetInput();
//   PlayerOrientation GetOrientation() const;
//   virtual bool CheckAttackCollision(const std::shared_ptr<SceneObject>& obj, Point& collision);
//   virtual bool CheckGenericCollision(const std::shared_ptr<SceneObject>& obj, Point& collision);
   // Is Alive();

//   int GetXCenter();
//   int GetYCenter();

//   SDL_Surface* GetFrame() const;

private:
   // How many milliseconds does the player have to wait to move another pixel?
   static const int MOVE_PIXEL_DELAY = 6;
   // How many milliseconds does the player have to wait to plant another bomb?
   static const int PLANT_BOMB_DELAY = 1000;

   void UpdateMovement(int elapsed_time);
   void UpdateBombing(int elapsed_time);

   bool CanMoveUp(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveDown(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveLeft(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveRight(const Point& cell_pos, const Size& cell_size, int distance) const;

//   bool IsUserDataValid(const kinex::UserData& user) const;
//   Point GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const;
//
////   bool CheckCollision(const Point& pt, const SceneObject& obj) const;
////   bool CollisionInProgress(const std::list<std::shared_ptr<SceneObject>>& collisions,
////                            const std::shared_ptr<SceneObject>& obj) const;
//
//   std::shared_ptr<kinex::Nui> mKinect;
//   kinex::UserData mUserData;
//   SDL_Surface* mTexture;
//
//   PlayerId mId;
   std::shared_ptr<InputDevice> mInput;
   std::shared_ptr<Cell> mParentCell;
   int mMoveIdleTime = 0;
   int mBombIdleTime = 0;
   bool mWantToPlantBomb = false;

//   PlayerInput mInput; // NOT practical, because it does not know about collisions!
//
//   // Remember objects that the player is currently colliding.
//   // CheckAttackCollision() will only return true for the initial collision
//   // with the object. It returns false if the player stays colliding.
//   // As soon as the player is really not colliding any more, the status
//   // is reset.
////   std::list<std::shared_ptr<SceneObject>> mLeftHandAttacks;
////   std::list<std::shared_ptr<SceneObject>> mRightHandAttacks;
////   std::list<std::shared_ptr<SceneObject>> mLeftFootAttacks;
////   std::list<std::shared_ptr<SceneObject>> mRightFootAttacks;
};

#endif // PLAYER_HPP
