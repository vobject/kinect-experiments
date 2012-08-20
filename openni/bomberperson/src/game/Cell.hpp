#ifndef CELL_HPP
#define CELL_HPP

#include "SceneObject.hpp"

#include <memory>

class Field;
class Bomb;
class Explosion;

enum class CellType
{
   Floor,
   IndestructibleWall,
   DestructibleWall
};

enum class CellItem
{
   None,
   Speed,
   BombRange,
   BombSupply,
   CELL_ITEM_COUNT
};

//class CellObject
//{
//
//};

//enum class ExtraType
//{
//   Speed,
//   BombRange,
//   BombSupply
//};
//
//class Extra : public SceneObject
//{
//
//};
//
//class Wall : public SceneObject
//{
//
//};

//class Cell;
//
//class Item : public Cell
//{
//   //ctor
//   //dtor
//
//};
//
//class Indestructible : public Cell
//{
//
//};
//
//class Destructible : public Cell
//{
//
//};
//
//class Exploding??? : public Cell
//{
//
//};

class Cell : public SceneObject
{
public:
   Cell(const std::string& name,
        int field_pos_x,
        int field_pos_y,
        const std::shared_ptr<Field>& field);
   virtual ~Cell();

   Cell(const Cell&) = delete;
   Cell& operator=(const Cell&) = delete;

   void Update(int elapsed_time) override;

   CellType GetType() const; // TODO: Remove Me!
   void SetType(CellType type);

   bool HasBomb() const;
   std::shared_ptr<Bomb> GetBomb() const;
   void SetBomb(const std::shared_ptr<Bomb>& bomb);

   bool HasExplosion() const;
   std::shared_ptr<Explosion> GetExplosion() const;
   void SetExplosion(const std::shared_ptr<Explosion>& explosion);

   bool HasItem() const;
   CellItem GetItem() const;
   void SetItem(CellItem item);

   bool IsBlocking() const;
   bool IsDestructible() const;

   std::shared_ptr<Cell> GetCell(Direction dir) const;

private:
   // (X,Y) index on the playing field.
   const int mFieldPosX;
   const int mFieldPosY;
   const std::shared_ptr<Field> mField;

   CellType mType;
   CellItem mItem;

   // Will be dynamically casted to get its derived type.
   // Yes, this is ugly, but still better than maintaining two pointers
   //  with potentially contradictory state -> a cell can not have both,
   //  a bomb and an explosion, but the public interface allows consecutive
   //  calls to SetBomb() and SetExplosion().
   std::shared_ptr<SceneObject> mBombOrExplosion;
};

#endif // CELL_HPP
