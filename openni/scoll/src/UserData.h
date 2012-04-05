#ifndef USER_DATA_H
#define USER_DATA_H

#include <XnTypes.h>

#include <map>
#include <string>

class UserData
{
public:
   UserData(XnUserID id);
   ~UserData();

   const XnPoint3D& operator[](int joint_id) const;

   XnUserID GetId() const;

   std::map<int, XnPoint3D> GetRealWorldJoints() const;
   void SetRealWorldJoint(int joint, const XnPoint3D& pos);

   std::string JointId2JointName(int joint_id) const;

private:
   XnUserID mId;

   // FIXME: Is there a way to implement read-operator[] without having to make this mutable?
   mutable std::map<int, XnPoint3D> mRealWorldJoints;

   // FIXME: Make this static
   mutable std::map<int, std::string> mJointNames;
};

#endif // USER_DATA_H
