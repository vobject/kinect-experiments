#ifndef ENEMY_HPP
#define ENEMY_HPP

#include "Sprite.hpp"

class Enemy : public Sprite
{
public:
   Enemy(const SpriteResource& res, bool looping = false);
   virtual ~Enemy();

   Enemy(const Enemy&) = delete;
   Enemy& operator=(const Enemy&) = delete;

//   void Update(int elapsed_time) override;

private:

};

#endif // ENEMY_HPP
