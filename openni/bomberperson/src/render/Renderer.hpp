#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>

class Field;
class Cell;
class Player;
class Bomb;
class Explosion;
class SceneObject;

class Renderer
{
public:
   Renderer() { }
   virtual ~Renderer() { }

   virtual void PreRender() { }
   virtual void PostRender() { }
   virtual void Render(const std::shared_ptr<Field>& field) = 0;
   virtual void Render(const std::shared_ptr<Cell>& cell) = 0;
   virtual void Render(const std::shared_ptr<Player>& player) = 0;
   virtual void Render(const std::shared_ptr<Bomb>& bomb) = 0;
   virtual void Render(const std::shared_ptr<Explosion>& explosion) = 0;
   virtual void Render(const std::shared_ptr<SceneObject>& obj) = 0;
};

#endif // RENDERER_HPP
