#ifndef DEBUG_OVERLAY_DRAWER_H
#define DEBUG_OVERLAY_DRAWER_H

#include "Observer.h"
#include "KinectWrapper.h"

#if defined(WIN32)
#include <SDL.h>
#elif defined (__linux__)
#include <SDL/SDL.h>
#endif

#include <sstream>

class SdlWindow;

enum DebugOverlayMode {
   dom_None,
   dom_JointsRealWorld,
   dom_JointsProjective,
   DEBUG_OVERLAY_MODE_ITEM_COUNT
};

class DebugOverlayDrawer : public Observer
{
public:
   DebugOverlayDrawer(KinectWrapper* subject, const SdlWindow& wnd);
   virtual ~DebugOverlayDrawer();

   virtual void Update(const Subject* updated_subject);

   DebugOverlayMode SwitchOverlayMode();

private:
   void DrawOverlay();

   KinectWrapper* const mSubject;
   const SdlWindow& mWindow;

   DebugOverlayMode mOverlayMode;

   SDL_Color mTextColor;
   std::ostringstream mTextBuf;

   DebugOverlayDrawer& operator=(const DebugOverlayDrawer&);
};

#endif // DEBUG_OVERLAY_DRAWER_H
