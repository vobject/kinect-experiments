#include "SceneObject.h"

SceneObject::SceneObject()
   : mXPos(0)
   , mYPos(0)
   , mWidth(0)
   , mHeight(0)
   , mZOrder(ZOrder::zo_Layer_1)
   , mIsVisible(true)
   , mIsAlive(true)
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

int SceneObject::GetXRes() const
{
   return mWidth;
}

int SceneObject::GetYRes() const
{
   return mHeight;
}

void SceneObject::SetSize(const int width, const int height)
{
   mWidth = width;
   mHeight = height;
}

ZOrder SceneObject::GetZOrder() const
{
   return mZOrder;
}

void SceneObject::SetZOrder(const ZOrder order)
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

bool SceneObject::IsAlive() const
{
   return mIsAlive;
}

void SceneObject::SetAlive(const bool alive)
{
   mIsAlive = alive;
}
