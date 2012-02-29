#ifndef SCENE_OBJECT_H
#define SCENE_OBJECT_H

class SceneObject
{
public:
   SceneObject(int x_pos, int y_pos, float end_time);
   virtual ~SceneObject();

//   virtual SceneObject* Create() = 0;
//   virtual SceneObject* Clone() = 0;
//   virtual void Destroy();

   int GetXPos() const;
   int GetYPos() const;

   void SetXPos(int x_pos);
   void SetYPos(int y_pos);

   virtual bool IsDone() = 0;
   virtual void Update() = 0;
   virtual void Render() = 0;

protected:
   int mXPos;
   int mYPos;
   float mEndTime;
};

#endif // SCENE_OBJECT_H
