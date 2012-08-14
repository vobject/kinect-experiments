#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SceneObject.hpp"
#include "InputDevice.hpp"
#include "Utils.hpp"

#include <memory>
#include <string>
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

private:
   void UpdateMovement(int elapsed_time);
   void UpdateBombing(int elapsed_time);

   bool CanMoveUp(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveDown(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveLeft(const Point& cell_pos, const Size& cell_size, int distance) const;
   bool CanMoveRight(const Point& cell_pos, const Size& cell_size, int distance) const;

   bool CanPlantBomb();

   void IncreaseSpeed();

   std::shared_ptr<InputDevice> mInput;
   std::shared_ptr<Cell> mParentCell;
   int mMoveIdleTime = 0;
   int mBombIdleTime = 0;

   // Number of milliseconds the player has to wait to move another pixel.
   int mSpeed = 8;
   int mBombRange = 1;
   int mBombSupply = 1;
   std::vector<std::shared_ptr<Bomb>> mPlantedBombs;
};

#endif // PLAYER_HPP
