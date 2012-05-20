#ifndef LOGIC_HPP
#define LOGIC_HPP

#include "Utils.hpp"

#include <memory>
#include <list>

#include <SDL_events.h>

namespace kinex {
   class Nui;
}
class Renderer;
class ResourceCache;
class Sprite;
class Particle;
class Background;
class Player;

class Logic
{
public:
   Logic(const std::shared_ptr<Renderer>& renderer,
         const std::shared_ptr<ResourceCache>& res,
         const std::shared_ptr<kinex::Nui>& kinect);
   virtual ~Logic();

   Logic(const Logic&) = delete;
   Logic& operator=(const Logic&) = delete;

   virtual void ProcessInput(const SDL_KeyboardEvent& ev);
   virtual void ProcessInput(const SDL_MouseButtonEvent& ev);
//   virtual void ProcessInput(const Kinect& kinect);
   virtual void Update(int app_time, int elapsed_time);
   virtual void Render();

private:
   void UpdateBackground(int app_time, int elapsed_time);
   void UpdatePlayer(int app_time, int elapsed_time);
   void UpdateEnemies(int app_time, int elapsed_time);

   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Background> mBackground;
   std::shared_ptr<Player> mPlayer;
   std::list<std::shared_ptr<Sprite>> mSprites;
//   std::list<std::shared_ptr<Particle>> mParticles;

   Size mScreenSize = { 0, 0 };

//   ProcessManager* m_pProcessManager;
//   LevelManager* m_pLevelManager;

//   ActorMap m_actors;
//   ActorId m_LastActorId;
//   GameViewList m_gameViews;
//   ActorFactory* m_pActorFactory;
};

#endif // LOGIC_HPP
