#include "Kinect.h"

#include <cassert>

Kinect::Kinect()
   : mPlaybackMode(false)
{

}

Kinect::~Kinect()
{

}

void Kinect::Init()
{
   InitOpenNI("");
   mUserTracking.Init(mContext);
   mContext.StartGeneratingAll();
}

void Kinect::InitPlayback(const std::string& file)
{
   // Check if the given filepath is accessible.
   if ((-1 == access(file.c_str(), 0))) {
      throw "The given file does not exist.";
   }
   mPlaybackMode = true;

   InitOpenNI(file);
   mUserTracking.Init(mContext);
   mContext.StartGeneratingAll();
}

void Kinect::InitOpenNI(const std::string& file)
{
   // TODO: Better (real!) error handling for OpenNI API failures.

   auto rc = mContext.Init();
   assert(XN_STATUS_OK == rc);

   if (!file.empty())
   {
      rc = mContext.OpenFileRecording(file.c_str(), mPlayer);
      assert(XN_STATUS_OK == rc);

      // Try to find data for image and depths generator in the recording.
      rc = mContext.FindExistingNode(XN_NODE_TYPE_DEPTH, mDepthGen);
      assert(XN_STATUS_OK == rc);
      rc = mContext.FindExistingNode(XN_NODE_TYPE_IMAGE, mImageGen);
      assert(XN_STATUS_OK == rc);
   }
   else
   {
      rc = mContext.SetGlobalMirror(true);
      assert(XN_STATUS_OK == rc);

      rc = mDepthGen.Create(mContext);
      assert(XN_STATUS_OK == rc);
      rc = mImageGen.Create(mContext);
      assert(XN_STATUS_OK == rc);
   }

   mDepthGen.GetMetaData(mDepthGenMD);
   mImageGen.GetMetaData(mImageGenMD);

   // Image and Depth must have the same resolution for this tool.
   if (mDepthGenMD.FullXRes() != mImageGenMD.FullXRes() ||
       mDepthGenMD.FullYRes() != mImageGenMD.FullYRes()){
         throw "Image and Depth do not have the same resolution.";
   }

   // The pixel format of the image recording and SDL_Surface must be the same.
   // FYI: depthmap usually returns XN_PIXEL_FORMAT_GRAYSCALE_16_BIT.
   if (XN_PIXEL_FORMAT_RGB24 != mImageGenMD.PixelFormat()) {
      throw "Currently 24bit RGB is the only supported format.";
   }
}

void Kinect::NextFrame()
{
   // Read a new frame from the recording.
   const auto rc = mContext.WaitNoneUpdateAll();
   if (XN_STATUS_OK != rc) {
      throw "xn::Context::WaitNoneUpdateAll() failed";
   }
}

void Kinect::SeekForward(const int frames /*= 100*/)
{
   if (mPlaybackMode)
   {
      mPlayer.SeekToFrame(mImageGen.GetName(), frames, XN_PLAYER_SEEK_CUR);
   }
}

void Kinect::SeekBackward(const int frames /*= -100*/)
{
   if (mPlaybackMode)
   {
      mPlayer.SeekToFrame(mImageGen.GetName(), frames, XN_PLAYER_SEEK_CUR);
   }
}

int Kinect::GetXRes() const
{
   return mDepthGenMD.FullXRes();
}

int Kinect::GetYRes() const
{
   return mDepthGenMD.FullYRes();
}

const XnRGB24Pixel* Kinect::GetImageData()
{
   // TODO: Find out why it is necessary to update the metadata
   //  object for each run. The playback still works if we comment this line
   //  out but it is somewhat "laggy". Isn't img_meta just a reference into
   //  img's metadata internals? Or is here some real calculation going on?
   mImageGen.GetMetaData(mImageGenMD);
   
   // Return a pointer to the image data from the generator.
   return mImageGenMD.RGB24Data();
}

const XnDepthPixel* Kinect::GetDepthData()
{
   mDepthGen.GetMetaData(mDepthGenMD);

   // Return a pointer to the depth data from the generator.
   return mDepthGenMD.Data();
}

std::vector<UserData> Kinect::GetUsers() const
{
   return mUserTracking.GetUsers(mDepthGen);
}

std::shared_ptr<xn::SceneMetaData> Kinect::GetUserPixels(const UserData& user) const
{
   return mUserTracking.GetUserPixels(user);
}
