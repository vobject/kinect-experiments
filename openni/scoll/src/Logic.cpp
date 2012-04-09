#include "Logic.h"
#include "Renderer.h"
#include "ResourceCache.h"
#include "Kinect.h"
#include "Sprite.h"
#include "Background.h"
#include "Actor.h"
#include "Log.h"

#include <algorithm>
#include <iostream>

template<class T>
struct SortBy_SharedPtr_Content
{
   bool operator()(const std::shared_ptr<T>& lhs, const std::shared_ptr<T>& rhs) const
   {
      return *lhs < *rhs;
   }
};

static void print_commands()
{
   std::cout << "Commands:\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

Logic::Logic(
   const std::shared_ptr<Renderer>& renderer,
   const std::shared_ptr<ResourceCache>& res,
   const std::shared_ptr<Kinect>& kinect
)
   : mRenderer(renderer)
   , mResCache(res)
   , mXScreen(0)
   , mYScreen(0)
   , mLastBgUpdateTime(0) // TODO: Move this into Background class
{
   const auto bg_id = "background";
   const auto bg_frame = mResCache->GetSpriteFrames(bg_id).at(0);
   mBackground = std::make_shared<Background>(bg_id, bg_frame);

   mActor = std::make_shared<Actor>(kinect);

//   srand(time(NULL));
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
         mBackground->ScrollRight(4);
         break;
      case SDLK_RIGHT:
         mBackground->ScrollLeft(4);
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
      const auto res_id = "blood_b";
      const auto frames = mResCache->GetSpriteFrames(res_id);

      auto obj = std::make_shared<Sprite>(res_id, frames, true);
      obj->SetSize(200, 200);
      obj->SetPos(ev.x - (obj->GetXRes() / 2), ev.y - (obj->GetYRes() / 2));
      obj->SetZOrder(ZOrder::zo_Layer_3);
      obj->SetDirection(-1, 1);
      obj->SetSpeed(3, 2);
      mSprites.push_back(obj);
   }
   else if ((SDL_MOUSEBUTTONUP == ev.type) && (SDL_BUTTON_RIGHT == ev.button))
   {
      auto obj = std::make_shared<Sprite>("Rectangle");
      obj->SetSize(60, 60);
      obj->SetPos(ev.x - (obj->GetXRes() / 2), ev.y - (obj->GetYRes() / 2));
      obj->SetZOrder(ZOrder::zo_Layer_2);
      obj->SetDirection(-1, 0);
      obj->SetSpeed(2, 2);
      mSprites.push_back(obj);
   }
}

void Logic::ProcessInput(const std::shared_ptr<Kinect>& kinect)
{
   // TODO: Actor reengineering!

//   const auto users = kinect->GetUsers();
//   if (users.empty()) {
//      mActor->SetVisible(false);
//      return;
//   }
//
//   mActor->Update(users[0]);
}

void Logic::Update(const int game_time, const int elapsed_time)
{
   if ((game_time - mLastBgUpdateTime) > BACKGROUND_UPDATE_DELTA)
   {
      ScrollBackground();
      mLastBgUpdateTime = game_time;
   }

   // TODO: Check for dead sprites and remove them
   // TODO: Trigger an animation on collision

//   for (auto& obj : mSprites)
//   {
//       if (mActor->CheckCollision(obj))
//       {
//          obj->SetVisible(false);
//       }
//   }

   for (auto& obj : mSprites)
   {
       obj->Update(elapsed_time);
   }

//   if(rand() % 2000 == 0)
//   {
//      auto obj = std::make_shared<Sprite>();
//      obj->SetResourceId("Rectangle");
//      obj->SetSize(50, 50);
//      obj->SetPos(rand() % ((mXScreen / 2) - (mXScreen + 2)), rand() % (mYScreen - 60));
//      obj->SetZOrder(zo_Layer_3);
//      obj->SetDirection(-1, 0);
//      obj->SetSpeed(2, 2);
//      mSceneObjects.push_back(obj);
//   }
}

void Logic::Render()
{
   mSprites.sort(SortBy_SharedPtr_Content<Sprite>());

   mRenderer->PreRender();
   mRenderer->Render(mBackground);
   mRenderer->Render(mSprites);
   mRenderer->Render(mActor);
   mRenderer->PostRender();
}

void Logic::SetScreenSize(const int x_res, const int y_res)
{
   mXScreen = x_res;
   mYScreen = y_res;

   mBackground->SetScreenSize(mXScreen, mYScreen);
}

void Logic::ScrollBackground()
{
   // TODO: Actor reengineering!

//   if (!mActor->IsVisible()) {
//      return;
//   }
//
//   const int actor_x_center = mActor->GetXCenter();
//   if (std::abs(actor_x_center) < 30) {
//      return;
//   }
//
//   const int scroll_speed = (std::abs(actor_x_center) - 30) / 30;
//   const bool walk_forward = (actor_x_center > 0) ? true : false;
//
//   if (walk_forward)
//   {
//      mBackground->ScrollLeft(scroll_speed);
//   }
//   else
//   {
//      mBackground->ScrollRight(scroll_speed);
//   }
}
