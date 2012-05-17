#ifndef RENDERER_HPP
#define RENDERER_HPP

#include <memory>
#include <list>

class KinectBackground;
class PaintStatus;

class Renderer
{
public:
   Renderer() { }
   virtual ~Renderer() { }

   virtual void PreRender() { }
   virtual void PostRender() { }
   virtual void Render(const std::shared_ptr<KinectBackground>& bg) = 0;
   virtual void Render(const std::shared_ptr<PaintStatus>& status) = 0;
};

#endif // RENDERER_HPP
