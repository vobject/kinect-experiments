#ifndef BOMB_HPP
#define BOMB_HPP

#include "SceneObject.hpp"
#include "Utils.hpp"

#include <memory>
#include <string>

class Cell;

class Bomb : public SceneObject
{
public:
   Bomb(const std::string& name, const std::shared_ptr<Cell>& cell);
   virtual ~Bomb();

   Bomb(const Bomb&) = delete;
   Bomb& operator=(const Bomb&) = delete;

   void Update(int elapsed_time) override;

   int GetRange() const;
   void SetRange(int range);

   void Detonate();

private:
   static const int DEFAULT_LIFETIME = 3000_ms;

   void PlantCenterExplosion() const;
   void PlantTopRangeExplosion() const;
   void PlantDownRangeExplosion() const;
   void PlantLeftRangeExplosion() const;
   void PlantRightRangeExplosion() const;

   std::shared_ptr<Cell> mParentCell;
   int mLifeTime = 0;
   int mRange = 1;
};

#endif // BOMB_HPP
