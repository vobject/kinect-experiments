#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <list>

class Background;
class Player;
class Enemy;
class Sprite;

class Renderer
{
public:
   Renderer() { }
   virtual ~Renderer() { }

   virtual void PreRender() { }
   virtual void PostRender() { }
   virtual void Render(const std::shared_ptr<Background>& bg) = 0;
   virtual void Render(const std::shared_ptr<Player>& player) = 0;
   virtual void Render(const std::shared_ptr<Enemy>& enemy) = 0;
   virtual void Render(const std::list<std::shared_ptr<Sprite>>& objects) = 0;
};

#endif // RENDERER_HPP
