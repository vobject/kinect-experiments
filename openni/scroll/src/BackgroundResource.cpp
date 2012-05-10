#include "BackgroundResource.h"

BackgroundResource::BackgroundResource()
{

}

BackgroundResource::BackgroundResource(
   const std::string& id,
   const std::shared_ptr<Texture>& texture
)
   : mId(id),
     mFrame(texture)
{

}

BackgroundResource::~BackgroundResource()
{

}

std::string BackgroundResource::GetId() const
{
   return mId;
}

std::shared_ptr<Texture> BackgroundResource::GetFrame() const
{
   return mFrame;
}

Size BackgroundResource::GetSize() const
{
   return mFrame->GetSize();
}
