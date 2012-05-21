#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SceneObject.hpp"
#include "UserData.hpp"
#include "Texture.h"
#include "Utils.hpp"

#include <SDL.h>

#include <memory>
#include <map>

namespace kinex {
   class Nui;
}

class Player : public SceneObject
{
public:
   Player(const std::shared_ptr<kinex::Nui>& kinect);
   virtual ~Player();

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   virtual bool CheckCollision(const SceneObject& obj, Point& collision) const;

   int GetXCenter();
   int GetYCenter();

   SDL_Surface* GetFrame() const;

private:
   bool IsUserDataValid(const kinex::UserData& user) const;
   Point GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const;

   std::shared_ptr<kinex::Nui> mKinect;
   kinex::UserData mUserData;
   SDL_Surface* mTexture;
};

#endif // PLAYER_HPP
