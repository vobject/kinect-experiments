#include "BloodAnimation.h"

#include <allegro5/allegro.h>

//BloodAnimation::BloodAnimation(int x_pos, int y_pos, float end_time)
//   : SceneObject(x_pos, y_pos, end_time)
//{
//   bloodImage = al_load_bitmap("../../../../external/blood_pack_1/blood_a/blood_a_0001.png");
//   al_convert_mask_to_alpha(bloodImage, al_map_rgb(0, 0, 0));
//}
//
//BloodAnimation::~BloodAnimation()
//{
//   al_destroy_bitmap(bloodImage);
//}
//
//bool BloodAnimation::IsAlive()
//{
//   return (al_current_time() > mEndTime);
////   return false;
//}
//
//void BloodAnimation::Update()
//{
//   if (IsAlive()) {
//      return;
//   }
//}
//
//void BloodAnimation::Render()
//{
//   al_draw_bitmap(bloodImage, mXPos, mYPos, 0);
//}
