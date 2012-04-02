#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

#include <SDL_events.h>

class Renderer;
class View;

//enum InputType
//{
//   it_Invalid,
//   it_Keyboard,
//   it_Mouse,
//   it_Kinect,
//   INPUT_TYPE_ITEM_COUNT
//};
//
//struct InputOption
//{
//   InputOption() : input_type(it_Invalid)
//                 , event_type(0)
//                 , w_param(0)
//                 , l_param(0)
//                 { }
//
//   InputType input_type;
//   int event_type;
//   int w_param;
//   int l_param;
//};

class Logic
{
public:
   Logic(std::shared_ptr<Renderer> renderer);
   virtual ~Logic();

   virtual void ProcessInput(const SDL_KeyboardEvent& ev);
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
