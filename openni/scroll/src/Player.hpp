#ifndef PLAYER_HPP
#define PLAYER_HPP

#include "SceneObject.hpp"
#include "UserData.hpp"
#include "Texture.h"
#include "Utils.hpp"

#include <SDL.h>

#include <memory>
#include <list>

namespace kinex {
   class Nui;
}

enum class PlayerOrientation
{
   Left,
   Right
};

class Player : public SceneObject
{
public:
   Player(const std::shared_ptr<kinex::Nui>& kinect);
   virtual ~Player();

   Player(const Player&) = delete;
   Player& operator=(const Player&) = delete;

   void Update(int elapsed_time) override;

   PlayerOrientation GetOrientation() const;
   virtual bool CheckAttackCollision(const std::shared_ptr<SceneObject>& obj, Point& collision);
   virtual bool CheckGenericCollision(const std::shared_ptr<SceneObject>& obj, Point& collision);

//   int GetXCenter();
//   int GetYCenter();

   SDL_Surface* GetFrame() const;

private:
   bool IsUserDataValid(const kinex::UserData& user) const;
   Point GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const;

   bool CheckCollision(const Point& pt, const SceneObject& obj) const;
   bool CollisionInProgress(const std::list<std::shared_ptr<SceneObject>>& collisions,
                            const std::shared_ptr<SceneObject>& obj) const;

   std::shared_ptr<kinex::Nui> mKinect;
   kinex::UserData mUserData;
   SDL_Surface* mTexture;

   // Remember objects that the player is currently colliding.
   // CheckAttackCollision() will only return true for the initial collision
   // with the object. It returns false if the player stays colliding.
   // As soon as the player is really not colliding any more, the status
   // is reset.
   std::list<std::shared_ptr<SceneObject>> mLeftHandAttacks;
   std::list<std::shared_ptr<SceneObject>> mRightHandAttacks;
   std::list<std::shared_ptr<SceneObject>> mLeftFootAttacks;
   std::list<std::shared_ptr<SceneObject>> mRightFootAttacks;
};

#endif // PLAYER_HPP
