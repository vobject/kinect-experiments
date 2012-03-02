#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

class SceneObject
{
public:
   SceneObject();
   virtual ~SceneObject();

//   virtual SceneObject* Create() = 0;
//   virtual SceneObject* Clone() = 0;
//   virtual void Destroy();

   virtual bool IsAlive() = 0;
   virtual void Update() = 0;
   virtual void Render() = 0;

   int GetXPos() const;
   int GetYPos() const;
   void SetPos(int x_pos, int y_pos);

   int GetWidth() const;
   int GetHeight() const;
   void SetSize(int width, int height);

private:
   int mXPos;
   int mYPos;
   int mWidth;
   int mHeight;
};

#endif // SCENE_OBJECT_H
