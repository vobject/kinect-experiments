#include "GlRenderer.hpp"
#include "NuiBackground.hpp"
#include "PaintApp.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

GlRenderer::GlRenderer()
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
   glHint(GL_LINE_SMOOTH_HINT, GL_NICEST);

   glEnable(GL_BLEND);
   glEnable(GL_LINE_SMOOTH);
}

GlRenderer::~GlRenderer()
{

}

void GlRenderer::PreRender()
{
   // Screen size might have changed.
   mScreen = SDL_GetVideoSurface();

   glViewport(0, 0, mScreen->w, mScreen->h);
   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();
   glOrtho(0.0, mScreen->w, mScreen->h, 0.0, -1.0, 1.0);

   glClear(GL_COLOR_BUFFER_BIT);
}

void GlRenderer::PostRender()
{
   SDL_GL_SwapBuffers();
}

void GlRenderer::Render(const std::shared_ptr<NuiBackground>& bg)
{
   Size img_size = {0, 0};
   const auto img = bg->GetImage(img_size);

   // Create the OpenGL texture map
   glEnable(GL_TEXTURE_2D);
//   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, img_size.Width, img_size.Height,
                1, GL_RGB, GL_UNSIGNED_BYTE, img);

   glColor3f(1.0f, 1.0f, 1.0f);
   glBegin(GL_QUADS);
      glTexCoord2f(0.0f, 0.0f); glVertex2f(0.0f, 0.0f);
      glTexCoord2f(1.0f, 0.0f); glVertex2f(mScreen->w, 0.0f);
      glTexCoord2f(1.0f, 1.0f); glVertex2f(mScreen->w, mScreen->h);
      glTexCoord2f(0.0f, 1.0f); glVertex2f(0.0f, mScreen->h);
   glEnd();
   glDisable(GL_TEXTURE_2D);
}

void GlRenderer::Render(const std::shared_ptr<PaintStatus>& status)
{
   // Redraw the previous drawings.
   glColor3f(1.0f, 1.0f, 0.0f);
   glLineWidth(4.0f);
   for (const auto& line : status->lines)
   {
      if (line.empty()) {
         continue;
      }

      glBegin(GL_LINE_STRIP);
         for (const auto& pos : line)
         {
            glVertex2i(pos.X, pos.Y);
         }
      glEnd();
   }

   // Show the currently active drawing.
   constexpr auto rect_size = 8_px;
   glColor3f(1.0f, 1.0f, 1.0f);
   for (const auto& pt : status->active_line)
   {
      glBegin(GL_POLYGON);
         glVertex2i(pt.X, pt.Y);
         glVertex2i(pt.X + rect_size, pt.Y);
         glVertex2i(pt.X + rect_size, pt.Y + rect_size);
         glVertex2i(pt.X, pt.Y + rect_size);
      glEnd();
   }
}
