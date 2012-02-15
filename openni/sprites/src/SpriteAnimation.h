#ifndef SPRITE_ANIMATION_H
#define SPRITE_ANIMATION_H

#include <string>
#include <vector>

class SDL_Rect;
class SDL_Surface;
class SdlWindow;

class SpriteAnimation
{
public:
   static const int DEFAULT_UDATE_RATE = 1000 / 60;

   SpriteAnimation();
   ~SpriteAnimation();

   void AddFrame(const std::string& file);

   void Init(int update_rate = DEFAULT_UDATE_RATE);
   bool IsPlaying() const;
   void Stop();
   void RenderFrame(const SdlWindow& wnd, SDL_Rect* const dest);

private:
   void NextFrame();

   std::vector<SDL_Surface*> mFrames;
   size_t mCurrentFrame;

   int mUpdateRate;
   int mLastFrameTime;
};

#endif // SPRITE_ANIMATION_H
