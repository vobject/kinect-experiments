#ifndef BACKGROUNDRESOURCE_H
#define BACKGROUNDRESOURCE_H

#include "Utils.hpp"

#include <SDL.h>

#include <string>

class BackgroundResource
{
public:
   BackgroundResource();
   BackgroundResource(const std::string& id, SDL_Surface* texture);
   ~BackgroundResource();

   BackgroundResource(const BackgroundResource&) = default;
   BackgroundResource& operator=(const BackgroundResource&) = default;

   std::string GetId() const;
   SDL_Surface* GetFrame() const;
   Size GetSize() const;

private:
   std::string mId;
   SDL_Surface* mFrame;
};

#endif // BACKGROUNDRESOURCE_H
