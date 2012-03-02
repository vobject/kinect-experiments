#include "BitmapBackground.h"

#include <allegro5/allegro.h>

BitmapBackground::BitmapBackground(const std::string& bitmap)
   : mBitmap(NULL)
{
   mBitmap = al_load_bitmap(bitmap.c_str());
   if (NULL == mBitmap) {
      throw "Failed to load background bitmap";
   }

   SetSize(al_get_bitmap_width(mBitmap), al_get_bitmap_height(mBitmap));
}

BitmapBackground::~BitmapBackground()
{
   al_destroy_bitmap(mBitmap);
}

void BitmapBackground::Update()
{

}

void BitmapBackground::Render()
{
   const int screen_x_res = al_get_display_width(al_get_current_display());
   const int screen_y_res = al_get_display_height(al_get_current_display());

   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   al_draw_scaled_bitmap(mBitmap, 0, 0, GetWidth(), GetHeight(),
                                  0, 0, screen_x_res, screen_y_res, 0);
}
