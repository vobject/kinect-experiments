#include "KinectPlayer.h"
#include "Kinect.h"
#include "UserTracking.h"

#include <allegro5/allegro.h>

KinectPlayer::KinectPlayer(const Kinect& kinect, const UserTracking& tracking)
   : mKinect(kinect)
   , mUserTracking(tracking)
   , mBitmapWidth(mKinect.GetXRes())
   , mBitmapHeight(mKinect.GetYRes())
   , mBitmap(NULL)
{
   mBitmap = al_create_bitmap(mBitmapWidth, mBitmapHeight);
   if (NULL == mBitmap) {
      throw "Failed to create Kinect bitmap";
   }

   SetSize(300, 200);
   SetPos(100, 100);
}

KinectPlayer::~KinectPlayer()
{
   al_destroy_bitmap(mBitmap);
}

bool KinectPlayer::IsAlive()
{
   return true;
}

void KinectPlayer::Update()
{
}

void KinectPlayer::Render()
{
//   if (!mPlayerPresent) {
//      return;
//   }

   std::vector<UserData> users;
   mUserTracking.GetUsers(users);

   if (users.empty()) {
      return;
   }

   al_set_target_bitmap(mBitmap);
   al_clear_to_color(al_map_rgb(0x00, 0x00, 0x00));
   al_convert_mask_to_alpha(mBitmap, al_map_rgb(0x00, 0x00, 0x00));

   xn::SceneMetaData scene_meta;
   mUserTracking.GetUserPixels(users[0], scene_meta);

   const XnRGB24Pixel* pRgbBuf = mKinect.GetImageData();
   const XnLabel* pLabelBuf = scene_meta.Data();

   ALLEGRO_LOCKED_REGION* lock = al_lock_bitmap(mBitmap,
                                                al_get_bitmap_format(mBitmap),
                                                ALLEGRO_LOCK_WRITEONLY);

   al_set_target_bitmap(mBitmap);
   for (int y = 0; y < mBitmapHeight; y++)
   {
      for (int x = 0; x < mBitmapWidth; x++, pLabelBuf++, pRgbBuf++)
      {
         if (*pLabelBuf == users[0].GetId())
         {
            al_put_pixel(x, y, al_map_rgb(pRgbBuf->nRed,
                                          pRgbBuf->nGreen,
                                          pRgbBuf->nBlue));
         }
      }
   }
   al_unlock_bitmap(mBitmap);

   const int screen_x_res = al_get_display_width(al_get_current_display());
   const int screen_y_res = al_get_display_height(al_get_current_display());

   al_set_target_bitmap(al_get_backbuffer(al_get_current_display()));
   al_draw_scaled_bitmap(mBitmap, 0, 0, mBitmapWidth, mBitmapHeight,
      GetXPos(), GetYPos(), GetWidth(), GetHeight(), 0);
}
