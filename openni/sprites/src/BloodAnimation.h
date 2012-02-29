#ifndef BLOOD_ANIMATION_H
#define BLOOD_ANIMATION_H

#include "SceneObject.h"

class ALLEGRO_BITMAP;

class BloodAnimation : public SceneObject
{
public:
   BloodAnimation(int x_pos, int y_pos, float end_time);
   virtual ~BloodAnimation();

   virtual bool IsDone();
   virtual void Update();
   virtual void Render();

private:
   ALLEGRO_BITMAP *bloodImage;
};

#endif // BLOOD_ANIMATION_H
