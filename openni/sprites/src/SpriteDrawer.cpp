#include "SpriteDrawer.h"
#include "SdlWindow.h"

#include <XnTypes.h>

#include <cstdlib>

SpriteDrawer::SpriteDrawer(KinectWrapper* subject, const SdlWindow& wnd)
   : mSubject(subject)
   , mWindow(wnd)
{
   mSubject->Subscribe(this);

   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0001.png");
   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0002.png");
   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0003.png");
   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0004.png");
   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0005.png");
   mBloodA.AddFrame("../../../../external/blood_pack_1/blood_a/blood_a_0006.png");
   mBloodA.Init(60);

   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0001.png");
   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0002.png");
   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0003.png");
   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0004.png");
   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0005.png");
   mBloodD.AddFrame("../../../../external/blood_pack_1/blood_d/blood_d_0006.png");
   mBloodD.Init(60);
}

SpriteDrawer::~SpriteDrawer()
{
   if (mSubject) {
      mSubject->Unsubscribe(this);
   }
}

void SpriteDrawer::Update( const Subject* updated_subject )
{
   if (updated_subject != mSubject) {
      // This is not the subject that we registered to.
      throw "Invalid subject.";
   }

   std::vector<UserData> users;
   mSubject->GetUsers(users);

   if (users.empty()) {
      return;
   }

   const XnPoint3D head_pos = mSubject->RealWorldToProjective(users.at(0).GetRealWorldJoints()[XN_SKEL_HEAD]);
   const XnPoint3D rhand_pos = mSubject->RealWorldToProjective(users.at(0).GetRealWorldJoints()[XN_SKEL_RIGHT_HAND]);
   const XnPoint3D lhand_pos = mSubject->RealWorldToProjective(users.at(0).GetRealWorldJoints()[XN_SKEL_LEFT_HAND]);

   SDL_Rect dest_rect = { head_pos.X, head_pos.Y, 10, 10 };

   if ((abs(head_pos.X - lhand_pos.X) < 50) && (abs(head_pos.Y - lhand_pos.Y) < 50))
   {
      mBloodA.RenderFrame(mWindow, &dest_rect);
   }
   else
   {
      mBloodA.Init(60);
   }

   if ((abs(head_pos.X - rhand_pos.X) < 50) && (abs(head_pos.Y - rhand_pos.Y) < 50))
   {
      mBloodD.RenderFrame(mWindow, &dest_rect);
   }
   else
   {
      mBloodD.Init(60);
   }
}
