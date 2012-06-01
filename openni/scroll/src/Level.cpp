#include "Level.hpp"
//#include "Renderer.hpp"
#include "ResourceCache.hpp"
//#include "Kinect.hpp"
#include "Sprite.hpp"
//#include "Particle.hpp"
#include "Background.h"
//#include "Player.hpp"
//#include "Enemy.hpp"
#include "Utils.hpp"

Level::Level(const std::string& name, const std::shared_ptr<ResourceCache>& res)
{
   mBackground = std::make_shared<Background>(res->GetBackground("bg2"));

   auto obj1 = std::make_shared<Sprite>(res->GetSprite("ken"), true);
   obj1->SetMsPerFrame(100);
   obj1->SetSize({ 124_px, 300_px });
   obj1->SetPosition({ 460, 158 });
   mSprites.push_back(obj1);

   auto obj2 = std::make_shared<Sprite>(res->GetSprite("hulk"), true);
   obj2->SetMsPerFrame(100);
   obj2->SetSize({ 250_px, 230_px });
   obj2->SetPosition({ 10, 230 });
   mSprites.push_back(obj2);

//   auto obj2 = std::make_shared<Sprite>(res->GetSprite("arcanister"));
//   obj2->SetSize({ 64_px, 64_px });
//   obj2->SetPosition({ 100, 30 });
//   mSprites.push_back(obj2);
//
//   auto obj3 = std::make_shared<Sprite>(res->GetSprite("arcanister"));
//   obj3->SetSize({ 32_px, 32_px });
//   obj3->SetPosition({ 400, 400 });
//   mSprites.push_back(obj3);
}

Level::~Level()
{

}

void Level::Update(const int elapsed_time)
{
   mBackground->Update(elapsed_time);

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
