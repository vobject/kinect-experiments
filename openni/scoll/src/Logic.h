#ifndef LOGIC_H
#define LOGIC_H

#include <memory>

#include <SDL_events.h>

class Kinect;
class Renderer;
class View;
class Background;
class Actor;

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
   Logic(const std::shared_ptr<Renderer>& renderer);
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

//   std::shared_ptr<Kinect> mKinect;
   std::shared_ptr<View> mView;

   std::shared_ptr<Background> mBackground;
   std::shared_ptr<Actor> mActor;

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
