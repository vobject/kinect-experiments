#include "Texture.h"

Texture::Texture(SDL_Surface* surface)
   : mSurface(surface)
{

}

Texture::~Texture()
{
   SDL_FreeSurface(mSurface);
}

void Texture::Blit(const Texture& tex, const Rect& rect)
{
   SDL_Rect dest_rect = { (Sint16)rect.X,
                          (Sint16)rect.Y,
                          (Uint16)rect.Width,
                          (Uint16)rect.Height };
   const auto src = (SDL_Surface*)tex.GetData();

   SDL_BlitSurface(src, NULL, mSurface, &dest_rect);
}

void* Texture::GetData() const
{
   return mSurface;
}

Size Texture::GetSize() const
{
   return { mSurface->w, mSurface->h };
}
