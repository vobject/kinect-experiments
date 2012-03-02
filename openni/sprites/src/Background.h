#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.h"

class Background : public SceneObject
{
public:
   Background();
   virtual ~Background();

   virtual bool IsAlive();
};

#endif // BACKGROUND_H
