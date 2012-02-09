#include "VlcPlayer.h"
#include "SdlWindow.h"

namespace kinectlib {

VlcPlayer::VlcPlayer(KinectWrapper* subject, 
                     const SdlWindow& wnd,
                     const std::string& video_path)
   : mSubject(subject)
   , mWindow(wnd)
   , mVideoPath(video_path)
   , mSurface(NULL)
   , mSurfaceMutex(NULL)
   , mLibvlc(NULL)
   , mMediaPlayer(NULL)
{
   mSubject->Subscribe(this);

   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   wnd.GetXRes(),
                                   wnd.GetYRes(),
                                   24, 0, 0, 0, 0);
   if (!mSurface) {
      throw "SDL_CreateRGBSurface() failed.";
   }

   mSurfaceMutex = SDL_CreateMutex();
   if (!mSurfaceMutex) {
      throw "SDL_CreateMutex() failed.";
   }
//    mSurface = wnd.GetSurface();
//    mSurfaceMutex = wnd.GetMutex();


   char const* vlc_argv[] =
   {
//        "--no-audio", // skip any audio track
//        "--no-xlib", // tell VLC to not use Xlib
      "--plugin-path", "D:\\Development\\Projects\\kinect\\external\\vlc-1.1.11\\plugins",
   };
   const int vlc_argc = sizeof(vlc_argv) / sizeof(*vlc_argv);

   // TODO: Error handling!

   mLibvlc = libvlc_new(vlc_argc, vlc_argv);

   libvlc_media_t* vlc_media = libvlc_media_new_path(mLibvlc, mVideoPath.c_str());
   mMediaPlayer = libvlc_media_player_new_from_media(vlc_media);
   libvlc_media_release(vlc_media);

   // TODO: This class should manage its own surface to draw on.
   //  The Update() method should then blit the video surface onto the window surface.

   libvlc_video_set_callbacks(mMediaPlayer, VlcLock, VlcUnlock, VlcDisplay, this);
   libvlc_video_set_format(mMediaPlayer, "RV24", wnd.GetXRes(), wnd.GetYRes(), wnd.GetXRes() * 3);
   libvlc_media_player_play(mMediaPlayer);
}

VlcPlayer::~VlcPlayer()
{
   libvlc_media_player_stop(mMediaPlayer);
   libvlc_media_player_release(mMediaPlayer);
   libvlc_release(mLibvlc);

   SDL_DestroyMutex(mSurfaceMutex);
   SDL_FreeSurface(mSurface);

   if (mSubject) {
      mSubject->Unsubscribe(this);
   }
}

void VlcPlayer::Update(const Subject* updated_subject)
{
   if (updated_subject != mSubject) {
      // This is not the subject that we registered to.
      throw "Invalid subject.";
   }

   SDL_LockMutex(mSurfaceMutex);
   mWindow.Blit(mSurface);
   SDL_UnlockMutex(mSurfaceMutex);
}

void* VlcPlayer::VlcLock(void* data, void** pixels)
{
   VlcPlayer* vp = static_cast<VlcPlayer*>(data);

   SDL_LockMutex(vp->mSurfaceMutex);
   SDL_LockSurface(vp->mSurface);
   *pixels = vp->mSurface->pixels;
   return NULL;
}

void VlcPlayer::VlcUnlock(void* data, void* id, void* const* pixels)
{
   (void) id;
   (void) pixels;

   VlcPlayer* vp = static_cast<VlcPlayer*>(data);

   SDL_UnlockSurface(vp->mSurface);
	SDL_UnlockMutex(vp->mSurfaceMutex);
}

void VlcPlayer::VlcDisplay(void* data, void* id)
{
   (void) data;
   (void) id;
}

} // namespace op
