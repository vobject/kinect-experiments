#ifndef SCENE_TEXT_H
#define SCENE_TEXT_H

#include "SceneObject.h"

#include <string>

class ALLEGRO_FONT;

class SceneText : public SceneObject
{
public:
   SceneText(int x_pos, int y_pos, int size);
   virtual ~SceneText();

   virtual bool IsAlive();
   virtual void Update();
   virtual void Render();

   void SetText(const std::string& text);

private:
   const int mFontSize;
   ALLEGRO_FONT* mFont;
   std::string mText;
};

#endif // SCENE_OBJECT_H
