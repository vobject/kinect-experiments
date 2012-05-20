#include "Particle.hpp"
#include "Utils.hpp"

//Particle::Particle()
//   : mLifetime(2000_ms)
//   , mMsPerPosUpdate(15) // TODO: Move this info into the resource
//   , mElapsedPosTime(0)
//   , mXDirection(rand() % 1)
//   , mYDirection(rand() % 1)
//   , mXSpeed(rand() % 4)
//   , mYSpeed(rand() % 4)
//{
//   SetSize({10, 10});
//   SetZOrder(ZOrder::zo_Layer_3);
//}
//
//Particle::~Particle()
//{
//
//}
//
//void Particle::Update(const int elapsed_time)
//{
////   if (mIsPaused) {
////      return;
////   }
//
//   mElapsedPosTime += elapsed_time;
//   UpdatePosition();
//}
//
////void Sprite::SetMsPerFrame(const int ms)
////{
////   mMsPerFrame = ms;
////}
////
////void Sprite::SetMsPerPosition(const int ms)
////{
////   mMsPerPosUpdate = ms;
////}
////
////void Sprite::SetDirection(const int x_dir, const int y_dir)
////{
////   mXDirection = x_dir;
////   mYDirection = y_dir;
////}
////
////void Sprite::SetSpeed(const int x_speed, const int y_speed)
////{
////   mXSpeed = x_speed;
////   mYSpeed = y_speed;
////}
////
////int Sprite::GetCurrentFrame() const
////{
////   return mCurrentFrame;
////}
////
////void Sprite::UpdateFrame()
////{
////   if (1 == mFrameCount) {
////      return;
////   }
////
////   if(mElapsedFrameTime >= mMsPerFrame)
////   {
////      const int adv_cnt = mElapsedFrameTime / mMsPerFrame;
////      mElapsedFrameTime -= (adv_cnt * mMsPerFrame);
////
////      int new_frame_index = mCurrentFrame + adv_cnt;
////
////      if(!mIsLooping && (new_frame_index >= mFrameCount))
////      {
////         new_frame_index = mFrameCount - 1;
////         SetAlive(false);
////      }
////
////      mCurrentFrame = new_frame_index % mFrameCount;
////   }
////}
//
//void Particle::UpdatePosition()
//{
//   if(mElapsedPosTime >= mMsPerPosUpdate)
//   {
//      const int adv_cnt = mElapsedPosTime / mMsPerPosUpdate;
//      mElapsedPosTime -= (adv_cnt * mMsPerPosUpdate);
//
//      SetPosition({ GetPosition().X + (mXDirection * mXSpeed * adv_cnt),
//                    GetPosition().Y + (mYDirection * mYSpeed * adv_cnt) });
//   }
//}
//
////void Sprite::SetAnimation(const bool is_paused, const bool is_looping)
////{
////   mIsPaused = is_paused;
////   mIsLooping = is_looping;
////}
