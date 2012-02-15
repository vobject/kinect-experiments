#include "SdlWindowDrawer.h"
#include "SdlWindow.h"

SdlWindowDrawer::SdlWindowDrawer(KinectWrapper* subject, const SdlWindow& wnd)
   : mSubject(subject)
   , mWindow(wnd)
   , mXRes(mSubject->GetXRes())
   , mYRes(mSubject->GetYRes())
   , mSurface(NULL)
   , mDisplayMode(dm_Image)
   , mMaxDepth(3000)
{
   mSurface = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   wnd.GetXRes(),
                                   wnd.GetYRes(),
                                   24, 0, 0, 0, 0);
   if (!mSurface) {
      throw "SDL_CreateRGBSurface() failed.";
   }

   mSubject->Subscribe(this);
}

SdlWindowDrawer::~SdlWindowDrawer()
{
   if (mSubject) {
      mSubject->Unsubscribe(this);
   }

   SDL_FreeSurface(mSurface);
}

void SdlWindowDrawer::Update( const Subject* updated_subject )
{
   if (updated_subject != mSubject) {
      // This is not the subject that we registered to.
      throw "Invalid subject.";
   }

   if (dm_Image == mDisplayMode)
   {
      DrawImage();
   }
   else if (dm_Depth == mDisplayMode)
   {
      DrawDepthMap();
   }
   else
   {
      SDL_FillRect(mSurface, NULL, 0xff0000);
   }

   mWindow.Blit(mSurface, NULL, NULL);
}

DisplayMode SdlWindowDrawer::SwitchDisplayMode()
{
   mDisplayMode = (DisplayMode)((mDisplayMode + 1) % DISPLAY_MODE_ITEM_COUNT);
   return mDisplayMode;
}

int SdlWindowDrawer::IncreaseDepth( const int plus /*= 200*/ )
{
   return mMaxDepth += plus;
}

int SdlWindowDrawer::DecreaseDepth( const int minus /*= 200*/ )
{
   return mMaxDepth -= minus;
}

void SdlWindowDrawer::DrawImage()
{
   SdlSurface surface(mSurface);
   memcpy(surface->pixels, mSubject->GetImageData(), mXRes * mYRes * 3);
}

void SdlWindowDrawer::DrawDepthMap()
{
   SdlSurface surface(mSurface);

   // Get a pointer/iterator for the depth data from the generator.
   const XnDepthPixel* pDepthBuf = mSubject->GetDepthData();
   // Get a pointer/iterator for the SDL screen buffer.
   XnRGB24Pixel* pSurfaceBuf = (XnRGB24Pixel*)surface->pixels;

   const int MAX_COLORS = 255;
   const int MAX_ZONES = (mMaxDepth / MAX_COLORS) + 1;

   for (XnInt i = 0; i < (mYRes * mXRes); ++i, ++pDepthBuf, ++pSurfaceBuf)
   {
      if ((0 == *pDepthBuf) || (mMaxDepth < *pDepthBuf))
      {
         // Everything beyond maximum chosen depth is black.
         pSurfaceBuf->nRed = 0;
         pSurfaceBuf->nGreen = 0;
         pSurfaceBuf->nBlue = 0;
      }
      else
      {
         pSurfaceBuf->nRed = 0;
         pSurfaceBuf->nGreen = MAX_COLORS - *pDepthBuf / MAX_ZONES;
         pSurfaceBuf->nBlue = 0;
      }
   }
}
