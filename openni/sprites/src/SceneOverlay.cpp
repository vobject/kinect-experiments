#include "SceneOverlay.h"

#include <allegro5/allegro.h>
#include <allegro5/allegro_image.h>

//SceneOverlay::SceneOverlay(
//   const std::string& bitmap,
//   ScrollType scroll_type,
//   int speed
//)
//   : mBitmap(NULL)
//   , mBitmapHeight(0)
//   , mBitmapWidth(0)
//   , mScrollType(None)
//   , mSpeed(speed)
//{
//   mBitmap = al_load_bitmap(bitmap.c_str());
//   if (NULL == mBitmap) {
//      throw "Failed to load overlay bitmap";
//   }
//
//   mBitmapHeight = al_get_bitmap_height(mBitmap);
//   mBitmapWidth = al_get_bitmap_width(mBitmap);
//}
//
//SceneOverlay::~SceneOverlay()
//{
//   al_destroy_bitmap(mBitmap);
//}
//
//bool SceneOverlay::IsAlive()
//{
//   return true;
//}
//
//void SceneOverlay::Update()
//{
//   mXPos -= mSpeed;
//
//   if((mXPos + mBitmapWidth) <= 0)
//   {
//      mXPos = 0;
//   }
//}
//
//void SceneOverlay::Render()
//{
//   al_draw_bitmap(mBitmap, mXPos, mYPos, 0);
//
////   if((mXPos + mBitmapWidth) < al_get_display_width(NULL))
////   {
//      al_draw_bitmap(mBitmap, mXPos + mBitmapWidth, mYPos, 0);
////   }
//
////   ALLEGRO_BITMAP* backbuf = al_get_backbuffer(al_get_current_display());
////   ALLEGRO_LOCKED_REGION* lock = al_lock_bitmap(backbuf,
////                                                al_get_bitmap_format(backbuf),
////                                                ALLEGRO_LOCK_WRITEONLY);
////
////   const XnRGB24Pixel* pDepthBuf = mKinect.GetImageData();
////   for (int y = 0; y < mKinect.GetYRes(); y++)
////   {
////      for (int x = 0; x < mKinect.GetXRes(); x++, pDepthBuf++)
////      {
////         al_put_pixel(x, y, al_map_rgb(pDepthBuf->nRed,
////                                       pDepthBuf->nGreen,
////                                       pDepthBuf->nBlue));
////      }
////   }
////   al_unlock_bitmap(backbuf);
//}
//
//int SceneOverlay::GetSpeed() const
//{
//   return mSpeed;
//}
//
//void SceneOverlay::SetSpeed(const int speed)
//{
//   mSpeed = speed;
//}
