#include "GlNoRes.hpp"
#include "../utils/Utils.hpp"

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

GlNoRes::GlNoRes(const Size res)
{
   if (0 > SDL_Init(SDL_INIT_VIDEO)) {
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit);

   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);
   const auto screen = SDL_SetVideoMode(res.Width,
                                        res.Height,
                                        32,
                                        SDL_OPENGL | SDL_RESIZABLE);
   if (!screen) {
      throw "SDL_SetVideoMode() failed.";
   }

   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

   glEnable(GL_BLEND);
   glEnable(GL_LINE_SMOOTH);
}

GlNoRes::~GlNoRes()
{

}

void GlNoRes::PreRender()
{
   // Screen size might have changed.
   mScreen = SDL_GetVideoSurface();

   glViewport(0, 0, mScreen->w, mScreen->h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, mScreen->w, mScreen->h, 0.0, -1.0, 1.0);

   glClear(GL_COLOR_BUFFER_BIT);
}

void GlNoRes::PostRender()
{
   SDL_GL_SwapBuffers();
}

void GlNoRes::Render(const std::shared_ptr<Field>& field)
{
   // TODO: Implement Me!
}

void GlNoRes::Render(const std::shared_ptr<Cell>& cell)
{
   // TODO: Implement Me!
}

void GlNoRes::Render(const std::shared_ptr<Player>& player)
{
   // TODO: Implement Me!
}

void GlNoRes::Render(const std::shared_ptr<Bomb>& bomb)
{
   // TODO: Implement Me!
}

void GlNoRes::Render(const std::shared_ptr<Explosion>& explosion)
{
   // TODO: Implement Me!
}

void GlNoRes::Render(const std::shared_ptr<SceneObject>& obj)
{
   // TODO: Implement Me!
}
