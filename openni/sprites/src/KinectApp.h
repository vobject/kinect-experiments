#ifndef KINENOID_APP_H
#define KINENOID_APP_H

#include "KinectWrapper.h"

#include <string>

class KinectApp
{
public:
   explicit KinectApp(const std::string& path);
   virtual ~KinectApp();

   void PrintCommands() const;
   void Mainloop();

protected:
//   virtual void Init();
//   virtual void ProcessInput();
//   virtual void RenderScene();

private:
   const std::string mPath;

   bool mMainloopDone;
   KinectWrapper mKinect;

   KinectApp(const KinectApp&);
   KinectApp& operator=(const KinectApp&);
};

#endif // KINENOID_APP_H
