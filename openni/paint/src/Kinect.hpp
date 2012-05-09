#ifndef KINECT_HPP
#define KINECT_HPP

#include "UserData.hpp"
#include "UserTracking.hpp"
#include "Utils.hpp"

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

   Kinect(const Kinect&) = delete;
   Kinect& operator=(const Kinect&) = delete;

   void Init();
   void InitPlayback(const std::string& file);
   Size GetSize() const;

   void NextFrame();

   const XnRGB24Pixel* GetImageData();
   const XnDepthPixel* GetDepthData();

   void SeekForward(int frames = 100);
   void SeekBackward(int frames = -100);

   std::vector<UserData> GetUsers() const;
   std::shared_ptr<xn::SceneMetaData> GetUserPixels(const UserData& user) const;

   // TODO:
   //  OnGesture(GESTURE, callback);

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
   Size mRes;
};

#endif // KINECT_HPP
