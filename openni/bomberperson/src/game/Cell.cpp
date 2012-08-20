#include "Cell.hpp"
#include "Field.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"
#include "../utils/Utils.hpp"

Cell::Cell(
   const std::string& name,
   const int field_pos_x,
   const int field_pos_y,
   const std::shared_ptr<Field>& field
)
   : mFieldPosX(field_pos_x)
   , mFieldPosY(field_pos_y)
   , mField(field) // Do not use inside the ctor - object is not ready yet.
   , mType(CellType::Floor)
   , mItem(CellItem::None)
   , mBombOrExplosion(nullptr)
{
   SetResourceId(name);
}

Cell::~Cell()
{

}

void Cell::Update(const int elapsed_time)
{
   if (mBombOrExplosion && mBombOrExplosion->IsAlive())
   {
      mBombOrExplosion->Update(elapsed_time);

      if (!mBombOrExplosion->IsAlive()) {
         mBombOrExplosion = nullptr;
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

   switch (mType)
   {
      case CellType::Floor:
         SetResourceId("cell_transparent");
         break;
      case CellType::DestructibleWall:
         SetResourceId("cell_wood");
         break;
      case CellType::IndestructibleWall:
         SetResourceId("cell_bricks");
         break;
      default:
         break;
   }
}

std::shared_ptr<Cell> Cell::GetCell(Direction dir) const
{
   switch (dir)
   {
      case Direction::Up:
         return mField->GetCellAboveOf(mFieldPosX, mFieldPosY);
      case Direction::Down:
         return mField->GetCellBelowOf(mFieldPosX, mFieldPosY);
      case Direction::Left:
         return mField->GetCellLeftOf(mFieldPosX, mFieldPosY);
      case Direction::Right:
         return mField->GetCellRightOf(mFieldPosX, mFieldPosY);
   }
}

//std::shared_ptr<Cell> Cell::GetTopCell() const
//{
//   return mField->GetCellAboveOf(mFieldPosX, mFieldPosY);
//}
//
//std::shared_ptr<Cell> Cell::GetDownCell() const
//{
//   return mField->GetCellBelowOf(mFieldPosX, mFieldPosY);
//}
//
//std::shared_ptr<Cell> Cell::GetLeftCell() const
//{
//   return mField->GetCellLeftOf(mFieldPosX, mFieldPosY);
//}
//
//std::shared_ptr<Cell> Cell::GetRightCell() const
//{
//   return mField->GetCellRightOf(mFieldPosX, mFieldPosY);
//}

bool Cell::IsBlocking() const
{
   if (CellType::Floor != mType) {
      return true;
   }

   if (HasBomb()) {
      return true;
   }

   // TODO: Take other items laying on this cell into account!

   return false;
}

bool Cell::HasBomb() const
{
   return (GetBomb() != nullptr);
}

std::shared_ptr<Bomb> Cell::GetBomb() const
{
   return std::dynamic_pointer_cast<Bomb>(mBombOrExplosion);
}

void Cell::SetBomb(const std::shared_ptr<Bomb>& bomb)
{
   mBombOrExplosion = bomb;
}

bool Cell::HasExplosion() const
{
   return (GetExplosion() != nullptr);
}

std::shared_ptr<Explosion> Cell::GetExplosion() const
{
   return std::dynamic_pointer_cast<Explosion>(mBombOrExplosion);
}

void Cell::SetExplosion(const std::shared_ptr<Explosion>& explosion)
{
   mBombOrExplosion = explosion;
}

bool Cell::HasItem() const
{
   return (CellItem::None != mItem);
}

CellItem Cell::GetItem() const
{
   return mItem;
}

void Cell::SetItem(const CellItem item)
{
   mItem = item;
}
