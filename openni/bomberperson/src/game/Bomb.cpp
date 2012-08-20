#include "Bomb.hpp"
#include "Cell.hpp"
#include "Explosion.hpp"

Bomb::Bomb(const std::string& name, const std::shared_ptr<Cell>& cell)
   : mParentCell(cell)
{
   SetResourceId(name);
}

Bomb::~Bomb()
{

}

void Bomb::Update(const int elapsed_time)
{
   mLifeTime += elapsed_time;

   if (mLifeTime >= DEFAULT_LIFETIME)
   {
      SetAlive(false);

      PlantCenterExplosion();
      PlantRangeExplosion(Direction::Up);
      PlantRangeExplosion(Direction::Down);
      PlantRangeExplosion(Direction::Left);
      PlantRangeExplosion(Direction::Right);
   }
}

int Bomb::GetRange() const
{
   return mRange;
}

void Bomb::SetRange(const int range)
{
   mRange = range;
}

void Bomb::Detonate()
{
   mLifeTime = DEFAULT_LIFETIME;
}

void Bomb::PlantCenterExplosion() const
{
   auto explosion = std::make_shared<Explosion>("explosion",
                                                ExplosionType::Crossway);
   explosion->SetSize(mParentCell->GetSize());
   explosion->SetPosition(mParentCell->GetPosition());
   mParentCell->SetExplosion(explosion);
}

void Bomb::PlantRangeExplosion(Direction dir) const
{
   std::shared_ptr<Cell> range_cell = mParentCell->GetCell(dir);

   int range_to_go = GetRange();

   while (range_cell && range_to_go)
   {
      if (CellType::IndestructibleWall == range_cell->GetType()) {
         break;
      }

      if (range_cell->HasBomb())
      {
         range_cell->GetBomb()->Detonate();
         break;
      }

      // TODO: Break if an existing explosion has the same orientation
      //  as this one, e.g. Vertical or Horizontal.

      // TODO: Select the right ExplosionType.
      auto range_exp = std::make_shared<Explosion>("explosion",
                                                   ExplosionType::Crossway);
      range_exp->SetSize(range_cell->GetSize());
      range_exp->SetPosition(range_cell->GetPosition());
      range_cell->SetExplosion(range_exp);

      if (CellType::DestructibleWall == range_cell->GetType())
      {
         // FIXME: This has a problem: when the exploding bomb destroys
         //  a wall and triggers another bomb with a greater range,
         //  the wall behind the first wall would also be destroyed
         //  at the same time.
         // Maybe this could be avoided by introducing an ExplodingWall type.
         range_cell->SetType(CellType::Floor);
         break;
      }

      if (range_cell->HasItem())
      {
         range_cell->SetItem(CellItem::None);
         break;
      }

      range_cell = range_cell->GetCell(dir);
      range_to_go--;
   }
}
