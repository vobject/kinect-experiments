#include "GlRenderer.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

//GlRenderer::GlRenderer()
//{
//   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
//
//   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
//   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);
//
//   glEnable(GL_BLEND);
//   glEnable(GL_LINE_SMOOTH);
//}
//
//GlRenderer::~GlRenderer()
//{
//
//}
//
//void GlRenderer::PreRender()
//{
//   // Screen size might have changed.
//   mScreen = SDL_GetVideoSurface();
//
//   glViewport(0, 0, mScreen->w, mScreen->h);
//   glMatrixMode(GL_PROJECTION);
//   glLoadIdentity();
//   glOrtho(0.0, mScreen->w, mScreen->h, 0.0, -1.0, 1.0);
//
//   glClear(GL_COLOR_BUFFER_BIT);
//}
//
//void GlRenderer::PostRender()
//{
//   SDL_GL_SwapBuffers();
//}
//
//void GlRenderer::Render(const std::shared_ptr<Match>& level)
//{
//
//}
