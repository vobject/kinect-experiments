#ifndef SPRITE_H
#define SPRITE_H

#include "SceneObject.h"

class Sprite : public SceneObject
{
public:
   Sprite(int frame_cnt = 1, int ms_per_frame = 0, int ms_per_pos = 33, bool looping = false);
   virtual ~Sprite();

   virtual void Update(int elapsed_time);

   void SetDirection(int x_dir, int y_dir);
   void SetSpeed(int x_speed, int y_speed);

   int GetCurrentFrame() const;

private:
   void UpdateFrame();
   void UpdatePosition();

   bool mIsPaused;
   bool mIsLooping;
   int mMsPerFrame;
   int mMsPerPosUpdate;
   int mElapsedFrameTime;
   int mElapsedPosTime;
   int mFrameCount;
   int mCurrentFrameIndex;

   int mXDirection;
   int mYDirection;
   int mXSpeed;
   int mYSpeed;

   Sprite(const Sprite&);
   const Sprite& operator=(const Sprite&);
};

#endif // SPRITE_H
