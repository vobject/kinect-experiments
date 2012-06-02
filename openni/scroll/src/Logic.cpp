#include "Logic.hpp"
#include "Renderer.hpp"
#include "ResourceCache.hpp"
#include "Kinect.hpp"
#include "Level.hpp"
#include "Sprite.hpp"
//#include "Particle.hpp"
//#include "Background.h"
#include "Player.hpp"
//#include "Enemy.hpp"
#include "Utils.hpp"

#include <algorithm>
#include <iostream>

//template<class T>
//struct SortBy_SharedPtr_Content
//{
//   bool operator()(const std::shared_ptr<T>& lhs, const std::shared_ptr<T>& rhs) const
//   {
//      return *lhs < *rhs;
//   }
//};

static void print_commands()
{
   std::cout << "Commands:\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

Logic::Logic(
   const std::shared_ptr<Renderer>& renderer,
   const std::shared_ptr<ResourceCache>& res,
   const std::shared_ptr<kinex::Nui>& kinect
)
   : mRenderer(renderer)
   , mResCache(res)
{
   mLevel = std::make_shared<Level>("test", mResCache);
//   mBackground = std::make_shared<Background>(mResCache->GetBackground("background"));
//   // TODO: Background must have a "buttom" coordinate.

   mPlayer = std::make_shared<Player>(kinect);
   mPlayer->SetSize({ 468_px, 324_px });
   mPlayer->SetPosition({ 100, 140 });

//   mEnemy = std::make_shared<Enemy>(mResCache->GetSprite("enemy1"));
//   mEnemy->SetSize({ 164_px, 360_px });
//   mEnemy->SetPosition({ 450, 178 });

   srand(time(NULL));
}

Logic::~Logic()
{

}

void Logic::ProcessInput(const SDL_KeyboardEvent& ev)
{
   // Event based keyboard-input handling:
   //  ---> if a key is pressed or released, handle the input immediately or
   //       set the corresponding logic state.
   // "Is-key-still-pressed"-handling does not belong here.

   if (SDL_KEYDOWN == ev.type)
   {
      switch (ev.keysym.sym)
      {
      case SDLK_h:
         print_commands();
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
//   if ((SDL_MOUSEBUTTONUP == ev.type) && (SDL_BUTTON_LEFT == ev.button))
//   {
//      auto obj = std::make_shared<Sprite>(mResCache->GetSprite("blood_b"));
//      obj->SetSize({ 192_px, 192_px });
//      obj->SetPosition({ ev.x - (obj->GetSize().Width / 2), ev.y - (obj->GetSize().Height / 2) });
////      obj->SetDirection(-1, 1);
////      obj->SetSpeed(3, 2);
//      mSprites.push_back(obj);
//
////      auto obj = std::make_shared<Particle>();
////      obj->SetPosition({ ev.x - (obj->GetSize().Width / 2), ev.y - (obj->GetSize().Height / 2) });
////      mParticles.push_back(obj);
//   }
//   else if ((SDL_MOUSEBUTTONUP == ev.type) && (SDL_BUTTON_RIGHT == ev.button))
//   {
//      auto obj = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//      obj->SetSize({ 64_px, 64_px });
//      obj->SetPosition({ ev.x - (obj->GetSize().Width / 2), ev.y - (obj->GetSize().Height / 2) });
//      obj->SetDirection(-1, 0);
//      obj->SetSpeed(2, 2);
//      mSprites.push_back(obj);
//   }
}

//void Logic::ProcessInput(const Kinect& kinect)
//{
//   const auto users = kinect.GetUsers();
//   if (users.empty()) {
//      mActor->SetVisible(false);
//      return;
//   }
//
//   mActor->SetInputData(users[0]);
//}

void Logic::Update(const int app_time, const int elapsed_time)
{
   mLevel->Update(elapsed_time);
   mPlayer->Update(elapsed_time);

   auto obj = std::begin(mSprites);
   while (obj != std::end(mSprites))
   {
       if ((*obj)->IsAlive())
       {
          (*obj)->Update(elapsed_time);
          obj++;
       }
       else
       {
          obj = mSprites.erase(obj); // Remove dead sprite.
       }
   }

   for (auto obj : mLevel->mSprites)
   {
      Point collision(0, 0);

      if (mPlayer->CheckAttackCollision(obj, collision))
      {
         // player deals damage

         const auto size = rand() % (512 - 96) + 96;
         auto pos_shift = size / 100 * 2;
         auto hit_shift = 24;
         if (PlayerOrientation::Left == mPlayer->GetOrientation()) {
            pos_shift = -pos_shift;
            hit_shift = -hit_shift;
         }

         const auto anim = rand() % 4;
         std::string anim_name;
         switch (anim) {
            case 0:
               anim_name = "blood_a";
               break;
            case 1:
               anim_name = "blood_b";
               break;
            case 2:
               anim_name = "blood_c";
               break;
            case 3:
               anim_name = "blood_d";
               break;
         }

         auto dam = std::make_shared<Sprite>(mResCache->GetSprite(anim_name));
         dam->SetSize({ size, size });
         dam->SetPosition({ collision.X - (dam->GetSize().Width / 2) + hit_shift, collision.Y - (dam->GetSize().Height / 2) });
         mSprites.push_back(dam);

         obj->SetPosition({obj->GetPosition().X + pos_shift, obj->GetPosition().Y});
      }
      else if (mPlayer->CheckGenericCollision(obj, collision))
      {
         // player takes damage
      }
   }

//   // HACK
//   static bool still_colliding = false;
//
//   Point collision(0, 0);
//   if (mPlayer->CheckCollision(*mEnemy, collision))
//   {
//      if (!still_colliding)
//      {
//         auto obj = std::make_shared<Sprite>(mResCache->GetSprite("blood_b"));
//         obj->SetSize({ 256_px, 256_px });
//         obj->SetPosition({ collision.X - (obj->GetSize().Width / 2) + 24, collision.Y - (obj->GetSize().Height / 2) });
////         obj->SetPosition({ collision.X, collision.Y });
//         mSprites.push_back(obj);
//         still_colliding = true;
//      }
//
//   }
//   else
//   {
//      still_colliding = false;
//   }

//   const Uint8* keystate = SDL_GetKeyState(nullptr);
//
//   if (keystate[SDLK_LEFT])
//   {
//      mBackground->ScrollLeft(1);
//   }
//
//   if (keystate[SDLK_RIGHT])
//   {
//      mBackground->ScrollRight(1);
//   }
//
//   UpdateBackground(app_time, elapsed_time);
//   UpdatePlayer(app_time, elapsed_time);
//   UpdateEnemies(app_time, elapsed_time);
//
////   if(rand() % 1000 == 0)
////   {
////      auto obj = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
////      obj->SetSize({ 50_px, 50_px });
////      obj->SetPosition({ rand() % mXScreen, rand() % mYScreen });
////      obj->SetDirection(-1, 0);
////      obj->SetSpeed(2, 2);
////      mSprites.push_back(obj);
////   }
}

void Logic::Render()
{
//   mSprites.sort(SortBy_SharedPtr_Content<Sprite>());

   mRenderer->PreRender();
   mRenderer->Render(mLevel->mBackground);
   mRenderer->Render(mLevel->mSprites);
//   mRenderer->Render(mEnemy);
   mRenderer->Render(mPlayer);
   mRenderer->Render(mSprites);

//   for (auto& obj : mParticles) {
//      SDL_Rect rect = { (Sint16)obj->GetPosition().X, (Sint16)obj->GetPosition().Y,
//                        (Uint16)obj->GetSize().Width, (Uint16)obj->GetSize().Height };
//      SDL_FillRect(mRenderer->mSurface, &rect, 0xff55ff);
//   }

   mRenderer->PostRender();
}

//void Logic::UpdateBackground(const int app_time, const int elapsed_time)
//{
////   if (!mPlayer->IsVisible()) {
////      return;
////   }
//
////   const int actor_x_center = mActor->GetXCenter();
////   if (std::abs(actor_x_center) < 30) {
////      return;
////   }
////
////   const int scroll_speed = (std::abs(actor_x_center) - 30) / 30;
////   const bool walk_forward = (actor_x_center > 0) ? true : false;
////
////   if (walk_forward)
////   {
////      mBackground->ScrollLeft(scroll_speed);
////   }
////   else
////   {
////      mBackground->ScrollRight(scroll_speed);
////   }
//
//   mBackground->Update(elapsed_time);
//}

//void Logic::UpdatePlayer(const int app_time, const int elapsed_time)
//{
//   // TODO: Trigger an animation on collision
//
////   for (auto& obj : mSprites)
////   {
////       if (mActor->CheckCollision(obj))
////       {
////          obj->SetVisible(false);
////       }
////   }
//
////   const int x_center = mPlayer->GetXCenter();
////   const int y_center = mPlayer->GetYCenter();
////   mPlayer->SetPos((mXScreen / 2) - x_center, (mYScreen / 2) - y_center);
//
////   const int x_center = mPlayer->GetXCenter();
////   static int i = 1;
////   const int x_center = mPlayer->mUserData.GetPerspectiveJoints()[XN_SKEL_TORSO].X;
////   const int x_left_hand = mPlayer->mUserData.GetPerspectiveJoints()[XN_SKEL_LEFT_HAND].X;
////   const int y_left_hand = mPlayer->mUserData.GetPerspectiveJoints()[XN_SKEL_LEFT_HAND].Y;
////
////   if (mPlayer->IsVisible() && i == 1) {
////      if (((x_left_hand - abs(x_center)) > 30) || ((x_left_hand - abs(x_center)) < 30))
////      {
////         const auto res_id = "blood_b";
////         const auto frames = mResCache->GetSpriteFrames(res_id);
////
////         auto obj = std::make_shared<Sprite>(res_id, frames, true);
////         obj->SetSize(200, 200);
////         obj->SetPos(x_left_hand, y_left_hand);
////         obj->SetZOrder(ZOrder::zo_Layer_3);
////         obj->SetDirection(0, 0);
////         obj->SetSpeed(0, 0);
////         mSprites.push_back(obj);
////         i++;
////      }
////   }
//
//   mPlayer->Update(elapsed_time);
//
//   if (!mPlayer->IsVisible()) {
//      return;
//   }
//
//   // HACK
//   static bool still_colliding = false;
//
//   Point collision(0, 0);
//   if (mPlayer->CheckCollision(*mEnemy, collision))
//   {
//      if (!still_colliding)
//      {
//         auto obj = std::make_shared<Sprite>(mResCache->GetSprite("blood_b"));
//         obj->SetSize({ 256_px, 256_px });
//         obj->SetPosition({ collision.X - (obj->GetSize().Width / 2) + 24, collision.Y - (obj->GetSize().Height / 2) });
////         obj->SetPosition({ collision.X, collision.Y });
//         mSprites.push_back(obj);
//         still_colliding = true;
//      }
//
//   }
//   else
//   {
//      still_colliding = false;
//   }
//}

//void Logic::UpdateEnemies(const int app_time, const int elapsed_time)
//{
//   auto obj = std::begin(mSprites);
//
//   while (obj != std::end(mSprites))
//   {
//       if ((*obj)->IsAlive())
//       {
//          (*obj)->Update(elapsed_time);
//          obj++;
//       }
//       else
//       {
//          obj = mSprites.erase(obj); // Remove dead sprite.
//       }
//   }
//}
