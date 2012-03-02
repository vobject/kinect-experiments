#include "SceneText.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <allegro5/allegro_ttf.h>

SceneText::SceneText(int x_pos, int y_pos, int size)
   : SceneObject(x_pos, y_pos)
   , mFontSize(size)
   , mFont(NULL)
{
   al_init_font_addon();
   al_init_ttf_addon();

   mFont = al_load_font("VeraMono.ttf", mFontSize, 0);
   if (NULL == mFont) {
      throw "Failed to load VeraMono.ttf font";
   }
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
   al_draw_text(mFont, al_map_rgb(0xff, 0xff, 0xff), mXPos, mYPos, 0, mText.c_str());
}

void SceneText::SetText(const std::string& text)
{
   mText = text;
}
