// This code was copied from:
//  http://www.gamedev.net/topic/284259-for-reference-using-sdl_ttf-with-opengl/page__view__findpost__p__3649811
// Changes were made where necessary.

#include "GlFont.hpp"

#include <SDL_image.h>

/* Quick utility function for texture creation */
static int power_of_two(const int input)
{
   int value = 1;

   while (value < input)
   {
      value <<= 1;
   }
   return value;
}

static GLuint SDL_GL_LoadTexture(SDL_Surface *surface, GLfloat *texcoord)
{
   /* Use the surface width and height expanded to powers of 2 */
   const int w = power_of_two(surface->w);
   const int h = power_of_two(surface->h);
   texcoord[0] = 0.0f;                    /* Min X */
   texcoord[1] = 0.0f;                    /* Min Y */
   texcoord[2] = (GLfloat)surface->w / w; /* Max X */
   texcoord[3] = (GLfloat)surface->h / h; /* Max Y */

   SDL_Surface* image = SDL_CreateRGBSurface(SDL_SWSURFACE, w, h, 32,
#if SDL_BYTEORDER == SDL_LIL_ENDIAN /* OpenGL RGBA masks */
         0x000000FF,
         0x0000FF00,
         0x00FF0000,
         0xFF000000
#else
         0xFF000000,
         0x00FF0000,
         0x0000FF00,
         0x000000FF
#endif
                  );
   if (!image) {
      return 0;
   }

   /* Save the alpha blending attributes */
   Uint32 saved_flags = surface->flags&(SDL_SRCALPHA | SDL_RLEACCELOK);
   Uint8 saved_alpha = surface->format->alpha;

   if ((saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA)
   {
      SDL_SetAlpha(surface, 0, 0);
   }

   /* Copy the surface into the GL texture image */
   SDL_Rect area = { 0, 0, static_cast<Uint16>(surface->w),
                           static_cast<Uint16>(surface->h) };
   SDL_BlitSurface(surface, &area, image, &area);

   /* Restore the alpha blending attributes */
   if ( (saved_flags & SDL_SRCALPHA) == SDL_SRCALPHA )
   {
      SDL_SetAlpha(surface, saved_flags, saved_alpha);
   }

   /* Create an OpenGL texture for the image */
   GLuint texture;
   glGenTextures(1, &texture);
   glBindTexture(GL_TEXTURE_2D, texture);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
   glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
   glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, w, h, 0, GL_RGBA, GL_UNSIGNED_BYTE, image->pixels);
   SDL_FreeSurface(image); /* No longer needed */

   return texture;
}

int GlFont::initCounter = 0;

GlFont::GlFont(const std::string& name, const int size, SDL_Color color)
   : mName(name)
   , mPointSize(size)
   , mForeground(color)
{
   if (!initCounter)
   {
      if (0 > TTF_Init()) {
         throw "Cannot init SDL ttf feature.";
      }
   }
   initCounter++;

   Init();
}

GlFont::~GlFont()
{
   initCounter--;

   if (!initCounter)
   {
      TTF_Quit();
   }
}

void GlFont::Init()
{
   ttfFont = TTF_OpenFont(mName.c_str(), mPointSize);
   if (!ttfFont) {
      TTF_Quit();
      throw "TTF_OpenFont() failed!";
   }

   height = TTF_FontHeight(ttfFont);
   ascent = TTF_FontAscent(ttfFont);
   descent = TTF_FontDescent(ttfFont);
   lineSkip = TTF_FontLineSkip(ttfFont);

   for (char c = MIN_GLYPH; c <= MAX_GLYPH; c++)
   {
      LoadChar(c);
   }
}

//void GlFont::GetTextSize(const char *text, SDL_Rect *r)
//{
//   int maxx = 0;
//   int advance = 0;
//   int w_largest = 0;
//   char lastchar = 0;
//
//   r->x = 0;
//   r->y = 0;
//   r->w = 0;
//   r->h = height;
//
//   while (*text)
//   {
//      if ((MIN_GLYPH <= *text) && (*text <= MAX_GLYPH))
//      {
//         lastchar = *text;
//
//         if (*text == '\n')
//         {
//            r->h += lineSkip;
//            r->w = r->w - advance + maxx;
//            if (r->w > w_largest) w_largest = r->w;
//            r->w = 0;
//         }
//         else
//         {
////            LoadChar(*text);
//
//            maxx = glyphs[((int)*text)].maxx;
//            advance = glyphs[((int)*text)].advance;
//            r->w += advance;
//         }
//      }
//
//      text++;
//   }
//
//   if (lastchar != '\n')
//   {
//      r->w = r->w - advance + maxx;
//      if (r->w > w_largest) w_largest = r->w;
//   }
//   else
//   {
//      r->h -= lineSkip;
//   }
//
//   if (w_largest > r->w)
//   {
//      r->w = w_largest;
//   }
//}

void GlFont::DrawText(const std::string& text, int x, int y) const
{
   glPushAttrib(GL_ALL_ATTRIB_BITS);

   glEnable(GL_BLEND);
   glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

   glEnable(GL_TEXTURE_2D);
   glTexEnvi(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE);

   GLfloat baseleft = x;

   for (const auto& c : text)
   {
      if ('\n' == c)
      {
         x = baseleft;
         y += lineSkip;
      }
      else if ((MIN_GLYPH <= c) && (c <= MAX_GLYPH))
      {
         GLfloat texMinX = glyphs[((int)c)].texMinX;
         GLfloat texMinY = glyphs[((int)c)].texMinY;
         GLfloat texMaxX = glyphs[((int)c)].texMaxX;
         GLfloat texMaxY = glyphs[((int)c)].texMaxY;

         GLfloat minx = glyphs[((int)c)].minx;

         GLfloat left   = x + minx;
         GLfloat right  = x + glyphs[((int)c)].pic->w + minx;
         GLfloat top    = y;
         GLfloat bottom = y + glyphs[((int)c)].pic->h;

         glBindTexture(GL_TEXTURE_2D, glyphs[((int)c)].tex);

         glBegin(GL_TRIANGLE_STRIP);
            glTexCoord2f(texMinX, texMinY); glVertex2f( left,    top);
            glTexCoord2f(texMaxX, texMinY); glVertex2f(right,    top);
            glTexCoord2f(texMinX, texMaxY); glVertex2f( left, bottom);
            glTexCoord2f(texMaxX, texMaxY); glVertex2f(right, bottom);
         glEnd();

         x += glyphs[((int)c)].advance;
      }
   }

   glPopAttrib();
}

void GlFont::LoadChar(const char c)
{
   GLfloat texcoord[4];
   char letter[2] = {0, 0};

   if ((MIN_GLYPH <= c) && (c <= MAX_GLYPH))
   {
      letter[0] = c;
      TTF_GlyphMetrics(ttfFont,
                       (Uint16)c,
                       &glyphs[((int)c)].minx,
                       &glyphs[((int)c)].maxx,
                       &glyphs[((int)c)].miny,
                       &glyphs[((int)c)].maxy,
                       &glyphs[((int)c)].advance);

      SDL_Surface* g0 = TTF_RenderText_Blended(ttfFont, letter, mForeground);
      SDL_Surface* g1 = nullptr;

      if (g0)
      {
         g1 = SDL_DisplayFormatAlpha(g0);
         SDL_FreeSurface(g0);
      }

      if (g1)
      {
         glyphs[((int)c)].pic = g1;
         glyphs[((int)c)].tex = SDL_GL_LoadTexture(g1, texcoord);
         glyphs[((int)c)].texMinX = texcoord[0];
         glyphs[((int)c)].texMinY = texcoord[1];
         glyphs[((int)c)].texMaxX = texcoord[2];
         glyphs[((int)c)].texMaxY = texcoord[3];
      }
   }
}
