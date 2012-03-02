#ifndef EMPTY_BACKGROUND_H
#define EMPTY_BACKGROUND_H

#include "Background.h"

class EmptyBackground : public Background
{
public:
   EmptyBackground();
   virtual ~EmptyBackground();

   virtual void Update();
   virtual void Render();
};

#endif // EMPTY_BACKGROUND_H
