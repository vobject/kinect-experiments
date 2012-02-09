#include "VlcPlayer.h"
#include "SdlWindow.h"

VlcPlayer::VlcPlayer(const SdlWindow& wnd, const std::string& video_path)
   : mWindow(wnd)
   , mVideoPath(video_path)
   , mSurface(NULL)
   , mSurfaceMutex(NULL)
   , mLibvlc(NULL)
   , mMediaPlayer(NULL)
{
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

   libvlc_video_set_callbacks(mMediaPlayer, VlcLock, VlcUnlock, VlcDisplay, this);
   libvlc_video_set_format(mMediaPlayer, "RV24", wnd.GetXRes(), wnd.GetYRes(), wnd.GetXRes() * 3);
}

VlcPlayer::~VlcPlayer()
{
   libvlc_media_player_stop(mMediaPlayer);
   libvlc_media_player_release(mMediaPlayer);
   libvlc_release(mLibvlc);

   SDL_DestroyMutex(mSurfaceMutex);
   SDL_FreeSurface(mSurface);
}

void VlcPlayer::Blit() const
{
   SDL_LockMutex(mSurfaceMutex);
   mWindow.Blit(mSurface);
   SDL_UnlockMutex(mSurfaceMutex);
}

void VlcPlayer::Play() const
{
   libvlc_media_player_play(mMediaPlayer);
}

void VlcPlayer::Pause() const
{
   libvlc_media_player_set_pause(mMediaPlayer, 1);
}

void VlcPlayer::SeekForward() const
{
   const libvlc_time_t pos = libvlc_media_player_get_time(mMediaPlayer);
   libvlc_media_player_set_time(mMediaPlayer, pos + 3000);
}

void VlcPlayer::SeekBackward() const
{
   const libvlc_time_t pos = libvlc_media_player_get_time(mMediaPlayer);
   libvlc_media_player_set_time(mMediaPlayer, pos - 3000);
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
