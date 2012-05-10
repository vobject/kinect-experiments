#ifndef LOGIC_H
#define LOGIC_H

#include <memory>
#include <list>

#include <SDL_events.h>

class Kinect;
class Renderer;
class ResourceCache;
class Sprite;
class Background;
class Player;

class Logic
{
public:
   Logic(const std::shared_ptr<Renderer>& renderer,
         const std::shared_ptr<ResourceCache>& res,
         const std::shared_ptr<Kinect>& kinect);
   virtual ~Logic();

   Logic(const Logic&) = delete;
   Logic& operator=(const Logic&) = delete;

   virtual void ProcessInput(const SDL_KeyboardEvent& ev);
   virtual void ProcessInput(const SDL_MouseButtonEvent& ev);
//   virtual void ProcessInput(const Kinect& kinect);
   virtual void Update(int game_time, int elapsed_time);
   virtual void Render();

   // Needed to know the direction and speed of scrolling.
   void SetScreenSize(int x_res, int y_res);

private:
   void UpdateBackground(int game_time, int elapsed_time);
   void UpdatePlayer(int game_time, int elapsed_time);
   void UpdateEnemies(int game_time, int elapsed_time);

   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Background> mBackground;
   std::shared_ptr<Player> mPlayer;
   std::list<std::shared_ptr<Sprite>> mSprites;

   int mXScreen;
   int mYScreen;

//   ProcessManager* m_pProcessManager;
//   LevelManager* m_pLevelManager;

//   ActorMap m_actors;
//   ActorId m_LastActorId;
//   GameViewList m_gameViews;
//   ActorFactory* m_pActorFactory;
};

#endif // LOGIC_H
