#ifndef VLC_REMOTE_H
#define VLC_REMOTE_H

#include "Observer.h"
#include "KinectWrapper.h"
#include "VlcPlayer.h"

class SdlWindow;

class VlcRemote : public Observer
{
public:
   VlcRemote(KinectWrapper* subject, const SdlWindow& wnd, const VlcPlayer& vlc);
   virtual ~VlcRemote();

   virtual void Update(const Subject* updated_subject);

private:
   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;
   const VlcPlayer& mVlc;

   VlcRemote& operator=(const VlcRemote&);
};

#endif // VLC_REMOTE_H
