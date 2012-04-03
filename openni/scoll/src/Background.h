#ifndef BACKGROUND_H
#define BACKGROUND_H

#include "SceneObject.h"

class Background : public SceneObject
{
public:
   Background();
   virtual ~Background();

   virtual void Update(int elapsed_time);

private:
   Background(const Background&);
   const Background& operator=(const Background&);
};

#endif // BACKGROUND_H
