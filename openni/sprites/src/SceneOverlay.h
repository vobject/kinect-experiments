#ifndef SCENE_OVERLAY_H
#define SCENE_OVERLAY_H

#include "SceneObject.h"

#include <string>

class ALLEGRO_BITMAP;

class SceneOverlay : public SceneObject
{
public:
   enum ScrollType
   {
      None,
      LeftToRight,
      RightToLeft,
      TopToBottom,
      BottomToTop
   };

   SceneOverlay(const std::string& bitmap, ScrollType scroll_type, int speed);
   virtual ~SceneOverlay();

   virtual bool IsAlive();
   virtual void Update();
   virtual void Render();

   int GetSpeed() const;
   void SetSpeed(int speed);

private:
   ALLEGRO_BITMAP* mBitmap;
   int mBitmapHeight;
   int mBitmapWidth;
   ScrollType mScrollType;
   int mSpeed;
};

#endif // SCENE_OVERLAY_H
