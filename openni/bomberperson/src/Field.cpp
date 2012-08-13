#include "Field.hpp"
#include "Cell.hpp"
#include "Utils.hpp"

#include <time.h>

Field::Field(const std::string& name, const Point& pos, const Size& size)
{
   SetResourceId(name);
   SetPosition(pos);
   SetSize(size);

   srand(time(nullptr));

   // TODO: get this from ResourceCache.
   mXCells = 9;
   mYCells = 9;

   // TODO: Initialize cells from the level file.
   const Size cell_size = GetCellSize();

   for (int i = 0; i < (mXCells * mYCells); i++)
   {
      int cell_field_pos_x;
      int cell_field_pos_y;
      std::tie(cell_field_pos_x, cell_field_pos_y) = IndexToFieldPos(i);

      auto cell = std::make_shared<Cell>("cell_test",
                                         cell_field_pos_x,
                                         cell_field_pos_y,
                                         *this,
                                         CellType::DestructibleWall);

      cell->SetPosition({ GetPosition().X + (cell_size.Width * cell_field_pos_x),
                          GetPosition().Y + (cell_size.Height * cell_field_pos_y) });
      cell->SetSize(cell_size);

      // Use indestructible cells to create a field boundary.
      if ((cell_field_pos_x == 0) ||
          (cell_field_pos_x == (mXCells - 1)) ||
          (cell_field_pos_y == 0) ||
          (cell_field_pos_y == (mYCells - 1)))
      {
         cell->SetType(CellType::IndestructibleWall);
      }
      else if (ShouldCellGetItem())
      {
         cell->SetItem(GetRandomCellItem());
      }

      mCells.push_back(cell);
   }

   mCells[FieldPosToIndex(1, 1)]->SetType(CellType::Floor);
   mCells[FieldPosToIndex(1, 2)]->SetType(CellType::Floor);
   mCells[FieldPosToIndex(2, 1)]->SetType(CellType::Floor);

   mCells[FieldPosToIndex(2, 2)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(2, 4)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(2, 6)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(4, 2)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(4, 4)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(4, 6)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(6, 2)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(6, 4)]->SetType(CellType::IndestructibleWall);
   mCells[FieldPosToIndex(6, 6)]->SetType(CellType::IndestructibleWall);

   mCells[FieldPosToIndex(2, 2)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(2, 4)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(2, 6)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(4, 2)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(4, 4)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(4, 6)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(6, 2)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(6, 4)]->SetItem(CellItem::None);
   mCells[FieldPosToIndex(6, 6)]->SetItem(CellItem::None);
}

Field::~Field()
{

}

void Field::Update(const int elapsed_time)
{
   // TODO: May also be used for an animated ground (e.g. grass or craters).

   for (auto& cell : mCells)
   {
      cell->Update(elapsed_time);
   }
}

std::vector<std::shared_ptr<Cell>> Field::GetCells() const
{
   return mCells;
}

int Field::GetXCells() const
{
   return mXCells;
}


int Field::GetYCells() const
{
   return mYCells;
}

std::shared_ptr<Cell> Field::GetCellFromPosition(const Point& pos) const
{
   const auto cell_x = (pos.X - GetPosition().X) / GetCellSize().Width;
   const auto cell_y = (pos.Y - GetPosition().Y) / GetCellSize().Height;
   return GetCellFromCoordinates(cell_x, cell_y);
}

std::shared_ptr<Cell> Field::GetCellFromCoordinates(const int cell_x, const int cell_y) const
{
   const auto index = FieldPosToIndex(cell_x, cell_y);
   if (index >= mCells.size()) {
      return nullptr;
   }
   return mCells[index];
}

std::shared_ptr<Cell> Field::GetCellAboveOf(const int cell_x, const int cell_y) const
{
   if (cell_y <= 0) {
      return nullptr;
   }
   return GetCellFromCoordinates(cell_x, cell_y - 1);
}

std::shared_ptr<Cell> Field::GetCellBelowOf(const int cell_x, const int cell_y) const
{
   return GetCellFromCoordinates(cell_x, cell_y + 1);
}

std::shared_ptr<Cell> Field::GetCellLeftOf(const int cell_x, const int cell_y) const
{
   if (cell_x <= 0) {
      return nullptr;
   }
   return GetCellFromCoordinates(cell_x - 1, cell_y);
}

std::shared_ptr<Cell> Field::GetCellRightOf(const int cell_x, const int cell_y) const
{
   return GetCellFromCoordinates(cell_x + 1, cell_y);
}

Size Field::GetCellSize() const
{
   const Size field_size = GetSize();
   return { field_size.Width / mXCells, field_size.Height / mYCells };
}

std::tuple<int, int> Field::IndexToFieldPos(const int index) const
{
   return std::make_tuple(index % mYCells, index / mYCells);
}

int Field::FieldPosToIndex(const int cell_x, const int cell_y) const
{
   return (cell_x + (cell_y * mYCells));
}

bool Field::ShouldCellGetItem() const
{
   // 25% chance to generate '0' and return true.
   return !(rand() % 4);
}

CellItem Field::GetRandomCellItem() const
{
   const int limit = static_cast<int>(CellItem::CELL_ITEM_COUNT) - 1;
   const int item_id = (rand() % limit) + 1;
   return static_cast<CellItem>(item_id);
}
