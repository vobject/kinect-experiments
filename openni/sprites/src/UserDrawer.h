#ifndef USER_DRAWER_H
#define USER_DRAWER_H

#include "Observer.h"
#include "KinectWrapper.h"

class SdlWindow;

enum UserPaintMode {
   upm_None,
   upm_LinesAndDots,
   upm_Color,
   upm_ColorAndLinesAndDots,
   upm_Real,
   upm_RealAndLinesAndDots,
   USER_PAINT_MODE_ITEM_COUNT
};

class UserDrawer : public Observer
{
public:
   UserDrawer(KinectWrapper* subject, const SdlWindow& wnd);
   virtual ~UserDrawer();

   virtual void Update(const Subject* updated_subject);

   UserPaintMode SwitchUserPaintMode();

private:
   void DrawLines(const UserData& user) const;
   void DrawDots(const UserData& user) const;
   void DrawPixels(const UserData& user) const;
   void DrawReal(const UserData& user) const;

   void DrawLine_ll(std::map<int, XnPoint3D>::const_iterator itA,
                    std::map<int, XnPoint3D>::const_iterator itB,
                    std::map<int, XnPoint3D>::const_iterator end) const;

   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;

   UserPaintMode mUserPaintMode;

   UserDrawer& operator=(const UserDrawer&);
};

#endif // USER_DRAWER_H
