#ifndef BOMB_HPP
#define BOMB_HPP

#include "SceneObject.hpp"
#include "Utils.hpp"

#include <memory>
#include <string>

class Explosion;

class Bomb : public SceneObject
{
public:
   Bomb(const std::string& name);
   virtual ~Bomb();

   Bomb(const Bomb&) = delete;
   Bomb& operator=(const Bomb&) = delete;

   void Update(int elapsed_time) override;

   int GetRange() const;
   void SetRange(int range);

   std::shared_ptr<Explosion> GetExplosion();

private:
   static const int DEFAULT_LIFETIME = 3000_ms;

   int mLifeTime = 0;
   int mRange = 1;
};

#endif // BOMB_HPP
