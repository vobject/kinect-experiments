#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.h"

#include <SDL.h>

#include <string>

class Background : public SceneObject
{
public:
   Background(const std::string& id, SDL_Surface* frame);
   virtual ~Background();

   virtual void Update(int elapsed_time);

   void SetScreenSize(int x_res, int y_res);

   void ScrollLeft(int speed);
   void ScrollRight(int speed);

   SDL_Surface* GetFrame() const;

private:
   int mXScreen;
   int mYScreen;
   SDL_Surface* mFrame;

   Background(const Background&);
   const Background& operator=(const Background&);
};

#endif // BACKGROUND_H
