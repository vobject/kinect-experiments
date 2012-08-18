#include "Explosion.hpp"

Explosion::Explosion(const std::string& name, const ExplosionType type)
   : mType(type)
{
   SetResourceId(name);
   SetSize({ 25, 25 });
}

Explosion::~Explosion()
{

}

void Explosion::Update(const int elapsed_time)
{
   mLifeTime += elapsed_time;

   if (mLifeTime >= DEFAULT_LIFETIME)
   {
      SetAlive(false);
   }
}

ExplosionType Explosion::GetType() const
{
   return mType;
}
