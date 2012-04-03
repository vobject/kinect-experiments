#ifndef USER_DATA_H
#define USER_DATA_H

#include <XnTypes.h>

#include <map>
#include <string>

class UserData
{
public:
   UserData(XnUserID id);
   virtual ~UserData();

   XnUserID GetId() const;

   std::map<int, XnPoint3D> GetRealWorldJoints() const;
   void SetRealWorldJoints(int joint, const XnPoint3D& pos);

   std::string JointId2JointName(int joint_id) const;

protected:
   XnUserID mId;
   std::map<int, XnPoint3D> mRealWorldJoints;

private:
   // FIXME: Make this static
   mutable std::map<int, std::string> mJointNames;
};

#endif // USER_DATA_H
