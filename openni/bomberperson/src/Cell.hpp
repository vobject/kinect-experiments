#ifndef CELL_HPP
#define CELL_HPP

#include "SceneObject.hpp"

enum class CellType
{
   Floor,
   IndestructibleWall,
   DestructibleWall
};

//enum class CellItem
//{
//   None,
//   VerticalExplosion,
//   HorizontalExplosion
//};

class Cell : public SceneObject
{
public:
   Cell(const std::string& name, int field_pos_x, int field_pos_y, CellType type);
   virtual ~Cell();

   Cell(const Cell&) = delete;
   Cell& operator=(const Cell&) = delete;

   void Update(int elapsed_time) override;

//   int GetFieldPositionX() const;
//   int GetFieldPositionY() const;

   CellType GetType() const;
   void SetType(CellType type);

   bool Blocking() const;

//   CellItem GetItem() const;
//   void SetItem(CellItem item);

private:
   // (X,Y) index on the playing field.
   const int mFieldPosX;
   const int mFieldPosY;

   CellType mType;
//   CellItem mItem = CellItem::None;
};

#endif // CELL_HPP
