#ifndef ACTOR_H
#define ACTOR_H

#include "SceneObject.h"
#include "UserData.h"

#include <XnTypes.h>

#include <SDL.h>

#include <memory>
#include <map>

class Kinect;

class Player : public SceneObject
{
public:
   Player(const std::shared_ptr<Kinect>& kinect);
   virtual ~Player();

   virtual void Update(int elapsed_time);

   virtual bool CheckCollision(const SceneObject& obj) const;

   int GetXCenter();
   int GetYCenter();

   SDL_Surface* GetFrame() const;

private:
   bool IsUserDataValid(const UserData& user) const;

   std::shared_ptr<Kinect> mKinect;
   UserData mUserData;
   SDL_Surface* mFrame;

   Player(const Player&);
   const Player& operator=(const Player&);
};

#endif // ACTOR_H
