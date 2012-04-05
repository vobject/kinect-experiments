#include "Logic.h"
#include "Kinect.h"
#include "View.h"
#include "Sprite.h"
#include "Background.h"
#include "Actor.h"
#include "Log.h"

#include <iostream>

static void print_commands()
{
   std::cout << "Commands:\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

Logic::Logic(const std::shared_ptr<Renderer>& renderer)
   : mView(std::make_shared<View>(renderer))
   , mBackground(std::make_shared<Background>())
   , mActor(std::make_shared<Actor>())
   , mXScreen(0)
   , mYScreen(0)
   , mLastBgUpdateTime(0)
{
   mBackground->SetSize(2560, 480);
   mBackground->SetScreenSize(640, 480);

   mView->AddObject(mBackground);
   mView->AddObject(mActor);
}

Logic::~Logic()
{

}

void Logic::ProcessInput(const SDL_KeyboardEvent& ev)
{
   if (SDL_KEYDOWN == ev.type)
   {
      switch (ev.keysym.sym)
      {
      case SDLK_h:
         print_commands();
         break;
      case SDLK_LEFT:
         mBackground->ScrollRight(1);
         break;
      case SDLK_RIGHT:
         mBackground->ScrollLeft(1);
         break;
      default:
         break;
      }
   }
   else if (SDL_KEYUP == ev.type)
   {
      switch (ev.keysym.sym)
      {
      default:
         break;
      }
   }
}

void Logic::ProcessInput(const SDL_MouseButtonEvent& ev)
{
   if ((SDL_MOUSEBUTTONUP == ev.type) && (SDL_BUTTON_LEFT == ev.button))
   {
      auto obj = std::make_shared<Sprite>();
      obj->SetResourceId("Rectangle");
      obj->SetSize(20, 20);
      obj->SetPos(ev.x - (obj->GetWidth() / 2), ev.y - (obj->GetHeight() / 2));
      obj->SetZOrder(zo_Layer_3);
      mView->AddObject(obj);
   }
}

void Logic::ProcessInput(const std::shared_ptr<Kinect>& kinect)
{
   const auto users = kinect->GetUsers();
   if (users.empty()) {
      mActor->SetVisible(false);
      return;
   }

   mActor->Update(users[0]);
}

void Logic::Update(const int game_time, const int elapsed_time)
{
   if ((game_time - mLastBgUpdateTime) > BACKGROUND_UPDATE_DELTA)
   {
      ScrollBackground();
      mLastBgUpdateTime = game_time;
   }

   mView->Update(elapsed_time);
}

void Logic::Render()
{
   mView->Render();
}

void Logic::SetScreenSize(int x_res, int y_res)
{
   mXScreen = x_res;
   mYScreen = y_res;
}

void Logic::ScrollBackground()
{
   if (!mActor->IsVisible()) {
      return;
   }

   const int actor_x_center = mActor->GetXCenter();
   if (std::abs(actor_x_center) < 30) {
      return;
   }

   const int scroll_speed = (std::abs(actor_x_center) - 30) / 30;
   const bool walk_forward = (actor_x_center > 0) ? true : false;

   if (walk_forward)
   {
      mBackground->ScrollLeft(scroll_speed);
   }
   else
   {
      mBackground->ScrollRight(scroll_speed);
   }
}
