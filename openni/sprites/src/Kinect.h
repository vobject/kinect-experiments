#ifndef KINECT_H
#define KINECT_H

#include <XnOS.h>
#include <XnCppWrapper.h>

#include <string>
#include <vector>

class Kinect
{
   friend class UserTracking;

public:
   Kinect();
   ~Kinect();

   void Init();
   void InitPlayback(const std::string& file);

   void NextFrame();

   void SeekForward(int frames = 100);
   void SeekBackward(int frames = -100);

   int GetXRes() const;
   int GetYRes() const;

   const XnRGB24Pixel* GetImageData() const;
   const XnDepthPixel* GetDepthData() const;

   XnPoint3D RealWorldToProjective(const XnPoint3D& pos) const;
   XnPoint3D ProjectiveToRealWorld(const XnPoint3D& pos) const;

private:
   void InitOpenNI(const std::string& file);

   // OpenNI members
   xn::Context mContext;
   xn::DepthGenerator mDepthGen;
   xn::ImageGenerator mImageGen;
   mutable xn::DepthMetaData mDepthGenMD;
   mutable xn::ImageMetaData mImageGenMD;
   xn::Player mPlayer;
   
   bool mPlaybackMode;

   Kinect(const Kinect&);
   Kinect& operator=(const Kinect&);
};

#endif // KINECT_H
