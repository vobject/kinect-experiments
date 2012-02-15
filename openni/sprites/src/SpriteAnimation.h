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
   SpriteAnimation();
   ~SpriteAnimation();

   void SetFrameCycle(int ms);
   void AddFrame(const std::string& file);
   void RenderFrame(const SdlWindow& wnd, SDL_Rect* const dest);
   void NextFrame();

private:
   std::vector<SDL_Surface*> mFrames;
   size_t mCurrentFrame;
   int mFrameCycle;
};

#endif // SPRITE_ANIMATION_H
