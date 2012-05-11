#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.h"
#include "UserData.h"
#include "Texture.h"
#include "Utils.hpp"

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

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   virtual bool CheckCollision(const SceneObject& obj) const;

   int GetXCenter();
   int GetYCenter();

   std::shared_ptr<Texture> GetFrame() const;

private:
   bool IsUserDataValid(const UserData& user) const;

   std::shared_ptr<Kinect> mKinect;
   UserData mUserData;
   std::shared_ptr<Texture> mTexture;
};

#endif // PLAYER_H
