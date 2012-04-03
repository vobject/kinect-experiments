#ifndef SPRITE_H
#define SPRITE_H

#include "SceneObject.h"

class Sprite : public SceneObject
{
public:
   Sprite();
   virtual ~Sprite();

   virtual void Update(int elapsed_time);

   void SetFrameCount(int frame_cnt);
//   virtual void Restore();

//   void SetAnimation(bool is_paused, bool is_looping);

private:
   bool mIsPaused;
   bool mIsLooping;
   int mMsPerFrame;
   int mElapsedTime;
   int mFrameCount;
   int mCurrentFrameIndex;

   Sprite(const Sprite&);
   const Sprite& operator=(const Sprite&);
};

#endif // SPRITE_H
