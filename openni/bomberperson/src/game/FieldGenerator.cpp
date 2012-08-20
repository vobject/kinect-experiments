#include "FieldGenerator.hpp"
#include "Field.hpp"
#include "Cell.hpp"

#include <cstdlib>
#include <ctime>

FieldGenerator::FieldGenerator()
{
   srand(time(nullptr));
}

FieldGenerator::~FieldGenerator()
{

}

void FieldGenerator::SetFieldPosition(const Point& pos)
{
   mPos = pos;
}

void FieldGenerator::SetFieldSize(const Size& size)
{
   mSize = size;
}

std::shared_ptr<Field> FieldGenerator::GetDefaultArena(
   const int cells_x,
   const int cells_y,
   const int players
) const
{
   auto playing_field = std::make_shared<Field>("area");

   const auto cells = CreateDefaultCells(cells_x, cells_y, playing_field);

   if (players >= 1) {
      cells[1 + (1 * cells_y)]->SetType(CellType::Floor);
      cells[1 + (2 * cells_y)]->SetType(CellType::Floor);
      cells[2 + (1 * cells_y)]->SetType(CellType::Floor);
   }
   if (players >= 2) {
      cells[(cells_x - 3) + ((cells_x - 2) * cells_y)]->SetType(CellType::Floor);
      cells[(cells_x - 2) + ((cells_x - 3) * cells_y)]->SetType(CellType::Floor);
      cells[(cells_x - 2) + ((cells_x - 2) * cells_y)]->SetType(CellType::Floor);
   }

   for (auto& cell : cells)
   {
      if (CellType::DestructibleWall != cell->GetType()) {
         continue;
      }

      if (ShouldCreateItem()) {
         cell->SetItem(GetRandomCellItem());
      }
   }

   playing_field->SetPosition(mPos);
   playing_field->SetSize(mSize);
   playing_field->SetDimensions(cells_x, cells_y);
   playing_field->SetCells(cells);
   return playing_field;
}

std::vector<std::shared_ptr<Cell>> FieldGenerator::CreateDefaultCells(
   const int cells_x,
   const int cells_y,
   const std::shared_ptr<Field>& field
) const
{
   const auto cell_size = GetCellSize(cells_x, cells_y);
   std::vector<std::shared_ptr<Cell>> cells(cells_x * cells_y);

   for (int i = 0; i < (cells_x * cells_y); i++)
   {
      const int cell_field_pos_x = i % cells_y;
      const int cell_field_pos_y = i / cells_y;

      auto cell = std::make_shared<Cell>("cell_transparent",
                                         cell_field_pos_x,
                                         cell_field_pos_y,
                                         field);

      cell->SetPosition({ mPos.X + (cell_size.Width * cell_field_pos_x),
                          mPos.Y + (cell_size.Height * cell_field_pos_y) });
      cell->SetSize(cell_size);

      // Create the field boundary and pattern.
      if ((cell_field_pos_x == 0) ||
          (cell_field_pos_x == (cells_x - 1)) ||
          (cell_field_pos_y == 0) ||
          (cell_field_pos_y == (cells_y - 1)) ||
          (!(cell_field_pos_x % 2) && !(cell_field_pos_y % 2))) // Pattern
      {
         cell->SetType(CellType::IndestructibleWall);
      }
      else
      {
         cell->SetType(CellType::DestructibleWall);
      }
      cells[i] = cell;
   }
   return cells;
}

Size FieldGenerator::GetCellSize(const int cells_x, const int cells_y) const
{
   return { mSize.Width / cells_x, mSize.Height / cells_y };
}

bool FieldGenerator::ShouldCreateItem() const
{
   // 25% chance to generate '0' and return true.
   return !(rand() % 4);
}

CellItem FieldGenerator::GetRandomCellItem() const
{
   const int limit = static_cast<int>(CellItem::CELL_ITEM_COUNT) - 1;
   const int item_id = (rand() % limit) + 1;
   return static_cast<CellItem>(item_id);
}
