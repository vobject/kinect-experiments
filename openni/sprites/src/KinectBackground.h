#ifndef KINECT_BACKGROUND_H
#define KINECT_BACKGROUND_H

#include "Background.h"

class Kinect;
class ALLEGRO_BITMAP;

class KinectBackground : public Background
{
public:
   KinectBackground(Kinect& kinect);
   virtual ~KinectBackground();

   virtual void Update();
   virtual void Render();

private:
   Kinect& mKinect;
   ALLEGRO_BITMAP* mBitmap;
};

#endif // KINECT_BACKGROUND_H
