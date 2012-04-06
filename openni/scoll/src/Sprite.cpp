#include "Sprite.h"

Sprite::Sprite()
   : mIsPaused(false)
   , mIsLooping(false)
   , mMsPerFrame(100)
   , mMsPerPosUpdate(100)
   , mElapsedFrameTime(0)
   , mElapsedPosTime(0)
   , mFrameCount(1)
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

void Sprite::SetFrameCount(const int frame_cnt)
{
   mFrameCount = frame_cnt;
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

void Sprite::UpdateFrame()
{
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
