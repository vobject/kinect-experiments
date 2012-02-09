#ifndef __SDL_VIDEO_PLAYER2_H__
#define __SDL_VIDEO_PLAYER2_H__

#include "Observer.h"
#include "KinectWrapper.h"

#include <string>

#include <vlc/vlc.h>

#if defined(WIN32)
#include <SDL.h>
#include <SDL_mutex.h>
#elif defined (__linux__)
#include <SDL/SDL.h>
#include <SDL/SDL_mutex.h>
#endif

namespace kinectlib {

class SdlWindow;

class VlcPlayer : public Observer
{
public:
   VlcPlayer(KinectWrapper* subject, const SdlWindow& wnd, const std::string& video_path);
   virtual ~VlcPlayer();

   virtual void Update(const Subject* updated_subject);

private:
   static void* VlcLock(void* data, void** pixels);
   static void VlcUnlock(void* data, void* id, void* const* pixels);
   static void VlcDisplay(void* data, void* id);

   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;

   const std::string mVideoPath;

   SDL_Surface* mSurface;
   SDL_mutex* mSurfaceMutex;

   libvlc_instance_t* mLibvlc;
   libvlc_media_player_t* mMediaPlayer;

   VlcPlayer& operator=(const VlcPlayer&);
};

} // namespace op

#endif // __SDL_VIDEO_PLAYER2_H__
