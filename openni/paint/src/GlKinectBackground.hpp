#ifndef GL_KINECT_BACKGROUND_HPP
#define GL_KINECT_BACKGROUND_HPP

#include "KinectBackground.hpp"

#include <vector>

class Nui;

class GlKinectBackground : public KinectBackground
{
public:
   GlKinectBackground(const std::shared_ptr<Nui>& kinect);
   virtual ~GlKinectBackground();

   GlKinectBackground(const GlKinectBackground&) = delete;
   GlKinectBackground& operator=(const GlKinectBackground&) = delete;

   const void* GetImage(Size& img_size) override;

private:
   void SelectDepthImage();

   std::vector<char> mDepthBuf;
};

#endif // GL_KINECT_BACKGROUND_HPP
