#include "Bomb.hpp"
#include "Explosion.hpp"
#include "Utils.hpp"

Bomb::Bomb(const std::string& name)
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

std::shared_ptr<Explosion> Bomb::GetExplosion()
{
   auto explosion = std::make_shared<Explosion>("explosion_1");
   explosion->SetPosition(GetPosition());
   return explosion;
}
