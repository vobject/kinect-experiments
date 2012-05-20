#include "GlRenderer.hpp"
#include "Kinect.hpp"
#include "ResourceCache.hpp"
#include "Sprite.h"
#include "Background.h"
#include "Player.hpp"
#include "Utils.hpp"

#include <SDL.h>

#include <GL/gl.h>
#include <GL/glu.h>

#include <string>

GlRenderer::GlRenderer(const std::shared_ptr<ResourceCache>& res)
   : mResCache(res)
{
   glClearColor(0.0f, 0.0f, 0.0f, 0.0f);

   glEnable(GL_BLEND);
   glEnable(GL_TEXTURE_2D);
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

void GlRenderer::Render(const std::shared_ptr<Background>& bg)
{
   if (!bg->IsVisible()) {
      return;
   }

   const auto frame = mResCache->GetBackground(bg->GetResourceId()).GetFrame();
   if (!frame) {
      throw "No frame associated with background";
   }

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, mScreen->w, mScreen->h, 0, -1.0, 1.0);

   // Create the OpenGL texture map
//   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame->w, frame->h,
                1, GL_BGRA, GL_UNSIGNED_BYTE, frame->pixels);

   // Display the OpenGL texture map
   glColor3f(1.0f, 1.0f, 1.0f);

   const Point bg_pos = bg->GetPosition();
   const Size bg_size = bg->GetSize();

   // FIXME: enable correct scrolling.
   const float x_left_vertex = 0;//static_cast<float>(bg_pos.X) / bg_size.Width;
   const float y_left_vertex = static_cast<float>(bg_pos.Y) / bg_size.Height;
   const float x_right_vertex = static_cast<float>(mScreen->w) / bg_size.Width;
   const float y_right_vertex = static_cast<float>(mScreen->h + bg_pos.Y) / bg_size.Height;

   glBegin(GL_QUADS);
     glTexCoord2f(x_left_vertex, y_left_vertex);   glVertex2f(0.0f + bg_pos.X, 0.0f);
     glTexCoord2f(x_right_vertex, y_left_vertex);  glVertex2f(mScreen->w + bg_pos.X, 0.0f);
     glTexCoord2f(x_right_vertex, y_right_vertex); glVertex2f(mScreen->w + bg_pos.X, mScreen->h);
     glTexCoord2f(x_left_vertex, y_right_vertex);  glVertex2f(0.0f + bg_pos.X, mScreen->h);
   glEnd();
   glPopMatrix();
}

void GlRenderer::Render(const std::shared_ptr<Player>& player)
{
   //  TODO: Center the Actor with its XCenter to the middle of the window

   if (!player->IsVisible()) {
      return;
   }

   const auto frame = player->GetFrame();
   if (!frame) {
      throw "No frame associated with player";
   }

//   const double x_zoom = static_cast<double>(player->GetSize().Width) / orig_frame->GetSize().Width;
//   const double y_zoom = static_cast<double>(player->GetSize().Height) / orig_frame->GetSize().Height;
//   SDL_Surface* zoomed_frame = zoomSurface(static_cast<SDL_Surface*>(orig_frame->GetData()), x_zoom, y_zoom, 0);
//
//   const Uint32 colorkey = SDL_MapRGB(zoomed_frame->format, 0, 0, 0);
//   if (SDL_SetColorKey(zoomed_frame, SDL_RLEACCEL | SDL_SRCCOLORKEY, colorkey)) {
//      throw "SDL_SetColorKey failed";
//   }
//
//   SDL_Rect rect = { (Sint16)player->GetPosition().X, (Sint16)player->GetPosition().Y,
//                     (Uint16)player->GetSize().Width, (Uint16)player->GetSize().Height };
//   SDL_BlitSurface(zoomed_frame, NULL, mWindow->mSurface, &rect);
}

void GlRenderer::Render(const std::list<std::shared_ptr<Sprite>>& objects)
{
   for (const auto& obj : objects)
   {
      if (!obj->IsVisible()) {
         continue;
      }

//      // TODO: Get objects resources from resource manager
//      // TODO: Draw the objects resources in its current state to mSurface

      const auto res_id = obj->GetResourceId();

      if (res_id == "Rectangle")
      {
         glPushMatrix();
         glColor3f(1, 1, 1);
         glBegin(GL_POLYGON);
            glVertex2i(obj->GetPosition().X, obj->GetPosition().Y);
            glVertex2i(obj->GetPosition().X + obj->GetSize().Width, obj->GetPosition().Y);
            glVertex2i(obj->GetPosition().X + obj->GetSize().Width, obj->GetPosition().Y + obj->GetSize().Height);
            glVertex2i(obj->GetPosition().X, obj->GetPosition().Y + obj->GetSize().Height);
         glEnd();
         glPopMatrix();
      }
      else
      {
         RenderSprite(obj);
      }
   }
}

void GlRenderer::RenderSprite(const std::shared_ptr<Sprite>& obj) const
{
   const auto frame = mResCache->GetSprite(obj->GetResourceId()).GetFrame(obj->GetCurrentFrame());
   if (!frame) {
      throw "No texture associated with sprite";
   }

   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, mScreen->w, mScreen->h, 0, -1.0, 1.0);

   // Create the OpenGL texture map
   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, frame->w, frame->h,
                1, GL_BGRA, GL_UNSIGNED_BYTE, frame->pixels);

   // Display the OpenGL texture map
//   glColor3f(1., 1., 1.);

   glBegin(GL_QUADS);
      // upper left
      glTexCoord2f(0, 0);
      glVertex2f(obj->GetPosition().X, obj->GetPosition().Y);
      // upper right
      glTexCoord2f(1., 0);
      glVertex2f(obj->GetPosition().X + obj->GetSize().Width, obj->GetPosition().Y);
      // bottom right
      glTexCoord2f(1., 1);
      glVertex2f(obj->GetPosition().X + obj->GetSize().Width, obj->GetPosition().Y + obj->GetSize().Height);
      // bottom left
      glTexCoord2f(0, 1);
      glVertex2f(obj->GetPosition().X, obj->GetPosition().Y + obj->GetSize().Height);
   glEnd();
   glPopMatrix();
}
