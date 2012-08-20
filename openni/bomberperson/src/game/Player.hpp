#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SceneObject.hpp"
#include "../input/InputDevice.hpp"
#include "../utils/Utils.hpp"

#include <memory>
#include <vector>

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
   Player(const std::string& res_name);
   virtual ~Player();

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   std::shared_ptr<InputDevice> GetInputDevice() const;
   void SetInputDevice(const std::shared_ptr<InputDevice>& input);

   void SetParentCell(const std::shared_ptr<Cell>& cell);

   Direction GetDirection() const;

private:
   void UpdateMovement(int elapsed_time);
   void UpdateBombing(int elapsed_time);

   bool CanMove(Direction dir, int distance) const;
   bool CanPlantBomb();

   void IncreaseSpeed();

   std::shared_ptr<InputDevice> mInput;
   std::shared_ptr<Cell> mParentCell;
   int mMoveIdleTime = 0;
   int mBombIdleTime = 0;

   // Number of milliseconds the player has to wait to move another pixel.
   int mMovementSpeed = 12;
   // How many milliseconds does the player have to wait to plant another bomb?
   int mPlantingSpeed = 200;

   int mBombRange = 1;
   int mBombSupply = 1;
   std::vector<std::shared_ptr<Bomb>> mPlantedBombs;

   Direction mDirection = Direction::Down;
};

#endif // PLAYER_HPP
