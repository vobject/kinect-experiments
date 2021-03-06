#include "UserTracking.h"
#include "Log.h"

// Callback functions for xn::UserGenerator class.
void XN_CALLBACK_TYPE UserFoundCB(xn::UserGenerator& gen, XnUserID id, void* cookie);
void XN_CALLBACK_TYPE UserLostCB(xn::UserGenerator& gen, XnUserID id, void* cookie);

// Callback functions for xn::PoseDetectionCapability class.
void XN_CALLBACK_TYPE PoseStartCB(xn::PoseDetectionCapability& gen,
                                  const XnChar* pose, XnUserID id, void* cookie);
void XN_CALLBACK_TYPE PoseEndCB(xn::PoseDetectionCapability& gen,
                                const XnChar* pose, XnUserID id, void* cookie);

// Callback functions for xn::SkeletonCapability class.
void XN_CALLBACK_TYPE CalibStartCB(xn::SkeletonCapability& gen,
                                   XnUserID id, void* cookie);
void XN_CALLBACK_TYPE CalibEndCB(xn::SkeletonCapability& gen, XnUserID id,
                                 XnCalibrationStatus calibrationError, void* cookie);

UserTracking::UserTracking()
{

}

UserTracking::~UserTracking()
{

}

void UserTracking::Init( xn::Context& ctx )
{
   if (XN_STATUS_OK != mUserGen.Create(ctx)) {
      throw "xn::UserGenerator could not be inizialized. Does the context support it?";
   }

   mCallbackArgs.user_gen = &mUserGen;

   // Callback methods for the xn::UserGenerator class.
   mUserGen.RegisterUserCallbacks(UserFoundCB, UserLostCB, &mCallbackArgs, mUserGenCB);

   xn::PoseDetectionCapability pose_cap = mUserGen.GetPoseDetectionCap();
   pose_cap.RegisterToPoseDetected(PoseStartCB, &mCallbackArgs, mPoseStartCB);
   pose_cap.RegisterToOutOfPose(PoseEndCB, &mCallbackArgs, mPoseEndCB);

   xn::SkeletonCapability skel_cap = mUserGen.GetSkeletonCap();
   skel_cap.RegisterToCalibrationStart(CalibStartCB, &mCallbackArgs, mCalibStartCB);
   skel_cap.RegisterToCalibrationComplete(CalibEndCB, &mCallbackArgs, mCalibEndCB);
   skel_cap.SetSkeletonProfile(XN_SKEL_PROFILE_ALL);
}

size_t UserTracking::GetUsers(std::vector<UserData>& users) const
{
   XnUserID userBuf[16];
   XnUInt16 userMax = 16;

   if (userMax < mUserGen.GetNumberOfUsers()) {
      LOG(logWARNING) << mUserGen.GetNumberOfUsers() << " users detected"
                      << " but we only support " << userMax;
   }

   mUserGen.GetUsers(userBuf, userMax);
   for (XnUInt16 id = 0; userMax >= id; ++id)
   {
      if (!mUserGen.GetSkeletonCap().IsTracking(userBuf[id])) {
         // We are only interested in the users that are being tracked.
         continue;
      }

      UserData user(userBuf[id]);

      // User pixels
      xn::SceneMetaData scene_meta;
      mUserGen.GetUserPixels(userBuf[id], scene_meta);

      const XnLabel* pLabelBuf = scene_meta.Data();
      const size_t pixel_count = scene_meta.YRes() * scene_meta.XRes();
      std::vector<bool> user_pixels(pixel_count, false);

      for (XnUInt i = 0; i < pixel_count; ++i, ++pLabelBuf)
      {
         if (*pLabelBuf == userBuf[id])
         {
            user_pixels[i] = true;
         }
      }
      user.SetPixels(user_pixels);

      // Show skeleton points.
      XnSkeletonJointPosition pos;
      for (int joint = XN_SKEL_HEAD; joint <= XN_SKEL_RIGHT_FOOT; ++joint)
      {
         mUserGen.GetSkeletonCap().GetSkeletonJointPosition(userBuf[id], (XnSkeletonJoint)joint, pos);
         if (0.5 > pos.fConfidence) {
            continue;
         }
         user.SetRealWorldJoints(joint, pos.position);
      }

      users.push_back(user);
   }
   return users.size();
}

void XN_CALLBACK_TYPE UserFoundCB(
   xn::UserGenerator& gen,
   XnUserID id,
   void* /*cookie*/
)
{
   LOG(logDEBUG) << "UserFoundCB()";

   gen.GetPoseDetectionCap().StartPoseDetection("Psi", id);
}

void XN_CALLBACK_TYPE UserLostCB(
   xn::UserGenerator& /*gen*/,
   XnUserID /*id*/,
   void* /*cookie*/
)
{
   LOG(logDEBUG) << "UserLostCB()";
}

void XN_CALLBACK_TYPE PoseStartCB(
   xn::PoseDetectionCapability& /*cap*/,
   const XnChar* /*pose*/,
   XnUserID id,
   void* cookie
)
{
   LOG(logDEBUG) << "PoseStartCB()";

   UserTrackerCallbackArgs* args = static_cast<UserTrackerCallbackArgs*>(cookie);
   args->user_gen->GetPoseDetectionCap().StopPoseDetection(id);
   args->user_gen->GetSkeletonCap().RequestCalibration(id, TRUE);
}

void XN_CALLBACK_TYPE PoseEndCB(
   xn::PoseDetectionCapability& /*cap*/,
   const XnChar* /*pose*/,
   XnUserID /*id*/,
   void* /*cookie*/
)
{
   LOG(logDEBUG) << "PoseEndCB()";
}

void XN_CALLBACK_TYPE CalibStartCB(
   xn::SkeletonCapability& /*cap*/,
   XnUserID /*id*/,
   void* /*cookie*/
)
{
   LOG(logDEBUG) << "CalibStartCB()";
}

void XN_CALLBACK_TYPE CalibEndCB(
   xn::SkeletonCapability& /*cap*/,
   XnUserID id,
   XnCalibrationStatus calibrationError,
   void* cookie
)
{
   UserTrackerCallbackArgs* args = static_cast<UserTrackerCallbackArgs*>(cookie);

   if (XN_CALIBRATION_STATUS_OK == calibrationError)
   {
      LOG(logDEBUG) << "User successfully calibrated.";
      args->user_gen->GetSkeletonCap().StartTracking(id);
   }
   else
   {
      LOG(logDEBUG) << "Failed to calibrate user!";
      args->user_gen->GetPoseDetectionCap().StartPoseDetection("Psi", id);
   }
}
