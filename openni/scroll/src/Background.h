#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.h"

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

   void SetScreenResolution(int x_res, int y_res);

   void ScrollLeft(int speed);
   void ScrollRight(int speed);

private:
   int mXScreen;
   int mYScreen;

//   // In milliseconds - Determines the minimum scroll speed.
//   const int BACKGROUND_UPDATE_DELTA = 1000 / 60;
//
//   int mLastBgUpdateTime;
};

#endif // BACKGROUND_H
