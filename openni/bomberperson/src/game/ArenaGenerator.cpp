#include "ArenaGenerator.hpp"
#include "Arena.hpp"
#include "Cell.hpp"
#include "Wall.hpp"
#include "Extra.hpp"

#include <cstdlib>
#include <ctime>

ArenaGenerator::ArenaGenerator()
{
   srand(time(nullptr));
}

ArenaGenerator::~ArenaGenerator()
{

}

void ArenaGenerator::SetArenaPosition(const Point& pos)
{
   mPos = pos;
}

void ArenaGenerator::SetArenaSize(const Size& size)
{
   mSize = size;
}

std::shared_ptr<Arena> ArenaGenerator::GetDefaultArena(
   const int cells_x,
   const int cells_y,
   const int players
) const
{
   auto arena = std::make_shared<Arena>("arena");

   const auto cells = CreateDefaultCells(cells_x, cells_y, arena);

   if (players >= 1) {
      cells[1 + (1 * cells_y)]->SetWall(nullptr);
      cells[1 + (2 * cells_y)]->SetWall(nullptr);
      cells[2 + (1 * cells_y)]->SetWall(nullptr);
   }
   if (players >= 2) {
      cells[(cells_x - 3) + ((cells_x - 2) * cells_y)]->SetWall(nullptr);
      cells[(cells_x - 2) + ((cells_x - 3) * cells_y)]->SetWall(nullptr);
      cells[(cells_x - 2) + ((cells_x - 2) * cells_y)]->SetWall(nullptr);
   }

   for (auto& cell : cells)
   {
      if (cell->HasWall() && !cell->GetWall()->IsDestructible()) {
         continue;
      }

      if (!cell->HasWall()) {
         continue;
      }

      if (!ShouldCreateItem()) {
         continue;
      }

      std::string extra_name;
      ExtraType extra_type;

      switch (rand() % 3)
      {
         case 0:
            extra_name = "extra_speed";
            extra_type = ExtraType::Speed;
            break;
         case 1:
            extra_name = "extra_supply";
            extra_type = ExtraType::BombSupply;
            break;
         case 2:
            extra_name = "extra_range";
            extra_type = ExtraType::BombRange;
            break;
      }

      auto extra = std::make_shared<Extra>(extra_name, extra_type);
      extra->SetPosition(cell->GetPosition());
      extra->SetSize(cell->GetSize());
      cell->SetExtra(extra);
   }

   arena->SetPosition(mPos);
   arena->SetSize(mSize);
   arena->SetDimensions(cells_x, cells_y);
   arena->SetCells(cells);
   return arena;
}

std::vector<std::shared_ptr<Cell>> ArenaGenerator::CreateDefaultCells(
   const int cells_x,
   const int cells_y,
   const std::shared_ptr<Arena>& field
) const
{
   const auto cell_size = GetCellSize(cells_x, cells_y);
   std::vector<std::shared_ptr<Cell>> cells(cells_x * cells_y);

   for (int i = 0; i < (cells_x * cells_y); i++)
   {
      const int cell_field_pos_x = i % cells_y;
      const int cell_field_pos_y = i / cells_y;

      auto cell = std::make_shared<Cell>("cell",
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
         auto wall = std::make_shared<Wall>("wall_bricks",
                                            WallType::Indestructible);
         wall->SetPosition(cell->GetPosition());
         wall->SetSize(cell->GetSize());
         cell->SetWall(wall);
      }
      else
      {
         auto wall = std::make_shared<Wall>("wall_wood",
                                            WallType::Destructible);
         wall->SetPosition(cell->GetPosition());
         wall->SetSize(cell->GetSize());
         cell->SetWall(wall);
      }
      cells[i] = cell;
   }
   return cells;
}

Size ArenaGenerator::GetCellSize(const int cells_x, const int cells_y) const
{
   return { mSize.Width / cells_x, mSize.Height / cells_y };
}

bool ArenaGenerator::ShouldCreateItem() const
{
   // 25% chance to generate '0' and return true.
   return !(rand() % 4);
}

CellItem ArenaGenerator::GetRandomCellItem() const
{
//   const int limit = static_cast<int>(CellItem::CELL_ITEM_COUNT) - 1;
//   const int item_id = (rand() % limit) + 1;
//   return static_cast<CellItem>(item_id);
   return static_cast<CellItem>(0);
}
