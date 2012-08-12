#ifndef EXPLOSION_HPP
#define EXPLOSION_HPP

#include "SceneObject.hpp"
#include "Utils.hpp"

enum class ExplosionType
{
   CrosswayExplosion,
   VerticalExplosion,
   HorizontalExplosion
};

class Explosion : public SceneObject
{
public:
   Explosion(const std::string& name);
   virtual ~Explosion();

   Explosion(const Explosion&) = delete;
   Explosion& operator=(const Explosion&) = delete;

   void Update(int elapsed_time) override;

   ExplosionType GetType() const;
   void SetType(ExplosionType type);

//   int GetRange() const;
//   void SetRange(int range);

private:
   static const int DEFAULT_LIFETIME = 1000_ms;

   ExplosionType mType = ExplosionType::CrosswayExplosion;
   int mLifeTime = 0;
//   int mRange = 1;
};

#endif // EXPLOSION_HPP
