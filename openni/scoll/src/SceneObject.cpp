#include "SceneObject.h"

SceneObject::SceneObject()
   : mXPos(0)
   , mYPos(0)
   , mWidth(0)
   , mHeight(0)
   , mZOrder(0)
   , mIsVisible(true)
{

}

SceneObject::~SceneObject()
{

}

bool SceneObject::operator<(const SceneObject& other)
{
   return GetZOrder() < other.GetZOrder();
}

std::string SceneObject::GetResourceId() const
{
   return mResource;
}

void SceneObject::SetResourceId(const std::string& resource)
{
   mResource = resource;
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

int SceneObject::GetZOrder() const
{
   return mZOrder;
}

void SceneObject::SetZOrder(const int order)
{
   mZOrder = order;
}

bool SceneObject::IsVisible() const
{
   return mIsVisible;
}

void SceneObject::SetVisible(const bool visible)
{
   mIsVisible = visible;
}
