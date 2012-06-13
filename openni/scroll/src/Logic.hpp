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
class Level;
class Sprite;
//class Particle;
//class Background;
class Player;
//class Enemy;

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
   virtual void ProcessInput(const kinex::Nui& kinect);

   virtual void Update(int app_time, int elapsed_time);
   virtual void Render();

private:
   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Level> mLevel;
   std::shared_ptr<Player> mPlayer;

//   ProcessManager* mProcessManager;
//   LevelManager* mLevelManager;

//   ActorMap m_actors;
//   ActorId m_LastActorId;
//   GameViewList m_gameViews;
//   ActorFactory* m_pActorFactory;
};

#endif // LOGIC_HPP
