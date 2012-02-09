#ifndef KINENOID_APP_H
#define KINENOID_APP_H

#include "KinectWrapper.h"

#include <string>

class KinectApp
{
public:
   explicit KinectApp(const std::string& path);
   ~KinectApp();

   void PrintCommands() const;
   void EventLoop();

private:
   const std::string mPath;

   KinectWrapper mKinect;

   // Stuff we do not need atm.
   KinectApp(const KinectApp&);
   KinectApp& operator=(const KinectApp&);
};

#endif // KINENOID_APP_H
