#ifndef SPRITE_HPP
#define SPRITE_HPP

#include "SceneObject.hpp"

#include <SDL.h>

#include <string>
#include <vector>

class SpriteResource;

class Sprite : public SceneObject
{
public:
   Sprite(const SpriteResource& res, bool looping = false);
   virtual ~Sprite();

   Sprite(const Sprite&) = delete;
   Sprite& operator=(const Sprite&) = delete;

   void Update(int elapsed_time) override;

   void SetMsPerFrame(int ms);
   void SetMsPerPosition(int ms);
   void SetDirection(int x_dir, int y_dir);
   void SetSpeed(int x_speed, int y_speed);

   int GetCurrentFrame() const;

protected:
   void UpdateFrame();
   void UpdatePosition();

//   bool mIsPaused;
   bool mIsLooping;
   int mMsPerFrame;
   int mMsPerPosUpdate;

   int mElapsedFrameTime;
   int mElapsedPosTime;
   int mFrameCount;
   int mCurrentFrame;

   int mXDirection;
   int mYDirection;
   int mXSpeed;
   int mYSpeed;
};

#endif // SPRITE_HPP
