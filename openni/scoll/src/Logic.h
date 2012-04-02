#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

class Renderer;
class View;

class Logic
{
public:
   Logic(std::shared_ptr<Renderer> renderer);
   virtual ~Logic();

   virtual void Update(int game_time, int elapsed_time);
   virtual void Render();

private:
//   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<View> mView;

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
