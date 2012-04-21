#ifndef USER_TRACKING_H
#define USER_TRACKING_H

#include "UserData.h"

#include <XnOS.h>
#include <XnCppWrapper.h>

#include <memory>
#include <vector>

class Kinect;

// A pointer to this struct is passed as the "cookie" argument to the CB functions.
struct UserTrackerCallbackArgs
{
   constexpr UserTrackerCallbackArgs() : user_gen(nullptr) { }

   UserTrackerCallbackArgs(const UserTrackerCallbackArgs&) = delete;
   UserTrackerCallbackArgs& operator=(const UserTrackerCallbackArgs&) = delete;

   xn::UserGenerator* user_gen;
};

class UserTracking
{
public:
   UserTracking();
   ~UserTracking();

   UserTracking(const UserTracking&) = delete;
   UserTracking& operator=(const UserTracking&) = delete;

   void Init(xn::Context& ctx);
   std::vector<UserData> GetUsers(const xn::DepthGenerator& gen) const;
//   void GetUserPixels(const UserData& user, xn::SceneMetaData& meta) const;
   std::shared_ptr<xn::SceneMetaData> GetUserPixels(const UserData& user) const;

private:
   xn::UserGenerator mUserGen;

   XnCallbackHandle mUserGenCB;
   XnCallbackHandle mPoseStartCB;
   XnCallbackHandle mPoseEndCB;
   XnCallbackHandle mCalibStartCB;
   XnCallbackHandle mCalibEndCB;

   UserTrackerCallbackArgs mCallbackArgs;
};

#endif // USER_TRACKING_H
