#ifndef KINECT_BACKGROUND_H
#define KINECT_BACKGROUND_H

#include "Background.h"

class Kinect;

class KinectBackground : public Background
{
public:
   KinectBackground(Kinect& kinect);
   virtual ~KinectBackground();

   virtual void Update();
   virtual void Render();

private:
   Kinect& mKinect;
};

#endif // KINECT_BACKGROUND_H
