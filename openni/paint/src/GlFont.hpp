// This code was copied from:
//  http://www.gamedev.net/topic/284259-for-reference-using-sdl_ttf-with-opengl/page__view__findpost__p__3649811
// Changes were made where necessary.

#ifndef GL_FONT_HPP
#define GL_FONT_HPP

/** BTW, it is covered by the LGPL  ** Bob Pendleton **/
/** http://www.devolutio...ber/066119.html **/

/**

  +--------------------------------------+
  + Bob Pendleton: writer and programmer +
  + email: Bob@xxxxxxxxxxxxx             +
  + blog:  www.Stonewolf.net             +
  + web:   www.GameProgrammer.com        +
  +--------------------------------------+

   http://www.oreillynet.com/pub/au/1205

   Edits by Kaolin Fire ( kfire@xxxxxxxx; web: erif.org )
      now takes into account glyph minx so glyphs can overlap as intended
      now takes into account newline character

**/

#include <string>

#include <SDL.h>
#include <SDL_ttf.h>

#include <GL/gl.h>

class GlFont
{
public:
   GlFont(const std::string& name, int size, SDL_Color color);
   ~GlFont();

   void DrawText(const std::string& text, int x, int y) const;

private:
   void Init();
   void LoadChar(char c);

   static const int MIN_GLYPH = 32; // SPACE
   static const int MAX_GLYPH = 126; // ~

   static int initCounter;

   const std::string mName;
   const int mPointSize;
   const SDL_Color mForeground;

   typedef struct
   {
      int minx;
      int maxx;
      int miny;
      int maxy;
      int advance;
      SDL_Surface* pic;
      GLuint tex;
      GLfloat texMinX;
      GLfloat texMinY;
      GLfloat texMaxX;
      GLfloat texMaxY;
   } glyph;

   int height;
   int ascent;
   int descent;
   int lineSkip;
   glyph glyphs[MAX_GLYPH + 1];

   TTF_Font *ttfFont;
};

#endif // GL_FONT_HPP
