#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.h"

class Background : public SceneObject
{
public:
   Background();
   virtual ~Background();

   virtual void Update(int elapsed_time);

   void SetScreenSize(int x_res, int y_res);

   void ScrollLeft(int speed);
   void ScrollRight(int speed);

private:
   int mXScreen;
   int mYScreen;

   Background(const Background&);
   const Background& operator=(const Background&);
};

#endif // BACKGROUND_H
