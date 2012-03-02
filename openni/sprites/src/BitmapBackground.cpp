#include "BitmapBackground.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

BitmapBackground::BitmapBackground(const std::string& bitmap)
   : mBitmap(NULL)
{
   al_init_image_addon();

   mBitmap = al_load_bitmap(bitmap.c_str());
   if (NULL == mBitmap) {
      throw "Failed to load background bitmap";
   }
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
   al_draw_bitmap(mBitmap, mXPos, mYPos, 0);
}
