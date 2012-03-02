#ifndef USER_DATA_H
#define USER_DATA_H

#include <XnTypes.h>

#include <map>
#include <vector>
#include <string>

class UserData
{
public:
   UserData(XnUserID id);
   virtual ~UserData();

   XnUserID GetId() const;

//   size_t GetPixelIterator(std::vector<bool>::const_iterator& begin,
//                           std::vector<bool>::const_iterator& end) const;
   const XnLabel* GetPixels() const;
   void SetPixels(const XnLabel* pixels);

   std::map<int, XnPoint3D> GetRealWorldJoints() const;
   void SetRealWorldJoints(int joint, const XnPoint3D& pos);

   std::string JointId2JointName(int joint_id) const;

protected:
   XnUserID mId;
   const XnLabel* mPixels;
   std::map<int, XnPoint3D> mRealWorldJoints;

private:
   mutable std::map<int, std::string> mJointNames;
};

#endif // USER_DATA_H
