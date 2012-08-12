#include "Cell.hpp"
#include "Utils.hpp"

Cell::Cell(
   const std::string& name,
   const int field_pos_x,
   const int field_pos_y,
   const CellType type
)
   : mFieldPosX(field_pos_x)
   , mFieldPosY(field_pos_y)
   , mType(type)
{
   SetResourceId(name);
}

Cell::~Cell()
{

}

void Cell::Update(const int elapsed_time)
{

}

//int Cell::GetFieldPositionX() const
//{
//   return mFieldPosX;
//}
//
//int Cell::GetFieldPositionY() const
//{
//   return mFieldPosY;
//}

CellType Cell::GetType() const
{
   return mType;
}

void Cell::SetType(const CellType type)
{
   mType = type;
}

bool Cell::Blocking() const
{
   return (CellType::Floor != mType);
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
