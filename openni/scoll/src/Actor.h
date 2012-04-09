#ifndef ACTOR_H
#define ACTOR_H

#include "SceneObject.h"

#include <XnTypes.h>

#include <SDL.h>

#include <memory>
#include <map>

class Kinect;
class UserData;

class Actor : public SceneObject
{
public:
   Actor(const std::shared_ptr<Kinect>& kinect);
   virtual ~Actor();

   virtual void Update(int elapsed_time);
   virtual void Update(const UserData& user);

   virtual bool CheckCollision(const std::shared_ptr<SceneObject>& obj) const;

   int GetXCenter();
   int GetYCenter();

   SDL_Surface* GetFrame() const;

private:
   int mXCenter;
   int mYCenter;
   SDL_Surface* mFrame;
   mutable std::map<int, XnPoint3D> mJoints;

   Actor(const Actor&);
   const Actor& operator=(const Actor&);
};

#endif // ACTOR_H
