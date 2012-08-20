#ifndef ANIMATION_HPP
#define ANIMATION_HPP

#include "../utils/Utils.hpp"

class Animation
{
public:
   Animation();
   ~Animation();

   Animation(const Animation&) = delete;
   Animation& operator=(const Animation&) = delete;

   void SetFrameCount(int n);
   void SetLength(int milliseconds);
   void SetLooping(bool endless_loop);

   void Update(int elapsed_time);
   int GetCurrentFrame() const;

private:
   int mFrameCount = 0;
   int mLength = 1000_ms;
   bool mLooping = false;
   int mElapsedTime = 0;
};

#endif // ANIMATION_HPP
