#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <string>

enum ZOrder
{
   zo_Background,
   zo_Layer_1,
   zo_Layer_2,
   zo_Layer_3,
   zo_Messagebox
};

class SceneObject
{
public:
   SceneObject();
   virtual ~SceneObject();

   virtual bool operator<(const SceneObject& other);

   virtual void Update(int elapsed_time) = 0;
//   virtual void Restore() = 0;

   std::string GetResourceId() const;
   void SetResourceId(const std::string& resource);

   int GetXPos() const;
   int GetYPos() const;
   void SetPos(int x_pos, int y_pos);

   int GetWidth() const;
   int GetHeight() const;
   void SetSize(int width, int height);

   ZOrder GetZOrder() const;
   void SetZOrder(ZOrder order);

   bool IsVisible() const;
   void SetVisible(bool visible);

//   virtual SceneObject* Create() = 0;
//   virtual SceneObject* Clone() = 0;
//   virtual void Destroy();

private:
   std::string mResource;
   int mXPos;
   int mYPos;
   int mWidth;
   int mHeight;
   ZOrder mZOrder;
   bool mIsVisible;
};

#endif // SCENE_OBJECT_H
