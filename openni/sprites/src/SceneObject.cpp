#include "SceneObject.h"

SceneObject::SceneObject(int x_pos, int y_pos, float end_time)
   : mXPos(x_pos)
   , mYPos(y_pos)
   , mEndTime(end_time)
{

}

SceneObject::~SceneObject()
{

}

int SceneObject::GetXPos() const
{
   return mXPos;
}

int SceneObject::GetYPos() const
{
   return mYPos;
}

void SceneObject::SetXPos(int x_pos)
{
   mXPos = x_pos;
}

void SceneObject::SetYPos(int y_pos)
{
   mYPos = y_pos;
}
