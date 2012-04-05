#ifndef ACTOR_H
#define ACTOR_H

#include "SceneObject.h"

#include <memory>

class UserData;

class Actor : public SceneObject
{
public:
   Actor();
   virtual ~Actor();

   virtual void Update(int elapsed_time);
   virtual void Update(const UserData& user);

   int GetXCenter();
   int GetYCenter();

private:
   int mXCenter;
   int mYCenter;

   Actor(const Actor&);
   const Actor& operator=(const Actor&);
};

#endif // ACTOR_H
