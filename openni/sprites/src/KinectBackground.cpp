#include "KinectBackground.h"
#include "Kinect.h"

#include <allegro5/allegro.h>

KinectBackground::KinectBackground(Kinect& kinect)
   : SceneObject(0, 0, .0f)
   , mKinect(kinect)
{

}

KinectBackground::~KinectBackground()
{

}

bool KinectBackground::IsDone()
{
   return false;
}

void KinectBackground::Update()
{
   mKinect.NextFrame();
}

void KinectBackground::Render()
{
   al_clear_to_color(al_map_rgb(0,0,0));

   ALLEGRO_BITMAP* backbuf = al_get_backbuffer(al_get_current_display());
   ALLEGRO_LOCKED_REGION* lock = al_lock_bitmap(backbuf,
                                                al_get_bitmap_format(backbuf),
                                                ALLEGRO_LOCK_WRITEONLY);

   const XnRGB24Pixel* pDepthBuf = mKinect.GetImageData();
   for (int y = 0; y < mKinect.GetYRes(); y++)
   {
      for (int x = 0; x < mKinect.GetXRes(); x++, pDepthBuf++)
      {
         al_put_pixel(x, y, al_map_rgb(pDepthBuf->nRed,
                                       pDepthBuf->nGreen,
                                       pDepthBuf->nBlue));
      }
   }
   al_unlock_bitmap(backbuf);

//   al_draw_textf(mFont18, al_map_rgb(255, 255, 255), 5, 5, 0, "FPS: %i", gameFPS);
}
