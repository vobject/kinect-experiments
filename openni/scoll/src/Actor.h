#ifndef ACTOR_H
#define ACTOR_H

#include "SceneObject.h"

#include <XnTypes.h>

#include <memory>
#include <map>

class UserData;

class Actor : public SceneObject
{
public:
   Actor();
   virtual ~Actor();

   virtual void Update(int elapsed_time);
   virtual void Update(const UserData& user);

   virtual bool CheckCollision(const std::shared_ptr<SceneObject>& obj) const;

   int GetXCenter();
   int GetYCenter();

private:
   int mXCenter;
   int mYCenter;
   mutable std::map<int, XnPoint3D> mJoints;

   Actor(const Actor&);
   const Actor& operator=(const Actor&);
};

#endif // ACTOR_H
