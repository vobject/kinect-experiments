#ifndef BOMBERPERSON_APP_HPP
#define BOMBERPERSON_APP_HPP

#include "utils/Utils.hpp"

#include <memory>

class Nui;
class WindowFrame;
class Renderer;
class Logic;

enum class VideoMode
{
   Software,
   OpenGL
};

class BomberPersonApp
{
public:
   BomberPersonApp();
   ~BomberPersonApp();

   BomberPersonApp(const BomberPersonApp&) = delete;
   BomberPersonApp& operator=(const BomberPersonApp&) = delete;

   void Start();

private:
   void Mainloop();

   void Initialize();
   void ProcessInput();
   void UpdateScene(int app_time, int elapsed_time);
   void RenderScene();

   void InitNui();
   void InitVideo(VideoMode mode, Size res) const;
   void SelectSdlVideo(Size res) const;
   void SelectGlVideo(Size res) const;

   VideoMode mVideoMode = VideoMode::Software;
   Size mVideoResolution = { 640_px, 480_px };
   bool mQuitRequested = false;

   std::shared_ptr<Nui> mNui;
   std::shared_ptr<WindowFrame> mWndFrame;
   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<Logic> mLogic;
};

#endif // BOMBERPERSON_APP_HPP
