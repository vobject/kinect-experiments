#ifndef SPRITE_DRAWER_H
#define SPRITE_DRAWER_H

#include "Observer.h"
#include "KinectWrapper.h"
#include "SpriteAnimation.h"

#include <SDL.h>

class SdlWindow;

class SpriteDrawer : public Observer
{
public:
   SpriteDrawer(KinectWrapper* subject, const SdlWindow& wnd);
   virtual ~SpriteDrawer();

   virtual void Update(const Subject* updated_subject);

private:
   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;

   SpriteAnimation mBloodA;
   SpriteAnimation mBloodD;

   SpriteDrawer& operator=(const SpriteDrawer&);
};

#endif // SPRITE_DRAWER_H
