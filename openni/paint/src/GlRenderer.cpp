#include "GlRenderer.hpp"
#include "KinectBackground.hpp"
#include "PaintApp.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

GlRenderer::GlRenderer()
   : mScreen(SDL_GetVideoSurface())
{
   glClearColor(.0, .0, .0, .0);

   glEnable(GL_TEXTURE_2D);

   glViewport(0, 0, mScreen->w, mScreen->h);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(0, mScreen->w, mScreen->h, 0, 1, -1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();
}

GlRenderer::~GlRenderer()
{

}

void GlRenderer::PreRender()
{
   glClear(GL_COLOR_BUFFER_BIT);
}

void GlRenderer::PostRender()
{
   SDL_GL_SwapBuffers();
}

void GlRenderer::Render(const std::shared_ptr<KinectBackground>& bg)
{
   Size img_size = {0, 0};
   const auto img = bg->GetImage(img_size);

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, mScreen->w, mScreen->h, 0, -1.0, 1.0);

   // Create the OpenGL texture map
   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, img_size.Width, img_size.Height,
                1, GL_RGB, GL_UNSIGNED_BYTE, img);

   glColor3f(0.0f, 0.0f, 0.0f);

   glBegin(GL_QUADS);
      // upper left
      glTexCoord2f(0, 0);
      glVertex2f(0, 0);
      // upper right
      glTexCoord2f(1, 0);
      glVertex2f(mScreen->w, 0);
      // bottom right
      glTexCoord2f(1, 1);
      glVertex2f(mScreen->w, mScreen->h);
      // bottom left
      glTexCoord2f(0, 1);
      glVertex2f(0, mScreen->h);
   glEnd();
   glPopMatrix();
}

void GlRenderer::Render(const std::shared_ptr<PaintStatus>& status)
{
   glPushMatrix();
   glColor3f(1.0f, 0.5f, 1.0f);

   // Redraw the previous drawings.
   glLineWidth(2);
   for (const auto& line : status->lines)
   {
      if (line.empty()) {
         continue;
      }

      Point src_pos = line.at(0);
      for (const auto& dest_pos : line)
      {
         glBegin(GL_LINES);
            glVertex2i(src_pos.X, src_pos.Y);
            glVertex2i(dest_pos.X, dest_pos.Y);
         glEnd();

         src_pos = dest_pos;
      }
   }

   // Show the currently active drawing.
   constexpr auto rect_size = 6_px;
   for (const auto& pt : status->active_line)
   {
      glBegin(GL_POLYGON);
         glVertex2i(pt.X, pt.Y);
         glVertex2i(pt.X + rect_size, pt.Y);
         glVertex2i(pt.X + rect_size, pt.Y + rect_size);
         glVertex2i(pt.X, pt.Y + rect_size);
      glEnd();
   }

   glPopMatrix();
}
