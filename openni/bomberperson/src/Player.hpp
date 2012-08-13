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

   void SetParentCell(const std::shared_ptr<Cell>& cell);

private:
   // How many milliseconds does the player have to wait to move another pixel?
   static const int MOVE_PIXEL_DELAY = 6;
   // How many milliseconds does the player have to wait to plant another bomb?
   static const int PLANT_BOMB_DELAY = 750;

   void UpdateMovement(int elapsed_time);
   void UpdateBombing(int elapsed_time);

   bool CanMoveUp(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveDown(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveLeft(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveRight(const Point& cell_pos, const Size& cell_size, int distance) const;

   std::shared_ptr<InputDevice> mInput;
   std::shared_ptr<Cell> mParentCell;
   int mMoveIdleTime = 0;
   int mBombIdleTime = 0;
   bool mWantToPlantBomb = false;
};

#endif // PLAYER_HPP
