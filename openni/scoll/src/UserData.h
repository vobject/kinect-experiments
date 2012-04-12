#ifndef USER_DATA_H
#define USER_DATA_H

#include <XnTypes.h>

#include <map>
#include <string>

class UserData
{
public:
   static std::string NameFromId(int joint_id);
   static const int INVALID_USER_ID = -1;

   UserData(XnUserID id);
   UserData(const UserData& rhs);
   UserData& operator=(const UserData& rhs);
   ~UserData();

//   const XnPoint3D& operator[](int joint_id) const;

   XnUserID GetId() const;

   std::map<int, XnPoint3D> GetRealWorldJoints() const;
   void SetRealWorldJoint(int joint, const XnPoint3D& pos);

   std::map<int, XnPoint3D> GetPerspectiveJoints() const;
   void SetPerspectiveJoint(int joint, const XnPoint3D& pos);

private:
   static const std::map<int, std::string> mJointNames;

   XnUserID mId;
   std::map<int, XnPoint3D> mRealWorldJoints;
   std::map<int, XnPoint3D> mPerspectiveJoints;

};

#endif // USER_DATA_H
