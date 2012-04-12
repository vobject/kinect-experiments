#include "Sprite.h"

Sprite::Sprite(
   const std::string& id,
   const std::vector<SDL_Surface*>& frames /*=std::vector<SDL_Surface*>()*/,
   const bool looping /*=false*/
)
   : mIsLooping(looping)
   , mMsPerFrame(60)
   , mMsPerPosUpdate(30)
   , mElapsedFrameTime(0)
   , mElapsedPosTime(0)
   , mFrameCount(frames.size() ? frames.size() : 1)
   , mCurrentFrame(0)
   , mXDirection(0)
   , mYDirection(0)
   , mXSpeed(0)
   , mYSpeed(0)
   , mFrames(frames)
{
   SetResourceId(id);
}

Sprite::~Sprite()
{

}

void Sprite::Update(const int elapsed_time)
{
//   if (mIsPaused) {
//      return;
//   }

   mElapsedFrameTime += elapsed_time;
   mElapsedPosTime += elapsed_time;

   UpdateFrame();
   UpdatePosition();
}

void Sprite::SetMsPerFrame(const int ms)
{
   mMsPerFrame = ms;
}

void Sprite::SetMsPerPosition(const int ms)
{
   mMsPerPosUpdate = ms;
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

SDL_Surface* Sprite::GetCurrentFrame() const
{
   return mFrames.at(mCurrentFrame);
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

      int new_frame_index = mCurrentFrame + adv_cnt;

      if(!mIsLooping && (new_frame_index >= mFrameCount))
      {
         new_frame_index = mFrameCount - 1;
         SetAlive(false);
      }

      mCurrentFrame = new_frame_index % mFrameCount;
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

//void Sprite::SetAnimation(const bool is_paused, const bool is_looping)
//{
//   mIsPaused = is_paused;
//   mIsLooping = is_looping;
//}
