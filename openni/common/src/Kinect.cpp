#include "Kinect.hpp"

Kinect::Kinect()
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
   auto rc = mContext.Init();
   if (XN_STATUS_OK != rc) {
      throw "OpenNI context could not be initialized.\n \
              Check if your Kinect is attached and \
              unload gspca_kinect kernel driver.";
   }

   if (!file.empty())
   {
      rc = mContext.OpenFileRecording(file.c_str(), mPlayer);
      if (XN_STATUS_OK != rc) {
         throw "Failed to load the pre-recorded file.";
      }

      // Try to find data for image and depths generator in the recording.
      rc = mContext.FindExistingNode(XN_NODE_TYPE_DEPTH, mDepthGen);
      if (XN_STATUS_OK != rc) {
         throw "Could not find the OpenNI depth node.";
      }

      rc = mContext.FindExistingNode(XN_NODE_TYPE_IMAGE, mImageGen);
      if (XN_STATUS_OK != rc) {
         throw "Could not find the OpenNI image node.";
      }
   }
   else
   {
      rc = mContext.SetGlobalMirror(true);
      if (XN_STATUS_OK != rc) {
         throw "Failed to set global mirror mode.";
      }

      rc = mDepthGen.Create(mContext);
      if (XN_STATUS_OK != rc) {
         throw "Failed to set create the OpenNI depth generator.";
      }

      rc = mImageGen.Create(mContext);
      if (XN_STATUS_OK != rc) {
         throw "Failed to set create the OpenNI image generator.";
      }
   }

   mDepthGen.GetMetaData(mDepthGenMD);
   mImageGen.GetMetaData(mImageGenMD);

   // Image and Depth must have the same resolution for this tool.
   if (mDepthGenMD.FullXRes() != mImageGenMD.FullXRes() ||
       mDepthGenMD.FullYRes() != mImageGenMD.FullYRes()){
         throw "Image and Depth do not have the same resolution.";
   }

   mRes.Width = mDepthGenMD.FullXRes();
   mRes.Height = mDepthGenMD.FullYRes();

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

std::vector<UserData> Kinect::GetUsers() const
{
   return mUserTracking.GetUsers(mDepthGen);
}

std::shared_ptr<xn::SceneMetaData> Kinect::GetUserPixels(const UserData& user) const
{
   return mUserTracking.GetUserPixels(user);
}
