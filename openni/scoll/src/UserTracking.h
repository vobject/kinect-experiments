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
   UserTrackerCallbackArgs() : user_gen(NULL) { }

   xn::UserGenerator* user_gen;

private:
   UserTrackerCallbackArgs(const UserTrackerCallbackArgs&);
   UserTrackerCallbackArgs& operator=(const UserTrackerCallbackArgs&);
};

class UserTracking
{
public:
   UserTracking();
   ~UserTracking();

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

   // Stuff we do not need atm.
   UserTracking(const UserTracking&);
   const UserTracking& operator=(const UserTracking&);
};

#endif // USER_TRACKING_H
