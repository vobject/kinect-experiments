#include "Enemy.hpp"
#include "SpriteResource.h"
#include "Utils.hpp"

Enemy::Enemy(
   const SpriteResource& res,
   const bool looping /*=false*/
)
   : Sprite(res, looping)
{

}

Enemy::~Enemy()
{

}

//void Enemy::Update(const int elapsed_time)
//{
//   mElapsedFrameTime += elapsed_time;
//   mElapsedPosTime += elapsed_time;
//
//   UpdateFrame();
//   UpdatePosition();
//}
//
//
//void Sprite::UpdateFrame()
//{
//   if (1 == mFrameCount) {
//      return;
//   }
//
//   if(mElapsedFrameTime >= mMsPerFrame)
//   {
//      const int adv_cnt = mElapsedFrameTime / mMsPerFrame;
//      mElapsedFrameTime -= (adv_cnt * mMsPerFrame);
//
//      int new_frame_index = mCurrentFrame + adv_cnt;
//
//      if(!mIsLooping && (new_frame_index >= mFrameCount))
//      {
//         new_frame_index = mFrameCount - 1;
//         SetAlive(false);
//      }
//
//      mCurrentFrame = new_frame_index % mFrameCount;
//   }
//}
//
//void Sprite::UpdatePosition()
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

//void Sprite::SetAnimation(const bool is_paused, const bool is_looping)
//{
//   mIsPaused = is_paused;
//   mIsLooping = is_looping;
//}
