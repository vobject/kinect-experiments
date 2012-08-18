#include "Bomb.hpp"
#include "Cell.hpp"
#include "Explosion.hpp"

Bomb::Bomb(const std::string& name, const std::shared_ptr<Cell>& cell)
   : mParentCell(cell)
{
   SetResourceId(name);
   SetSize({ 15, 15 });
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
      PlantTopRangeExplosion();
      PlantDownRangeExplosion();
      PlantLeftRangeExplosion();
      PlantRightRangeExplosion();
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
   auto explosion = std::make_shared<Explosion>("explosion_center",
                                                ExplosionType::Crossway);
   explosion->SetPosition({ mParentCell->GetPosition().X + 1,
                            mParentCell->GetPosition().Y + 1});
   mParentCell->SetExplosion(explosion);
}

void Bomb::PlantTopRangeExplosion() const
{
   auto range_cell = mParentCell->GetTopCell();
   int range_to_go = GetRange();

   while (range_cell && range_to_go)
   {
      if (CellType::IndestructibleWall == range_cell->GetType()) {
         break;
      }

      auto range_exp = std::make_shared<Explosion>("explosion_top",
                                                   ExplosionType::Vertical);
      range_exp->SetPosition({ range_cell->GetPosition().X + 1,
                               range_cell->GetPosition().Y + 1});
      range_cell->SetExplosion(range_exp);

      if (CellType::DestructibleWall == range_cell->GetType())
      {
         range_cell->SetType(CellType::Floor);
         break;
      }

      if (range_cell->HasItem())
      {
         range_cell->SetItem(CellItem::None);
         break;
      }

      if (range_cell->HasBomb())
      {
         range_cell->GetBomb()->Detonate();
      }

      range_cell = range_cell->GetTopCell();
      range_to_go--;
   }
}

void Bomb::PlantDownRangeExplosion() const
{
   auto range_cell = mParentCell->GetDownCell();
   int range_to_go = GetRange();

   while (range_cell && range_to_go)
   {
      if (CellType::IndestructibleWall == range_cell->GetType()) {
         break;
      }

      auto range_exp = std::make_shared<Explosion>("explosion_down",
                                                   ExplosionType::Vertical);
      range_exp->SetPosition({ range_cell->GetPosition().X + 1,
                               range_cell->GetPosition().Y + 1});
      range_cell->SetExplosion(range_exp);

      if (CellType::DestructibleWall == range_cell->GetType())
      {
         range_cell->SetType(CellType::Floor);
         break;
      }

      if (range_cell->HasItem())
      {
         range_cell->SetItem(CellItem::None);
         break;
      }

      if (range_cell->HasBomb())
      {
         range_cell->GetBomb()->Detonate();
      }

      range_cell = range_cell->GetDownCell();
      range_to_go--;
   }
}

void Bomb::PlantLeftRangeExplosion() const
{
   auto range_cell = mParentCell->GetLeftCell();
   int range_to_go = GetRange();

   while (range_cell && range_to_go)
   {
      if (CellType::IndestructibleWall == range_cell->GetType()) {
         break;
      }

      auto range_exp = std::make_shared<Explosion>("explosion_left",
                                                   ExplosionType::Horizontal);
      range_exp->SetPosition({ range_cell->GetPosition().X + 1,
                               range_cell->GetPosition().Y + 1});
      range_cell->SetExplosion(range_exp);

      if (CellType::DestructibleWall == range_cell->GetType())
      {
         range_cell->SetType(CellType::Floor);
         break;
      }

      if (range_cell->HasItem())
      {
         range_cell->SetItem(CellItem::None);
         break;
      }

      if (range_cell->HasBomb())
      {
         range_cell->GetBomb()->Detonate();
      }

      range_cell = range_cell->GetLeftCell();
      range_to_go--;
   }
}

void Bomb::PlantRightRangeExplosion() const
{
   auto range_cell = mParentCell->GetRightCell();
   int range_to_go = GetRange();

   while (range_cell && range_to_go)
   {
      if (CellType::IndestructibleWall == range_cell->GetType()) {
         break;
      }

      auto range_exp = std::make_shared<Explosion>("explosion_right",
                                                   ExplosionType::Horizontal);
      range_exp->SetPosition({ range_cell->GetPosition().X + 1,
                               range_cell->GetPosition().Y + 1});
      range_cell->SetExplosion(range_exp);

      if (CellType::DestructibleWall == range_cell->GetType())
      {
         range_cell->SetType(CellType::Floor);
         break;
      }

      if (range_cell->HasItem())
      {
         range_cell->SetItem(CellItem::None);
         break;
      }

      if (range_cell->HasBomb())
      {
         range_cell->GetBomb()->Detonate();
      }

      range_cell = range_cell->GetRightCell();
      range_to_go--;
   }
}
