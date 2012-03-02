#ifndef BITMAP_BACKGROUND_H
#define BITMAP_BACKGROUND_H

#include "Background.h"

#include <string>

class ALLEGRO_BITMAP;

class BitmapBackground : public Background
{
public:
   BitmapBackground(const std::string& bitmap);
   virtual ~BitmapBackground();

   virtual void Update();
   virtual void Render();

private:
   ALLEGRO_BITMAP* mBitmap;
};

#endif // BITMAP_BACKGROUND_H
