#include "Cell.hpp"
#include "Field.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"
#include "Utils.hpp"

Cell::Cell(
   const std::string& name,
   const int field_pos_x,
   const int field_pos_y,
   const Field& field,
   const CellType type
)
   : mFieldPosX(field_pos_x)
   , mFieldPosY(field_pos_y)
   , mField(field) // Do not use inside the ctor - object is not ready yet.
   , mType(type)
   , mBomb(nullptr)
   , mExplosion(nullptr)
{
   SetResourceId(name);
}

Cell::~Cell()
{

}

void Cell::Update(const int elapsed_time)
{
   if (mBomb && mBomb->IsAlive())
   {
      mBomb->Update(elapsed_time);

      if (!mBomb->IsAlive()) {
         mBomb = nullptr; // Bomb detonated.
      }
   }

   if (mExplosion && mExplosion->IsAlive())
   {
      mExplosion->Update(elapsed_time);

      if (!mExplosion->IsAlive()) {
         mExplosion = nullptr;
      }
   }

   // TODO: call Update for other items that could be present on this cell.
}

CellType Cell::GetType() const
{
   return mType;
}

void Cell::SetType(const CellType type)
{
   mType = type;
}

std::shared_ptr<Cell> Cell::GetTopCell() const
{
   return mField.GetCellAboveOf(mFieldPosX, mFieldPosY);
}

std::shared_ptr<Cell> Cell::GetDownCell() const
{
   return mField.GetCellBelowOf(mFieldPosX, mFieldPosY);
}

std::shared_ptr<Cell> Cell::GetLeftCell() const
{
   return mField.GetCellLeftOf(mFieldPosX, mFieldPosY);
}

std::shared_ptr<Cell> Cell::GetRightCell() const
{
   return mField.GetCellRightOf(mFieldPosX, mFieldPosY);
}

bool Cell::IsBlocking() const
{
   if (CellType::Floor != mType) {
      return true;
   }

   if (mBomb) {
      return true;
   }

   // TODO: Take other items laying on this cell into account!

   return false;
}

std::shared_ptr<Bomb> Cell::GetBomb() const
{
   return mBomb;
}

void Cell::SetBomb(const std::shared_ptr<Bomb>& bomb)
{
   mBomb = bomb;
}

std::shared_ptr<Explosion> Cell::GetExplosion() const
{
   return mExplosion;
}

void Cell::SetExplosion(const std::shared_ptr<Explosion>& explosion)
{
   mExplosion = explosion;
}

//CellItem Cell::GetItem() const
//{
//   return mItem;
//}
//
//void Cell::SetItem(const CellItem item)
//{
//   mItem = item;
//}
