#include "Background.h"

Background::Background()
{
   SetResourceId("smw");
   SetPos(0, 0);
   SetSize(640, 480);
   SetZOrder(zo_Background);
   SetVisible(true);
}

Background::~Background()
{

}

void Background::Update(const int elapsed_time)
{

}
