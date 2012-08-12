#include "Explosion.hpp"
#include "Utils.hpp"

Explosion::Explosion(const std::string& name)
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

void Explosion::SetType(const ExplosionType type)
{
   mType = type;
}

//int Explosion::GetRange() const
//{
//   return mRange;
//}
//
//void Explosion::SetRange(const int range)
//{
//   mRange = range;
//}
