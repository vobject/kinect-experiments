#include "Field.hpp"
#include "Cell.hpp"
#include "../utils/Utils.hpp"

#include <ctime>

Field::Field(const std::string& name)
{
   SetResourceId(name);
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

void Field::SetDimensions(const int cells_x, const int cells_y)
{
   mXCells = cells_x;
   mYCells = cells_y;
}

void Field::SetCells(const std::vector<std::shared_ptr<Cell>>& cells)
{
   mCells = cells;
}

std::vector<std::shared_ptr<Cell>> Field::GetCells() const
{
   return mCells;
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
