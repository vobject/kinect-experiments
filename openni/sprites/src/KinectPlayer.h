#ifndef KINECT_PLAYER_H
#define KINECT_PLAYER_H

#include "SceneObject.h"

class Kinect;
class UserTracking;

class ALLEGRO_BITMAP;

class KinectPlayer : public SceneObject
{
public:
   KinectPlayer(const Kinect& kinect, const UserTracking& tracking);
   virtual ~KinectPlayer();

   virtual bool IsAlive();
   virtual void Update();
   virtual void Render();

private:
   const Kinect& mKinect;
   const UserTracking& mUserTracking;
   const int mBitmapWidth;
   const int mBitmapHeight;
   ALLEGRO_BITMAP* mBitmap;
//   bool mPlayerPresent;
};

#endif // KINECT_PLAYER_H
