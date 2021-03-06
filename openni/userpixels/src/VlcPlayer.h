#ifndef VLC_PLAYER_H
#define VLC_PLAYER_H

#include <vlc/vlc.h>

#include <SDL.h>
#include <SDL_mutex.h>

#include <string>

class SdlWindow;

class VlcPlayer
{
public:
   VlcPlayer(const SdlWindow& wnd, const std::string& vlc_plugins_dir, const std::string& video_path);
   ~VlcPlayer();

   void Blit() const;

   void Play() const;
   void Pause() const;
   void SeekForward() const;
   void SeekBackward() const;

private:
   static void* VlcLock(void* data, void** pixels);
   static void VlcUnlock(void* data, void* id, void* const* pixels);
   static void VlcDisplay(void* data, void* id);

   const SdlWindow& mWindow;
   const std::string mVideoPath;

   SDL_Surface* mSurface;
   SDL_mutex* mSurfaceMutex;

   libvlc_instance_t* mLibvlc;
   libvlc_media_player_t* mMediaPlayer;

   VlcPlayer(const VlcPlayer&);
   VlcPlayer& operator=(const VlcPlayer&);
};

#endif // VLC_PLAYER_H
