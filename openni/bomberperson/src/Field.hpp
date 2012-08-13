#ifndef FIELD_HPP
#define FIELD_HPP

#include "SceneObject.hpp"

#include <memory>
#include <tuple>
#include <vector>

class Cell;
class Point;
class Size;
enum class CellItem;

class Field : public SceneObject
{
public:
   Field(const std::string& name, const Point& pos, const Size& size);
   virtual ~Field();

   Field(const Field&) = delete;
   Field& operator=(const Field&) = delete;

   void Update(int elapsed_time) override;

   int GetXCells() const;
   int GetYCells() const;
   std::vector<std::shared_ptr<Cell>> GetCells() const;

   std::shared_ptr<Cell> GetCellFromPosition(const Point& pos) const;
   std::shared_ptr<Cell> GetCellFromCoordinates(int cell_x, int cell_y) const;

   std::shared_ptr<Cell> GetCellAboveOf(int cell_x, int cell_y) const;
   std::shared_ptr<Cell> GetCellBelowOf(int cell_x, int cell_y) const;
   std::shared_ptr<Cell> GetCellLeftOf(int cell_x, int cell_y) const;
   std::shared_ptr<Cell> GetCellRightOf(int cell_x, int cell_y) const;

private:
   Size GetCellSize() const;
   std::tuple<int, int> IndexToFieldPos(int index) const;
   int FieldPosToIndex(int cell_x, int cell_y) const;

   bool ShouldCellGetItem() const;
   CellItem GetRandomCellItem() const;

   int mXCells;
   int mYCells;
   std::vector<std::shared_ptr<Cell>> mCells;
};

#endif // FIELD_HPP
