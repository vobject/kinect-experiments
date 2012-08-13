#ifndef CELL_HPP
#define CELL_HPP

#include "SceneObject.hpp"

class Field;
class Bomb;
class Explosion;

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
   Cell(const std::string& name,
        int field_pos_x,
        int field_pos_y,
        const Field& field,
        CellType type);
   virtual ~Cell();

   Cell(const Cell&) = delete;
   Cell& operator=(const Cell&) = delete;

   void Update(int elapsed_time) override;

   CellType GetType() const;
   void SetType(CellType type);

   std::shared_ptr<Cell> GetTopCell() const;
   std::shared_ptr<Cell> GetDownCell() const;
   std::shared_ptr<Cell> GetLeftCell() const;
   std::shared_ptr<Cell> GetRightCell() const;

   bool IsBlocking() const;

   bool HasBomb() const;
   std::shared_ptr<Bomb> GetBomb() const;
   void SetBomb(const std::shared_ptr<Bomb>& bomb);

   bool HasExplosion() const;
   std::shared_ptr<Explosion> GetExplosion() const;
   void SetExplosion(const std::shared_ptr<Explosion>& explosion);

//   CellItem GetItem() const;
//   void SetItem(CellItem item);

private:
   // (X,Y) index on the playing field.
   const int mFieldPosX;
   const int mFieldPosY;
   const Field& mField;

   CellType mType;
//   CellItem mItem = CellItem::None;

   std::shared_ptr<Bomb> mBomb;
   std::shared_ptr<Explosion> mExplosion;
};

#endif // CELL_HPP
