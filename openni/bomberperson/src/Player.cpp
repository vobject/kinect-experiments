#include "Player.hpp"
#include "InputDevice.hpp"
#include "Cell.hpp"
#include "Bomb.hpp"
#include "Utils.hpp"

Player::Player(
   const std::string& name,
   const std::shared_ptr<InputDevice>& input,
   const std::shared_ptr<Cell>& cell
)
   : mInput(input)
   , mParentCell(cell)
{
   SetResourceId(name);
   SetPosition({ mParentCell->GetPosition().X + 10,
                 mParentCell->GetPosition().Y + 10 });
   SetSize({ 25, 25 });
}

Player::~Player()
{

}

void Player::Update(const int elapsed_time)
{
   mMoveIdleTime += elapsed_time;
   if (mMoveIdleTime > MOVE_PIXEL_DELAY)
   {
      UpdateMovement(elapsed_time);
      mMoveIdleTime = 0;
   }

   mBombIdleTime += elapsed_time;
   if ((mBombIdleTime > PLANT_BOMB_DELAY) && mInput->TestPlantBomb())
   {
      UpdateBombing(elapsed_time);
      mBombIdleTime = 0;
   }
}

std::shared_ptr<InputDevice> Player::GetInputDevice() const
{
   return mInput;
}

void Player::SetParentCell(const std::shared_ptr<Cell>& cell)
{
   mParentCell = cell;
}

void Player::UpdateMovement(const int elapsed_time)
{
   const Point cell_pos = mParentCell->GetPosition();
   const Size cell_size = mParentCell->GetSize();

   const int distance = 1;
   int up = 0;
   int down = 0;
   int left = 0;
   int right = 0;

   if (mInput->TestUp() && CanMoveUp(cell_pos, cell_size, distance)) {
      up++;
   }
   if (mInput->TestDown() && CanMoveDown(cell_pos, cell_size, distance)) {
      down++;
   }
   if (mInput->TestLeft() && CanMoveLeft(cell_pos, cell_size, distance)) {
      left++;
   }
   if (mInput->TestRight() && CanMoveRight(cell_pos, cell_size, distance)) {
      right++;
   }

   SetPosition({ GetPosition().X - left + right, GetPosition().Y - up + down});
}

bool Player::CanMoveUp(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().Y - distance) > cell_pos.Y)
   {
      // Movement inside the current cell is ok.
      return true;
   }

   // Player wants to walk inside the cell on top - check if that is allowed.
   const auto top_cell = mParentCell->GetTopCell();
   if (top_cell && !top_cell->IsBlocking())
   {
      // A cell exists and does not block the player.
      return true;
   }
   // TODO: Should cells with bombs also block? Probably YES!

   return false;
}

bool Player::CanMoveDown(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().Y + GetSize().Height + distance) < (cell_pos.Y + cell_size.Height))
   {
      return true;
   }

   const auto down_cell = mParentCell->GetDownCell();
   if (down_cell && !down_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

bool Player::CanMoveLeft(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().X - distance) > cell_pos.X)
   {
      return true;
   }

   const auto left_cell = mParentCell->GetLeftCell();
   if (left_cell && !left_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

bool Player::CanMoveRight(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().X + GetSize().Width + distance) < (cell_pos.X + cell_size.Width))
   {
      return true;
   }

   const auto right_cell = mParentCell->GetRightCell();
   if (right_cell && !right_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

void Player::UpdateBombing(const int elapsed_time)
{
   auto bomb = std::make_shared<Bomb>("bomb_1", mParentCell);
   bomb->SetRange(3); // TODO: Set depending on players modifications.
   bomb->SetPosition({ mParentCell->GetPosition().X + 1,
                       mParentCell->GetPosition().Y + 1});
   mParentCell->SetBomb(bomb);
}
