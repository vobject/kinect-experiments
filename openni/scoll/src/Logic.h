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
class Actor;

class Logic
{
public:
   Logic(const std::shared_ptr<Renderer>& renderer, std::shared_ptr<ResourceCache>& res);
   virtual ~Logic();

   virtual void ProcessInput(const SDL_KeyboardEvent& ev);
   virtual void ProcessInput(const SDL_MouseButtonEvent& ev);
   virtual void ProcessInput(const std::shared_ptr<Kinect>& kinect);
   virtual void Update(int game_time, int elapsed_time);
   virtual void Render();

   // Needed to know the direction and speed of scrolling.
   void SetScreenSize(int x_res, int y_res);

private:
   void ScrollBackground();

   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Background> mBackground;
   std::shared_ptr<Actor> mActor;
   std::list<std::shared_ptr<Sprite>> mSprites;

   int mXScreen;
   int mYScreen;

   // In milliseconds - Determines the minimum scroll speed.
   const int BACKGROUND_UPDATE_DELTA = 1000 / 60;

   int mLastBgUpdateTime;

//   ProcessManager* m_pProcessManager;
//   LevelManager* m_pLevelManager;

//   ActorMap m_actors;
//   ActorId m_LastActorId;
//   GameViewList m_gameViews;
//   ActorFactory* m_pActorFactory;

   Logic(const Logic&);
   const Logic& operator=(const Logic&);
};

#endif // LOGIC_H
