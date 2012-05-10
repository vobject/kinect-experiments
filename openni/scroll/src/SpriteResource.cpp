#include "SpriteResource.h"

SpriteResource::SpriteResource()
{

}

SpriteResource::SpriteResource(
   const std::string& id,
   const std::vector<std::shared_ptr<Texture>>& textures
)
   : mId(id),
     mFrames(textures)
{

}

SpriteResource::~SpriteResource()
{

}

std::string SpriteResource::GetId() const
{
   return mId;
}

int SpriteResource::GetFrameCount() const
{
   return mFrames.size();
}

std::shared_ptr<Texture> SpriteResource::GetFrame(int n) const
{
   return mFrames.at(n);
}

Size SpriteResource::GetSize() const
{
   if (mFrames.empty()) {
      throw "No frames associated with the current sprite";
   }
   return mFrames.at(0)->GetSize();
}
