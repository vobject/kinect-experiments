#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.hpp"

#include <SDL.h>

#include <string>

class BackgroundResource;

class Background : public SceneObject
{
public:
   Background(const BackgroundResource& res);
   virtual ~Background();

   Background(const Background&) = delete;
   Background& operator=(const Background&) = delete;

   void Update(int elapsed_time) override;

   void ScrollLeft(int speed);
   void ScrollRight(int speed);

private:
   int mXScreen;
   int mYScreen;

   // The maximum scroll speed -> how long to wait for one scroll operation.
   const int MILLISECONDS_PER_SCROLL = 10_ms; // Move this into BackgroundResource
   //   const int BACKGROUND_UPDATE_DELTA = 1000 / 60;
//
   int mElapsedTimeSinceLastScroll = 0_ms;
};

#endif // BACKGROUND_H
