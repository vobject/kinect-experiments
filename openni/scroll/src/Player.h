#ifndef PLAYER_H
#define PLAYER_H

#include "SceneObject.hpp"
#include "UserData.hpp"
#include "Texture.h"
#include "Utils.hpp"

#include <XnTypes.h>

#include <SDL.h>

#include <memory>
#include <map>

class Nui;

class Player : public SceneObject
{
public:
   Player(const std::shared_ptr<Nui>& kinect);
   virtual ~Player();

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   virtual bool CheckCollision(const SceneObject& obj) const;

   int GetXCenter();
   int GetYCenter();

   SDL_Surface* GetFrame() const;

private:
   bool IsUserDataValid(const UserData& user) const;

   std::shared_ptr<Nui> mKinect;
   UserData mUserData;
   SDL_Surface* mTexture;
};

#endif // PLAYER_H
