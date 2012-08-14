#ifndef FIELD_GENERATOR_HPP
#define FIELD_GENERATOR_HPP

#include "Utils.hpp"

#include <memory>
#include <string>
#include <tuple>
#include <vector>

class Field;
class Cell;
enum class CellItem;

class FieldGenerator
{
public:
   FieldGenerator(); // TODO: Init with ResCache.
   ~FieldGenerator();

   FieldGenerator(const FieldGenerator&) = delete;
   FieldGenerator& operator=(const FieldGenerator&) = delete;

   void SetFieldPosition(const Point& pos);
   void SetFieldSize(const Size& size);

//   std::shared_ptr<Field> FromLevel(const std::string& name) const;
   std::shared_ptr<Field> GetDefaultArena(int cells_x, int cells_y, int players) const;

private:
   std::vector<std::shared_ptr<Cell>> CreateDefaultCells(int cells_x,
         int cells_y, const std::shared_ptr<Field>& field) const;

   Size GetCellSize(int cells_x, int cells_y) const;
   bool ShouldCreateItem() const;
   CellItem GetRandomCellItem() const;

   Point mPos = { 0, 0 };
   Size mSize = { 0, 0 };
};

#endif // FIELD_GENERATOR_HPP
