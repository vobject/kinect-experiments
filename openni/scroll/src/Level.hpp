#ifndef LEVEL_HPP
#define LEVEL_HPP

//#include "Utils.hpp"

#include <memory>
#include <list>
#include <map>

//#include <SDL_events.h>

//namespace kinex {
//   class Nui;
//}
//class Renderer;
class ResourceCache;
class Sprite;
//class Particle;
class Background;
class Player;
class PlayerInput;
//class Enemy;
class ScreenPos;

class Level
{
   friend class Logic;
//   friend class Player;

public:
   Level(const std::string& name, const std::shared_ptr<ResourceCache>& res);
   virtual ~Level();

   Level(const Level&) = delete;
   Level& operator=(const Level&) = delete;

   virtual void Update(int elapsed_time);

   void ProcessInput(const PlayerInput& input);
//   void HandlePunch(const ScreenPos& pos);

private:
   void HandlePunch(const ScreenPos& pos, std::list<std::shared_ptr<Sprite>>& contact);
//   void UpdateBackground(int app_time, int elapsed_time);
//   void UpdatePlayer(int app_time, int elapsed_time);
//   void UpdateEnemies(int app_time, int elapsed_time);

   bool CheckCollision(const ScreenPos& pos, const Sprite& obj) const;
   bool CollisionInProgress(const std::list<std::shared_ptr<Sprite>>& collisions,
                            const std::shared_ptr<Sprite>& obj) const;

   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Background> mBackground;
//   std::shared_ptr<Enemy> mEnemy;
   std::list<std::shared_ptr<Sprite>> mEnemies;
   std::list<std::shared_ptr<Sprite>> mSprites;
//   std::list<std::shared_ptr<Particle>> mParticles;
//   std::map<std::shared_ptr<Sprite>, bool> mHitMap;

   std::map<std::string, std::list<std::shared_ptr<Sprite>>> mSpriteContacts;
//   std::list<std::shared_ptr<Sprite>> mLeftHandAttacks;
//   std::list<std::shared_ptr<Sprite>> mRightHandAttacks;

//   Size mScreenSize = { 0, 0 };

//   ProcessManager* m_pProcessManager;
//   LevelManager* m_pLevelManager;

//   ActorMap m_actors;
//   ActorId m_LastActorId;
//   GameViewList m_gameViews;
//   ActorFactory* m_pActorFactory;
};

#endif // LEVEL_HPP
