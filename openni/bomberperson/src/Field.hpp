#ifndef FIELD_HPP
#define FIELD_HPP

#include "SceneObject.hpp"

#include <memory>
#include <vector>

class Cell;

class Field : public SceneObject
{
public:
   Field(const std::string& name);
   virtual ~Field();

   Field(const Field&) = delete;
   Field& operator=(const Field&) = delete;

   void Update(int elapsed_time) override;

   int GetXCells() const;
   int GetYCells() const;
   std::vector<std::shared_ptr<Cell>> GetCells() const;

//   std::shared_ptr<Cell> GetCell(int cell_pos_x, int cell_pos_y) const;
//   std::shared_ptr<Cell> GetCellAboveOf(int cell_x, int cell_y) const;
//   std::shared_ptr<Cell> GetCellBelowOf(int cell_x, int cell_y) const;
//   std::shared_ptr<Cell> GetCellLeftOf(int cell_x, int cell_y) const;
//   std::shared_ptr<Cell> GetCellRightOf(int cell_x, int cell_y) const;

private:
   // TODO: Helper methods to convert from 2-dimensional indexing to 1D
   //  and the other way around.

   int mXCells;
   int mYCells;
   std::vector<std::shared_ptr<Cell>> mCells;
};

#endif // FIELD_HPP
