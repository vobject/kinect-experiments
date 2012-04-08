#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

#include <string>

enum class ZOrder
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

   int GetXPos() const;
   int GetYPos() const;
   void SetPos(int x_pos, int y_pos);

   int GetXRes() const;
   int GetYRes() const;
   void SetSize(int x_res, int y_res);

   ZOrder GetZOrder() const;
   void SetZOrder(ZOrder order);

   bool IsVisible() const;
   void SetVisible(bool visible);

   bool IsAlive() const;
   void SetAlive(bool alive);

//   virtual SceneObject* Create() = 0;
//   virtual SceneObject* Clone() = 0;
//   virtual void Destroy();

protected:
   void SetResourceId(const std::string& resource);

private:
   std::string mResource;
   int mXPos;
   int mYPos;
   int mWidth;
   int mHeight;
   ZOrder mZOrder;
   bool mIsVisible;
   bool mIsAlive;
};

#endif // SCENE_OBJECT_H
