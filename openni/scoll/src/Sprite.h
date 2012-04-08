#ifndef SPRITE_H
#define SPRITE_H

#include "SceneObject.h"

#include <SDL.h>

#include <string>
#include <vector>

class Sprite : public SceneObject
{
public:
   Sprite(const std::string& id,
           const std::vector<SDL_Surface*>& frames = std::vector<SDL_Surface*>(),
           bool looping = false);
   virtual ~Sprite();

   virtual void Update(int elapsed_time);

   void SetMsPerFrame(int ms);
   void SetMsPerPosition(int ms);
   void SetDirection(int x_dir, int y_dir);
   void SetSpeed(int x_speed, int y_speed);

   SDL_Surface* GetCurrentFrame() const;

private:
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

   // TODO: Replace this with a shared_ptr<vector<Frame>>?
   const std::vector<SDL_Surface*> mFrames;

   Sprite(const Sprite&);
   const Sprite& operator=(const Sprite&);
};

#endif // SPRITE_H
