#include "Level.hpp"
#include "ResourceCache.hpp"
//#include "Kinect.hpp"
#include "Sprite.hpp"
#include "Background.h"
#include "PlayerInput.hpp"
//#include "Enemy.hpp"
#include "Utils.hpp"

#include <algorithm>

Level::Level(const std::string& name, const std::shared_ptr<ResourceCache>& res)
   : mResCache(res)
{
   mBackground = std::make_shared<Background>(mResCache->GetBackground("bg1"));

   auto obj1 = std::make_shared<Sprite>(mResCache->GetSprite("ken"), true);
   obj1->SetMsPerFrame(100);
   obj1->SetSize({ 224_px, 600_px });
   obj1->SetPosition({ 660, 158 });
   mEnemies.push_back(obj1);

//   auto obj2 = std::make_shared<Sprite>(mResCache->GetSprite("hulk"), true);
//   obj2->SetMsPerFrame(100);
//   obj2->SetSize({ 250_px, 230_px });
//   obj2->SetPosition({ 10, 230 });
//   mEnemies.push_back(obj2);
//   mHitMap[obj2] = false;

//   auto obj2 = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//   obj2->SetSize({ 64_px, 64_px });
//   obj2->SetPosition({ 100, 30 });
//   mSprites.push_back(obj2);
//
//   auto obj3 = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//   obj3->SetSize({ 32_px, 32_px });
//   obj3->SetPosition({ 400, 400 });
//   mSprites.push_back(obj3);

   srand(time(NULL));
}

Level::~Level()
{

}

void Level::Update(const int elapsed_time)
{
   mBackground->Update(elapsed_time);

   auto enemy = std::begin(mEnemies);
   while (enemy != std::end(mEnemies))
   {
       if ((*enemy)->IsAlive())
       {
          (*enemy)->Update(elapsed_time);
          enemy++;
       }
       else
       {
          enemy = mEnemies.erase(enemy); // Remove dead sprite.
       }
   }

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
}

void Level::ProcessInput(const PlayerInput& input)
{
   const auto punch_l = input.LeftPunch();
   if (punch_l.present) {
      HandlePunch(punch_l.pos, mSpriteContacts["hand_left"]);
   }

   const auto punch_r = input.RightPunch();
   if (punch_r.present) {
      HandlePunch(punch_r.pos, mSpriteContacts["hand_right"]);
   }

   const auto kick_l = input.LeftKick();
   if (kick_l.present) {
      HandlePunch(kick_l.pos, mSpriteContacts["foot_left"]);
   }

   const auto kick_r = input.RightKick();
   if (kick_r.present) {
      HandlePunch(kick_r.pos, mSpriteContacts["foot_right"]);
   }

   const auto hadouken = input.Hadouken();
   if (hadouken.present && hadouken.first) {
      auto hadouken_obj = std::make_shared<Sprite>(mResCache->GetSprite("fireball"), true);
      hadouken_obj->SetSize({ 256_px, 192_px });
      hadouken_obj->SetPosition({ hadouken.pos.X - (hadouken_obj->GetSize().Width / 2), hadouken.pos.Y - (hadouken_obj->GetSize().Height / 2) });
      hadouken_obj->SetDirection(1, 0);
      hadouken_obj->SetSpeed(4, 0);
      mSprites.push_back(hadouken_obj);
   }
}

void Level::HandlePunch(
   const ScreenPos& pos,
   std::list<std::shared_ptr<Sprite>>& contact
)
{
   for (auto obj : mEnemies)
   {
      if (!CheckCollision(pos, *obj)) {
         contact.remove(obj);
         continue;
      }

      if (CollisionInProgress(contact, obj)) {
         continue;
      }
      contact.push_back(obj);

      const auto size = rand() % (512 - 96) + 96;
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
      dam->SetPosition({ pos.X - (dam->GetSize().Width / 2), pos.Y - (dam->GetSize().Height / 2) });
      mSprites.push_back(dam);
   }
}

bool Level::CheckCollision(const ScreenPos& pos, const Sprite& obj) const
{
   return (pos.X > obj.GetPosition().X) &&
          (pos.X < obj.GetPosition().X + obj.GetSize().Width) &&
          (pos.Y > obj.GetPosition().Y) &&
          (pos.Y < obj.GetPosition().Y + obj.GetSize().Height);
}

bool Level::CollisionInProgress(
   const std::list<std::shared_ptr<Sprite>>& collisions,
   const std::shared_ptr<Sprite>& obj
) const
{
   const auto existing = std::find(collisions.begin(), collisions.end(), obj);

   // The object to check is inside the "currently colliding with"-list.
   // By convention we return true only for the initial collision.
   return existing != collisions.end();
}

//void Logic::Update(const int app_time, const int elapsed_time)
//{
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
//}

//void Logic::Render()
//{
//   mSprites.sort(SortBy_SharedPtr_Content<Sprite>());
//
//   mRenderer->PreRender();
//   mRenderer->Render(mBackground);
//   mRenderer->Render(mEnemy);
//   mRenderer->Render(mPlayer);
//   mRenderer->Render(mSprites);
//
////   for (auto& obj : mParticles) {
////      SDL_Rect rect = { (Sint16)obj->GetPosition().X, (Sint16)obj->GetPosition().Y,
////                        (Uint16)obj->GetSize().Width, (Uint16)obj->GetSize().Height };
////      SDL_FillRect(mRenderer->mSurface, &rect, 0xff55ff);
////   }
//
//   mRenderer->PostRender();
//}

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
