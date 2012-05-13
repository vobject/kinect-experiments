#ifndef KINECT_HPP
#define KINECT_HPP

#include "Nui.hpp"
#include "UserTracking.hpp"

#include <string>

class Kinect : public Nui
{
public:
   Kinect();
   virtual ~Kinect();

   Kinect(const Kinect&) = delete;
   Kinect& operator=(const Kinect&) = delete;

   void Init() override;
   void InitPlayback(const std::string& file);
   void NextFrame() override;

   const XnRGB24Pixel* GetImageData() override;
   const XnDepthPixel* GetDepthData() override;

   void SeekForward(int frames = 100);
   void SeekBackward(int frames = -100);

   std::vector<UserData> GetUsers() const override;
   std::shared_ptr<xn::SceneMetaData> GetUserPixels(const UserData& user) const override;

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
   
   bool mPlaybackMode = false;
};

#endif // KINECT_HPP
