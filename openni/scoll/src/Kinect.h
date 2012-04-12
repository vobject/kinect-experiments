#ifndef KINECT_H
#define KINECT_H

#include "UserData.h"
#include "UserTracking.h"

#include <XnOS.h>
#include <XnCppWrapper.h>

#include <memory>
#include <string>
#include <vector>

class Kinect
{
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

   const XnRGB24Pixel* GetImageData();
   const XnDepthPixel* GetDepthData();

   std::vector<UserData> GetUsers() const;
   std::shared_ptr<xn::SceneMetaData> GetUserPixels(const UserData& user) const;

private:
   void InitOpenNI(const std::string& file);

   // OpenNI members
   xn::Context mContext;
   xn::DepthGenerator mDepthGen;
   xn::ImageGenerator mImageGen;
   xn::DepthMetaData mDepthGenMD;
   xn::ImageMetaData mImageGenMD;
   xn::Player mPlayer;

   UserTracking mUserTracking;
   
   bool mPlaybackMode;

   Kinect(const Kinect&);
   const Kinect& operator=(const Kinect&);
};

#endif // KINECT_H
