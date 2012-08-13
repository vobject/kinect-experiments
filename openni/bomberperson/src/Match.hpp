#ifndef MATCH_HPP
#define MATCH_HPP

#include "Utils.hpp"

#include <memory>
#include <tuple>
#include <vector>

//class ResourceCache;
class Field;
class Cell;
class Player;
class Bomb;
class Explosion;
class SceneObject;

class Match
{
public:
   Match(const std::shared_ptr<Field>& playing_field,
         const std::vector<std::shared_ptr<Player>>& players);
   virtual ~Match();

   Match(const Match&) = delete;
   Match& operator=(const Match&) = delete;

   void Update(int elapsed_time);

   std::shared_ptr<Field> GetField() const;
   std::vector<std::shared_ptr<Player>> GetPlayers() const;
//   std::vector<std::shared_ptr<Bomb>> GetBombs() const;
   std::vector<std::shared_ptr<Explosion>> GetExplosions() const;

//   int GetRows() const;
//   int GetColumns() const;
//   int GetCellWidth() const;
//   int GetCellHeight() const;

private:
   std::shared_ptr<Cell> GetCellFromObject(const std::shared_ptr<SceneObject>& obj) const;
//   void HandlePlayerUpdate(std::shared_ptr<Player>& player, int elapsed_time);
//   void HandleBombUpdate(int elapsed_time);
//   void HandleExplosionUpdate(int elapsed_time);
//
//   std::tuple<int, int> GetParentCell(const std::shared_ptr<SceneObject>& obj) const;
//   std::tuple<int, int> GetCellCoordinate(const std::shared_ptr<SceneObject>& obj) const;
////   std::vector<std::shared_ptr<Cell>> GetAdjacentCells(const std::shared_ptr<Cell>& cell) const;
//
////   void HandlePunch(const ScreenPos& pos, std::list<std::shared_ptr<Sprite>>& contact);
//////   void UpdateBackground(int app_time, int elapsed_time);
//////   void UpdatePlayer(int app_time, int elapsed_time);
//////   void UpdateEnemies(int app_time, int elapsed_time);
////
////   bool CheckCollision(const ScreenPos& pos, const Sprite& obj) const;
////   bool CollisionInProgress(const std::list<std::shared_ptr<Sprite>>& collisions,
////                            const std::shared_ptr<Sprite>& obj) const;
//
////   std::vector<std::pair<std::shared_ptr<Player>, std::shared_ptr<InputDevice>>> mPlayers;

   std::shared_ptr<Field> mField;
   std::vector<std::shared_ptr<Player>> mPlayers;
//   std::vector<std::shared_ptr<Bomb>> mBombs;
   std::vector<std::shared_ptr<Explosion>> mExplosions;

//   std::shared_ptr<ResourceCache> mResCache;
//   std::shared_ptr<Background> mBackground;
////   std::shared_ptr<Enemy> mEnemy;
//   std::list<std::shared_ptr<Sprite>> mEnemies;
//   std::list<std::shared_ptr<Sprite>> mSprites;
////   std::list<std::shared_ptr<Particle>> mParticles;
////   std::map<std::shared_ptr<Sprite>, bool> mHitMap;
//
//   std::map<std::string, std::list<std::shared_ptr<Sprite>>> mSpriteContacts;
////   std::list<std::shared_ptr<Sprite>> mLeftHandAttacks;
////   std::list<std::shared_ptr<Sprite>> mRightHandAttacks;
};

#endif // MATCH_HPP
