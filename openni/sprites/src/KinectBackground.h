#ifndef KINECT_BACKGROUND_H
#define KINECT_BACKGROUND_H

#include "SceneObject.h"

class Kinect;

class KinectBackground : public SceneObject
{
public:
   KinectBackground(Kinect& kinect);
   virtual ~KinectBackground();

   virtual bool IsDone();
   virtual void Update();
   virtual void Render();

private:
   Kinect& mKinect;
};

#endif // KINECT_BACKGROUND_H
