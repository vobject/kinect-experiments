#include "DirectedSpriteResource.hpp"

#include <SDL.h>

DirectedSpriteResource::DirectedSpriteResource()
{

}

DirectedSpriteResource::DirectedSpriteResource(
   const std::string& id,
   const std::vector<SDL_Surface*>& textures_up,
   const std::vector<SDL_Surface*>& textures_down,
   const std::vector<SDL_Surface*>& textures_left,
   const std::vector<SDL_Surface*>& textures_right
)
   : mId(id)
   , mFramesUp(textures_up)
   , mFramesDown(textures_down)
   , mFramesLeft(textures_left)
   , mFramesRight(textures_right)
{

}

DirectedSpriteResource::~DirectedSpriteResource()
{

}

std::string DirectedSpriteResource::GetId() const
{
   return mId;
}

int DirectedSpriteResource::GetFrameCount(const Direction dir) const
{
   switch (dir)
   {
      case Direction::Up:
         return mFramesUp.size();
      case Direction::Down:
         return mFramesDown.size();
      case Direction::Left:
         return mFramesLeft.size();
      case Direction::Right:
         return mFramesRight.size();
   }
   return 0;
}

SDL_Surface* DirectedSpriteResource::GetFrame(const Direction dir, const int n) const
{
   switch (dir)
   {
      case Direction::Up:
         return mFramesUp.at(n);
      case Direction::Down:
         return mFramesDown.at(n);
      case Direction::Left:
         return mFramesLeft.at(n);
      case Direction::Right:
         return mFramesRight.at(n);
   }
   return nullptr;
}

Size DirectedSpriteResource::GetSize(const Direction dir) const
{
   switch (dir)
   {
      case Direction::Up:
         return { mFramesUp.at(0)->w, mFramesUp.at(0)->h };
      case Direction::Down:
         return { mFramesDown.at(0)->w, mFramesDown.at(0)->h };
      case Direction::Left:
         return { mFramesLeft.at(0)->w, mFramesLeft.at(0)->h };
      case Direction::Right:
         return { mFramesRight.at(0)->w, mFramesRight.at(0)->h };
   }
   return { 0, 0 };
}
