#ifndef BACKGROUNDRESOURCE_H
#define BACKGROUNDRESOURCE_H

#include "Texture.h"
#include "Utils.hpp"

#include <SDL.h>

#include <memory>
#include <string>

class BackgroundResource
{
public:
   BackgroundResource();
   BackgroundResource(const std::string& id, const std::shared_ptr<Texture>& texture);
   ~BackgroundResource();

   BackgroundResource(const BackgroundResource&) = default;
   BackgroundResource& operator=(const BackgroundResource&) = default;

   std::string GetId() const;
   std::shared_ptr<Texture> GetFrame() const;
   Size GetSize() const;

private:
   std::string mId;
   std::shared_ptr<Texture> mFrame;
};

#endif // BACKGROUNDRESOURCE_H
