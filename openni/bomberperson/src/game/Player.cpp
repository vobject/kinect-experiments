#include "Player.hpp"
#include "Cell.hpp"
#include "Extra.hpp"
#include "Bomb.hpp"
#include "../input/InputDevice.hpp"
#include "../utils/Utils.hpp"

Player::Player(const std::string& res_name)
{
   SetResourceId(res_name);
}

Player::~Player()
{

}

void Player::Update(const int elapsed_time)
{
   mMoveIdleTime += elapsed_time;
   if (mMoveIdleTime > mMovementSpeed)
   {
      UpdateMovement(elapsed_time);
   }

   mBombIdleTime += elapsed_time;
   if (mBombIdleTime > mPlantingSpeed)
   {
      UpdateBombing(elapsed_time);
   }
}

std::shared_ptr<InputDevice> Player::GetInputDevice() const
{
   return mInput;
}

void Player::SetInputDevice(const std::shared_ptr<InputDevice>& input)
{
   mInput = input;
}

void Player::SetParentCell(const std::shared_ptr<Cell>& cell)
{
   mParentCell = cell;

   if (mParentCell->HasExplosion())
   {
      // Explosions kill the player instantly.
      SetAlive(false);
      return;
   }

   if (mParentCell->HasExtra())
   {
      switch (mParentCell->CollectExtra()->GetType())
      {
         case ExtraType::Speed:
            IncreaseSpeed();
            break;
         case ExtraType::BombRange:
            mBombRange++;
            break;
         case ExtraType::BombSupply:
            mBombSupply++;
            break;
         default:
            break;
      }
   }
}

Direction Player::GetDirection() const
{
   return mDirection;
}

void Player::UpdateMovement(const int elapsed_time)
{
   const int distance = 1;
   int up = 0;
   int down = 0;
   int left = 0;
   int right = 0;

   if (mInput->TestUp())
   {
      mDirection = Direction::Up;

      if (CanMove(mDirection, distance)) {
         up++;
      }
   }
   if (mInput->TestDown())
   {
      mDirection = Direction::Down;

      if (CanMove(mDirection, distance)) {
         down++;
      }
   }
   if (mInput->TestLeft())
   {
      mDirection = Direction::Left;

      if (CanMove(mDirection, distance)) {
         left++;
      }
   }
   if (mInput->TestRight())
   {
      mDirection = Direction::Right;

      if (CanMove(mDirection, distance)) {
         right++;
      }
   }

   SetPosition({ GetPosition().X - left + right, GetPosition().Y - up + down});
   mMoveIdleTime = 0;
}

void Player::UpdateBombing(const int elapsed_time)
{
   if (!mInput->TestPlantBomb())
   {
      // The user did not request to plant a bomb.
      return;
   }

   if (mParentCell->HasBomb()) {
      // Only one bomb per cell.
      return;
   }

   if (!CanPlantBomb()) {
      // Out of bomb supply. Wait till an older bomb exploded.
      return;
   }

   auto bomb = std::make_shared<Bomb>("bomb", mParentCell);
   bomb->SetRange(mBombRange);
   bomb->SetSize(mParentCell->GetSize());
   bomb->SetPosition(mParentCell->GetPosition());
   mParentCell->SetBomb(bomb);

   mPlantedBombs.push_back(bomb);
   mBombIdleTime = 0;
}

bool Player::CanMove(const Direction dir, const int distance) const
{
   const Point cell_pos = mParentCell->GetPosition();
   const Size cell_size = mParentCell->GetSize();

   // Check for movement inside the current cell.
   // Movement inside the current cell is always ok.
   switch (dir)
   {
      case Direction::Up:
         if ((GetPosition().Y - distance) >= cell_pos.Y)
            return true;
         break;
      case Direction::Down:
         if ((GetPosition().Y + GetSize().Height + distance) <= (cell_pos.Y + cell_size.Height))
            return true;
         break;
      case Direction::Left:
         if ((GetPosition().X - distance) >= cell_pos.X)
            return true;
         break;
      case Direction::Right:
         if ((GetPosition().X + GetSize().Width + distance) <= (cell_pos.X + cell_size.Width))
            return true;
         break;
   }

   // Player wants to walk to another cell - check if that is allowed.
   const auto neighbor_cell = mParentCell->GetNeighborCell(dir);
   if (neighbor_cell &&
       !neighbor_cell->HasWall() &&
       !neighbor_cell->HasBomb())
   {
      // A cell exists and does not block the player.
      return true;
   }

   return false;
}

bool Player::CanPlantBomb()
{
   int bombs_alive = 0;
   for (const auto& bomb : mPlantedBombs)
   {
      if (bomb->IsAlive())
      {
         bombs_alive++;
      }
   }

   // Garbage collection of the planted-bombs-vector.
   if (!bombs_alive) {
      mPlantedBombs.clear();
   }

   return (mBombSupply > bombs_alive);
}

void Player::IncreaseSpeed()
{
   if (mMovementSpeed > 2) {
      mMovementSpeed -= 2;
   }
   // The player is already at maximum speed.
}
