#include "KinectBackground.h"
#include "Kinect.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

KinectBackground::KinectBackground(Kinect& kinect)
   : mKinect(kinect)
   , mBitmap(NULL)
{
   al_init_image_addon();

   mBitmap = al_create_bitmap(mKinect.GetXRes(), mKinect.GetYRes());
   if (NULL == mBitmap) {
      throw "Failed to create Kinect bitmap";
   }
}

KinectBackground::~KinectBackground()
{
   al_destroy_bitmap(mBitmap);
}

void KinectBackground::Update()
{
   mKinect.NextFrame();
}

void KinectBackground::Render()
{
   ALLEGRO_LOCKED_REGION* lock = al_lock_bitmap(mBitmap,
                                                al_get_bitmap_format(mBitmap),
                                                ALLEGRO_LOCK_WRITEONLY);
   al_set_target_bitmap(mBitmap);

   const int kinect_x_res = mKinect.GetXRes();
   const int kinect_y_res = mKinect.GetYRes();
   const XnRGB24Pixel* pDepthBuf = mKinect.GetImageData();

   for (int y = 0; y < kinect_y_res; y++)
   {
      for (int x = 0; x < kinect_x_res; x++, pDepthBuf++)
      {
         al_put_pixel(x, y, al_map_rgb(pDepthBuf->nRed,
                                       pDepthBuf->nGreen,
                                       pDepthBuf->nBlue));
      }
   }
   al_unlock_bitmap(mBitmap);

   const int screen_x_res = al_get_display_width(al_get_current_display());
   const int screen_y_res = al_get_display_height(al_get_current_display());

   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   al_draw_scaled_bitmap(mBitmap, 0, 0, kinect_x_res, kinect_y_res,
                                  0, 0, screen_x_res, screen_y_res, 0);
}
