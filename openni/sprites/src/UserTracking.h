#ifndef USER_TRACKING_H
#define USER_TRACKING_H

#include "UserData.h"

#include <XnOS.h>
#include <XnCppWrapper.h>

#include <vector>

class Kinect;
class ALLEGRO_BITMAP;

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

   void Init(Kinect& kinect);
   size_t GetUsers(std::vector<UserData>& users) const;
   void GetUserPixels(const UserData& user, xn::SceneMetaData& meta) const;

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
   UserTracking& operator=(const UserTracking&);
};

#endif // USER_TRACKING_H
