#include "GlWindow.hpp"

#include <GL/gl.h>
#include <GL/glu.h>

#include <iostream>

GlWindow::GlWindow(const Size& res, const std::string& text)
   : Window(res)
{
   // Bring up SDL's video system...
#ifdef WIN32
   if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER)) {
#else
   if (0 > SDL_Init(SDL_INIT_VIDEO | SDL_INIT_EVENTTHREAD | SDL_INIT_TIMER)) {
#endif
      throw "Cannot init SDL video subsystem.";
   }
   atexit(SDL_Quit); // ...make sure everything gets cleaned up at exit...

//   SDL_GL_SetAttribute(SDL_GL_RED_SIZE,        8);
//   SDL_GL_SetAttribute(SDL_GL_GREEN_SIZE,      8);
//   SDL_GL_SetAttribute(SDL_GL_BLUE_SIZE,       8);
//   SDL_GL_SetAttribute(SDL_GL_ALPHA_SIZE,      8);
//
//   SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,      16);
//   SDL_GL_SetAttribute(SDL_GL_BUFFER_SIZE,        32);
//
//   SDL_GL_SetAttribute(SDL_GL_ACCUM_RED_SIZE,    8);
//   SDL_GL_SetAttribute(SDL_GL_ACCUM_GREEN_SIZE,    8);
//   SDL_GL_SetAttribute(SDL_GL_ACCUM_BLUE_SIZE,    8);
//   SDL_GL_SetAttribute(SDL_GL_ACCUM_ALPHA_SIZE,    8);
//
//   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLEBUFFERS,  1);
//   SDL_GL_SetAttribute(SDL_GL_MULTISAMPLESAMPLES,  2);

   SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1);

   // ...and finally create the window.
   mScreen = SDL_SetVideoMode(mRes.Width,
                              mRes.Height,
                              32,
                              SDL_HWSURFACE | SDL_OPENGL);
   if (!mScreen) {
      throw "SDL_SetVideoMode() failed.";
   }
   SDL_WM_SetCaption(text.c_str(), NULL);

   mGlFont.reset(new GlFont("res/font/VeraMono.ttf", 16_pt, { 0xaf, 0xa0, 0xaa }));

   glClearColor(0, 1.0f, 0, 0);

   glEnable(GL_TEXTURE_2D);

   glViewport(0, 0, mRes.Width, mRes.Height);

   glMatrixMode(GL_PROJECTION);
   glLoadIdentity();

   glOrtho(0, mRes.Width, mRes.Height, 0, 1, -1);

   glMatrixMode(GL_MODELVIEW);
   glLoadIdentity();

   mFrameTimer = SDL_AddTimer(1000_ms, FrameTimerCallback, this);
}

GlWindow::~GlWindow()
{
   SDL_RemoveTimer(mFrameTimer);
   SDL_FreeSurface(mScreen);
}

void GlWindow::Blit(const void* data, const Size& data_size, const Point& dest)
{
   // Copied from SimpleViewer

   // Setup the OpenGL viewpoint
   glMatrixMode(GL_PROJECTION);
   glPushMatrix();
   glLoadIdentity();
   glOrtho(0, mRes.Width, mRes.Height, 0, -1.0, 1.0);

   // Create the OpenGL texture map
   glTexParameteri(GL_TEXTURE_2D, GL_GENERATE_MIPMAP_SGIS, GL_TRUE);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, data_size.Width, data_size.Height,
                1, GL_RGB, GL_UNSIGNED_BYTE, data);

   // Display the OpenGL texture map
   glColor4f(1, 1, 1, 1);

   glBegin(GL_QUADS);
      // upper left
      glTexCoord2f(0, 0);
      glVertex2f(0, 0);
      // upper right
      glTexCoord2f(1, 0);
      glVertex2f(mRes.Width, 0);
      // bottom right
      glTexCoord2f(1, 1);
      glVertex2f(mRes.Width, mRes.Height);
      // bottom left
      glTexCoord2f(0, 1);
      glVertex2f(0, mRes.Height);
   glEnd();
}

void GlWindow::Clear()
{
   glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void GlWindow::Flip()
{
   mTextBuf.str("");
#ifdef NDEBUG
   mTextBuf << "Release | ";
#else
   mTextBuf << "Debug | ";
#endif
   mTextBuf << mFPS << " FPS";
   WriteText(mTextBuf.str(), {0, 0});
   mFrameCount++;

   SDL_GL_SwapBuffers();
}

//void GlWindow::DrawRect(
//   const int x_pos,
//   const int y_pos,
//   const unsigned int size,
//   const unsigned int color /* = 0xffffffff */
//)
//{
////   SDL_Rect rect = { (Sint16)(x_pos - (size / 2)), (Sint16)(y_pos - (size / 2)), (Uint16)size, (Uint16)size };
////
////   SDL_FillRect(mSurface, &rect, color);
//}

//void GlWindow::DrawLine(int x1, int y1, int x2, int y2, unsigned int color /*= 0xffffffff*/)
//{
//   // based on http://alawibaba.com/projects/whiteboard/drawing-SDL.c
//
////#define SGN(x) ((x)>0 ? 1 : ((x)==0 ? 0:(-1)))
////#define ABS(x) ((x)>0 ? (x) : (-x))
////
////   int lg_delta;
////   int sh_delta;
////   int cycle;
////   int lg_step;
////   int sh_step;
////
////   lg_delta = x2 - x1;
////   sh_delta = y2 - y1;
////   lg_step = SGN(lg_delta);
////   lg_delta = ABS(lg_delta);
////   sh_step = SGN(sh_delta);
////   sh_delta = ABS(sh_delta);
////
////   if (sh_delta < lg_delta)
////   {
////      cycle = lg_delta >> 1;
////      while (x1 != x2)
////      {
////         DrawPixel(x1, y1, color);
////
////         cycle += sh_delta;
////         if (cycle > lg_delta)
////         {
////            cycle -= lg_delta;
////            y1 += sh_step;
////         }
////         x1 += lg_step;
////      }
////      DrawPixel(x1, y1, color);
////   }
////
////   cycle = sh_delta >> 1;
////   while (y1 != y2)
////   {
////      DrawPixel(x1, y1, color);
////
////      cycle += lg_delta;
////      if (cycle > sh_delta)
////      {
////         cycle -= sh_delta;
////         x1 += lg_step;
////      }
////      y1 += sh_step;
////   }
////   DrawPixel(x1, y1, color);
//}

void GlWindow::DrawRect(const Point& pos, const int size)
{

}

void GlWindow::DrawLine(const Point& src_pos, const Point& dest_pos)
{

}

void GlWindow::WriteText(const std::string& text, const Point& point)
{
   mGlFont->DrawText(text, point.X, point.Y);
}

//void GlWindow::DrawPixel(int x_pos, int y_pos, unsigned int color /*= 0xffffffff*/)
//{
////   const size_t bpp = mSurface->format->BytesPerPixel;
////   const size_t offset = (mSurface->pitch * y_pos) + (x_pos * bpp);
////
////   SDL_LockSurface(mSurface);
////   memcpy(static_cast<char*>(mSurface->pixels) + offset, &color, bpp);
////   SDL_UnlockSurface(mSurface);
//}

Uint32 GlWindow::FrameTimerCallback(const Uint32 interval, void* param)
{
   auto obj = static_cast<GlWindow*>(param);

   obj->mFPS = (int)((obj->mFrameCount / (float)interval) * 1000_ms);
   obj->mFrameCount = 0;

   LOG(logDEBUG) << "FPS: " << obj->mFPS;

   return interval;
}
