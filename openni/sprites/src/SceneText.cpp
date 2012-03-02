#include "SceneText.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>

SceneText::SceneText(int x_pos, int y_pos, int size)
   : mFontSize(size)
   , mFont(NULL)
{
   mFont = al_load_font("VeraMono.ttf", mFontSize, 0);
   if (NULL == mFont) {
      throw "Failed to load VeraMono.ttf font";
   }

   SetPos(x_pos, y_pos);
}

SceneText::~SceneText()
{
   al_destroy_font(mFont);
}

bool SceneText::IsAlive()
{
   return true;
}

void SceneText::Update()
{

}

void SceneText::Render()
{
   al_draw_text(mFont, al_map_rgb(0xff, 0xff, 0xff), GetXPos(), GetYPos(), 0,
                mText.c_str());
}

void SceneText::SetText(const std::string& text)
{
   mText = text;
}
