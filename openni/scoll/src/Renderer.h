#ifndef RENDERER_H
#define RENDERER_H

#include <memory>

class Renderer
{
public:
   Renderer();
   virtual ~Renderer();

   virtual bool PreRender();
   virtual bool PostRender();

private:
   Renderer(const Renderer&);
   const Renderer& operator=(const Renderer&);
};

#endif // RENDERER_H
