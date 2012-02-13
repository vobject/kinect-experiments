#include "UserDrawer.h"
#include "SdlWindow.h"
#include "UserData.h"

UserDrawer::UserDrawer(KinectWrapper* subject, const SdlWindow& wnd)
   : mSubject(subject)
   , mWindow(wnd)
   , mUserPaintMode(upm_LinesAndDots)
{
   mSubject->Subscribe(this);
}

UserDrawer::~UserDrawer()
{
   if (mSubject) {
      mSubject->Unsubscribe(this);
   }
}

void UserDrawer::Update( const Subject* updated_subject )
{
   if (updated_subject != mSubject) {
      // This is not the subject that we registered to.
      throw "Invalid subject.";
   }

   std::vector<UserData> users;
   mSubject->GetUsers(users);

   for (std::vector<UserData>::const_iterator user_iter = users.begin();
        user_iter != users.end();
        user_iter++)
   {
      switch (mUserPaintMode)
      {
      case upm_LinesAndDots:
         DrawLines(*user_iter);
         DrawDots(*user_iter);
         break;
      case upm_Color:
         DrawPixels(*user_iter);
         break;
      case upm_ColorAndLinesAndDots:
         DrawPixels(*user_iter);
         DrawLines(*user_iter);
         DrawDots(*user_iter);
         break;
      case upm_Real:
         DrawReal(*user_iter);
         break;
      case upm_RealAndLinesAndDots:
         DrawReal(*user_iter);
         DrawLines(*user_iter);
         DrawDots(*user_iter);
         break;
      }
   }
}

UserPaintMode UserDrawer::SwitchUserPaintMode()
{
   mUserPaintMode = (UserPaintMode)((mUserPaintMode + 1) % USER_PAINT_MODE_ITEM_COUNT);
   return mUserPaintMode;
}

void UserDrawer::DrawLines( const UserData& user ) const
{
   std::map<int, XnPoint3D> joints = user.GetRealWorldJoints();
   
   std::map<int, XnPoint3D>::const_iterator itA;
   std::map<int, XnPoint3D>::const_iterator itB;

   itA = joints.find(XN_SKEL_HEAD);
   itB = joints.find(XN_SKEL_NECK);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_NECK);
   itB = joints.find(XN_SKEL_TORSO);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_NECK);
   itB = joints.find(XN_SKEL_LEFT_SHOULDER);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_LEFT_SHOULDER);
   itB = joints.find(XN_SKEL_LEFT_ELBOW);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_LEFT_ELBOW);
   itB = joints.find(XN_SKEL_LEFT_HAND);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_NECK);
   itB = joints.find(XN_SKEL_TORSO);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_NECK);
   itB = joints.find(XN_SKEL_LEFT_SHOULDER);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_NECK);
   itB = joints.find(XN_SKEL_RIGHT_SHOULDER);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_RIGHT_SHOULDER);
   itB = joints.find(XN_SKEL_RIGHT_ELBOW);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_RIGHT_ELBOW);
   itB = joints.find(XN_SKEL_RIGHT_HAND);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_TORSO);
   itB = joints.find(XN_SKEL_LEFT_HIP);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_TORSO);
   itB = joints.find(XN_SKEL_RIGHT_HIP);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_LEFT_HIP);
   itB = joints.find(XN_SKEL_LEFT_KNEE);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_LEFT_KNEE);
   itB = joints.find(XN_SKEL_LEFT_FOOT);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_RIGHT_HIP);
   itB = joints.find(XN_SKEL_RIGHT_KNEE);
   DrawLine_ll(itA, itB, joints.end());

   itA = joints.find(XN_SKEL_RIGHT_KNEE);
   itB = joints.find(XN_SKEL_RIGHT_FOOT);
   DrawLine_ll(itA, itB, joints.end());
}

void UserDrawer::DrawDots(const UserData& user) const
{
   const std::map<int, XnPoint3D> joints = user.GetRealWorldJoints();

   for (std::map<int, XnPoint3D>::const_iterator joint_iter = joints.begin();
        joint_iter != joints.end();
        ++joint_iter)
   {
      const XnPoint3D joint_proj = mSubject->RealWorldToProjective(joint_iter->second);
      mWindow.DrawRect(static_cast<Sint16>(joint_proj.X),
                       static_cast<Sint16>(joint_proj.Y),
                       6);
   }
}

void UserDrawer::DrawPixels(const UserData& user) const
{
   std::vector<bool>::const_iterator begin;
   std::vector<bool>::const_iterator end;
   user.GetPixelIterator(begin, end);

   SdlSurface surface = mWindow.GetSurface();
   XnRGB24Pixel* screen_buf = (XnRGB24Pixel*)surface->pixels;

   for (std::vector<bool>::const_iterator pix_iter = begin;
        pix_iter != end;
        ++pix_iter, ++screen_buf)
   {
      if (*pix_iter)
      {
         screen_buf->nRed = 0xff;
         screen_buf->nGreen = 0;
         screen_buf->nBlue = 0;
      }
   }
}

void UserDrawer::DrawReal(const UserData& user) const
{
   std::vector<bool>::const_iterator begin;
   std::vector<bool>::const_iterator end;
   user.GetPixelIterator(begin, end);

   SdlSurface surface = mWindow.GetSurface();
   XnRGB24Pixel* screen_buf = (XnRGB24Pixel*)surface->pixels;
   const XnRGB24Pixel* rgb_buf = mSubject->GetImageData();

   for (std::vector<bool>::const_iterator pix_iter = begin;
        pix_iter != end;
        ++pix_iter, ++screen_buf, ++rgb_buf)
   {
      if (*pix_iter)
      {
         screen_buf->nRed = (rgb_buf + 0)->nBlue;
         screen_buf->nGreen = (rgb_buf + 0)->nGreen;
         screen_buf->nBlue = (rgb_buf + 0)->nRed;
      }
   }
}

void UserDrawer::DrawLine_ll(
   std::map<int, XnPoint3D>::const_iterator itA,
   std::map<int, XnPoint3D>::const_iterator itB,
   std::map<int, XnPoint3D>::const_iterator end
   ) const
{
   if ((itA != end) && (itB != end))
   {
      mWindow.DrawLine(mSubject->RealWorldToProjective(itA->second).X,
         mSubject->RealWorldToProjective(itA->second).Y,
         mSubject->RealWorldToProjective(itB->second).X,
         mSubject->RealWorldToProjective(itB->second).Y);
   }
}
