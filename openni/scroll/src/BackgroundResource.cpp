#include "BackgroundResource.h"

BackgroundResource::BackgroundResource()
{

}
BackgroundResource::BackgroundResource( const std::string& id, SDL_Surface* texture)
   : mId(id)
   , mFrame(texture)
{

}

BackgroundResource::~BackgroundResource()
{

}

std::string BackgroundResource::GetId() const
{
   return mId;
}

SDL_Surface* BackgroundResource::GetFrame() const
{
   return mFrame;
}

Size BackgroundResource::GetSize() const
{
   return {mFrame->w, mFrame->h};
}
