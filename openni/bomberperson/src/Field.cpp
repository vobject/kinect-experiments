#include "Field.hpp"
#include "Cell.hpp"
#include "Utils.hpp"

Field::Field(const std::string& name)
{
   SetResourceId(name);

   // TODO: get this from ResourceCache.
   mXCells = 9;
   mYCells = 9;

   // TODO: Initialize cells from the level file.

//   // HACK:
//   for (int y = 0; y < mYCells; y++)
//   {
//      std::vector<std::shared_ptr<Cell>> x_cells;
//      for (int x = 0; x < mXCells; x++)
//      {
//         x_cells.push_back(std::make_shared<Cell>("cell_test", x, y, CellType::DestructibleWall));
//
//         if (x == 0) { x_cells[x]->SetType(CellType::IndestructibleWall); }
//         if (x == (mXCells - 1)) { x_cells[x]->SetType(CellType::IndestructibleWall); }
//         if (y == 0) { x_cells[x]->SetType(CellType::IndestructibleWall); }
//         if (y == (mYCells - 1)) { x_cells[x]->SetType(CellType::IndestructibleWall); }
//      }
//      mCells.push_back(x_cells);
//   }
//   mCells[1][1]->SetType(CellType::Floor);
//   mCells[2][2]->SetType(CellType::IndestructibleWall);
//   mCells[2][4]->SetType(CellType::IndestructibleWall);
//   mCells[2][6]->SetType(CellType::IndestructibleWall);
//   mCells[4][2]->SetType(CellType::IndestructibleWall);
//   mCells[4][4]->SetType(CellType::IndestructibleWall);
//   mCells[4][6]->SetType(CellType::IndestructibleWall);
//   mCells[6][2]->SetType(CellType::IndestructibleWall);
//   mCells[6][4]->SetType(CellType::IndestructibleWall);
//   mCells[6][6]->SetType(CellType::IndestructibleWall);
}

Field::~Field()
{

}

void Field::Update(const int elapsed_time)
{
   // May be used for an animated ground (e.g. grass or craters).
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

//std::shared_ptr<Cell> Field::GetCell(const int cell_x, const int cell_y) const
//{
//   return mCells.at(cell_y).at(cell_x);
//}
//
//std::shared_ptr<Cell> Field::GetCellAboveOf(const int cell_x, const int cell_y) const
//{
//   if (cell_y <= 0) {
//      return nullptr;
//   }
//   return mCells.at(cell_y - 1).at(cell_x);
//}
//
//std::shared_ptr<Cell> Field::GetCellBelowOf(const int cell_x, const int cell_y) const
//{
//   if (cell_y >= (mCells.size() - 1)) {
//      return nullptr;
//   }
//   return mCells.at(cell_y + 1).at(cell_x);
//}
//
//std::shared_ptr<Cell> Field::GetCellLeftOf(const int cell_x, const int cell_y) const
//{
//   if (cell_x <= 0) {
//      return nullptr;
//   }
//   return mCells.at(cell_y).at(cell_x - 1);
//}
//
//std::shared_ptr<Cell> Field::GetCellRightOf(const int cell_x, const int cell_y) const
//{
//   if (cell_x >= (mCells.at(cell_y).size() - 1)) {
//      return nullptr;
//   }
//   return mCells.at(cell_y).at(cell_x + 1);
//}

//std::shared_ptr<Cell> Field::GetCellLeftOf(const std::shared_ptr<Cell>& cell) const
//{
//   // TODO
//   return nullptr;
//}
