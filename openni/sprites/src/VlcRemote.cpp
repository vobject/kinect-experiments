#include "VlcRemote.h"
#include "SdlWindow.h"

VlcRemote::VlcRemote(KinectWrapper* subject,
                     const SdlWindow& wnd,
                     const VlcPlayer& vlc)
   : mSubject(subject)
   , mWindow(wnd)
   , mVlc(vlc)
{
   mSubject->Subscribe(this);
}

VlcRemote::~VlcRemote()
{
   if (mSubject) {
      mSubject->Unsubscribe(this);
   }
}

void VlcRemote::Update( const Subject* updated_subject )
{
   if (updated_subject != mSubject) {
      // This is not the subject that we registered to.
      throw "Invalid subject.";
   }

   std::vector<UserData> users;
   mSubject->GetUsers(users);

   if (users.empty())
   {
      return;
   }

   std::map<int, XnPoint3D> joints = users[0].GetRealWorldJoints();

   const XnPoint3D head = mSubject->RealWorldToProjective(joints[XN_SKEL_HEAD]);
   const XnPoint3D leftHand = mSubject->RealWorldToProjective(joints[XN_SKEL_LEFT_HAND]);
   const XnPoint3D rightHand = mSubject->RealWorldToProjective(joints[XN_SKEL_RIGHT_HAND]);
   const XnPoint3D leftShoulder = mSubject->RealWorldToProjective(joints[XN_SKEL_LEFT_SHOULDER]);
   const XnPoint3D rightShoulder = mSubject->RealWorldToProjective(joints[XN_SKEL_RIGHT_SHOULDER]);

   // Play
   if ((rightHand.Y + 20) < head.Y)
   {
      mVlc.Play();
      return;
   }

   // Pause
   if ((leftHand.Y + 20) < head.Y)
   {
      mVlc.Pause();
      return;
   }

   // Seek forward
   if ((leftHand.X - 40) > rightShoulder.X)
   {
      mVlc.SeekForward();
      return;
   }

   // Seek backward
   if ((rightHand.X + 40) < leftShoulder.X)
   {
      mVlc.SeekBackward();
      return;
   }
}
