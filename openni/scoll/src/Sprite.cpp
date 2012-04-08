#include "Sprite.h"

Sprite::Sprite(int frame_cnt /*=1*/, int ms_per_frame /*=100*/, int ms_per_pos /*=100*/, bool looping /*=false*/)
   : mIsPaused(false)
   , mIsLooping(looping)
   , mMsPerFrame(ms_per_frame)
   , mMsPerPosUpdate(ms_per_pos)
   , mElapsedFrameTime(0)
   , mElapsedPosTime(0)
   , mFrameCount(frame_cnt)
   , mCurrentFrameIndex(0)
   , mXDirection(0)
   , mYDirection(0)
   , mXSpeed(0)
   , mYSpeed(0)
{

}

Sprite::~Sprite()
{

}

void Sprite::Update(const int elapsed_time)
{
   if (mIsPaused) {
      return;
   }

   mElapsedFrameTime += elapsed_time;
   mElapsedPosTime += elapsed_time;

   UpdateFrame();
   UpdatePosition();
}

void Sprite::SetDirection(const int x_dir, const int y_dir)
{
   mXDirection = x_dir;
   mYDirection = y_dir;
}

void Sprite::SetSpeed(const int x_speed, const int y_speed)
{
   mXSpeed = x_speed;
   mYSpeed = y_speed;
}

int Sprite::GetCurrentFrame() const
{
   return mCurrentFrameIndex;
}

void Sprite::UpdateFrame()
{
   if (1 == mFrameCount) {
      return;
   }

   if(mElapsedFrameTime >= mMsPerFrame)
   {
      const int adv_cnt = mElapsedFrameTime / mMsPerFrame;
      mElapsedFrameTime -= (adv_cnt * mMsPerFrame);

      int new_frame_index = mCurrentFrameIndex + adv_cnt;

      if(!mIsLooping && (new_frame_index >= mFrameCount))
      {
         new_frame_index = mFrameCount - 1;
      }

      mCurrentFrameIndex = new_frame_index % mFrameCount;
   }
}

void Sprite::UpdatePosition()
{
   if(mElapsedPosTime >= mMsPerPosUpdate)
   {
      const int adv_cnt = mElapsedPosTime / mMsPerPosUpdate;
      mElapsedPosTime -= (adv_cnt * mMsPerPosUpdate);

      SetPos(GetXPos() + (mXDirection * mXSpeed * adv_cnt),
             GetYPos() + (mYDirection * mYSpeed * adv_cnt));
   }
}

//void Sprite::Restore()
//{
//
//}

//void Sprite::SetAnimation(const bool is_paused, const bool is_looping)
//{
//   mIsPaused = is_paused;
//   mIsLooping = is_looping;
//}
