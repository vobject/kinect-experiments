#include "Sprite.h"

Sprite::Sprite()
   : mIsPaused(false)
   , mIsLooping(false)
   , mMsPerFrame(100)
   , mElapsedTime(0)
   , mFrameCount(1)
   , mCurrentFrameIndex(0)
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

   mElapsedTime += elapsed_time;

   if (mElapsedTime >= mMsPerFrame)
   {
      const int advance_count = mElapsedTime / mMsPerFrame;
      mElapsedTime -= (advance_count * mMsPerFrame);

      int new_frame_index = mCurrentFrameIndex + advance_count;

      if (!mIsLooping && (new_frame_index >= mFrameCount)) {
         new_frame_index = mFrameCount - 1;
      }

      mCurrentFrameIndex = new_frame_index % mFrameCount;
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
