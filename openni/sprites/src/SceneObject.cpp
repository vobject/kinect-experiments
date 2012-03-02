#include "SceneObject.h"

SceneObject::SceneObject()
   : mXPos(0)
   , mYPos(0)
   , mWidth(0)
   , mHeight(0)
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

void SceneObject::SetPos(const int x_pos, const int y_pos)
{
   mXPos = x_pos;
   mYPos = y_pos;
}

int SceneObject::GetWidth() const
{
   return mWidth;
}

int SceneObject::GetHeight() const
{
   return mHeight;
}

void SceneObject::SetSize(const int width, const int height)
{
   mWidth = width;
   mHeight = height;
}
