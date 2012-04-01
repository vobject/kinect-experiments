#include "KinectBackground.h"
#include "Kinect.h"

#include <allegro5/allegro.h>

KinectBackground::KinectBackground(Kinect& kinect)
   : mKinect(kinect)
   , mBitmap(NULL)
{
   mBitmap = al_create_bitmap(mKinect.GetXRes(), mKinect.GetYRes());
   if (NULL == mBitmap) {
      throw "Failed to create Kinect bitmap";
   }

   SetSize(al_get_bitmap_width(mBitmap), al_get_bitmap_height(mBitmap));
}

KinectBackground::~KinectBackground()
{
   al_destroy_bitmap(mBitmap);
}

void KinectBackground::Update()
{

}

void KinectBackground::Render()
{
   ALLEGRO_LOCKED_REGION* lock = al_lock_bitmap(mBitmap,
                                                al_get_bitmap_format(mBitmap),
                                                ALLEGRO_LOCK_WRITEONLY);
   al_set_target_bitmap(mBitmap);
   const XnRGB24Pixel* pRgbBuf = mKinect.GetImageData();

   for (int y = 0; y < GetHeight(); y++)
   {
      for (int x = 0; x < GetWidth(); x++, pRgbBuf++)
      {
         al_put_pixel(x, y, al_map_rgb(pRgbBuf->nRed,
                                       pRgbBuf->nGreen,
                                       pRgbBuf->nBlue));
      }
   }
   al_unlock_bitmap(mBitmap);

   const int screen_x_res = al_get_display_width(al_get_current_display());
   const int screen_y_res = al_get_display_height(al_get_current_display());

   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   al_draw_scaled_bitmap(mBitmap, 0, 0, GetWidth(), GetHeight(),
                                  0, 0, screen_x_res, screen_y_res, 0);
}
