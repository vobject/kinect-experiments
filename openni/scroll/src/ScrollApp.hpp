#ifndef SCROLL_APP_HPP
#define SCROLL_APP_HPP

#include "KinectApp.hpp"

namespace kinex {
   class Window;
}
class ResourceCache;
class Renderer;
class Logic;
class Size;

class ScrollApp : public KinectApp
{
public:
   ScrollApp();
   virtual ~ScrollApp();

   ScrollApp(const ScrollApp&) = delete;
   ScrollApp& operator=(const ScrollApp&) = delete;

protected:
   void Initialize() override;
   void UpdateScene(int app_time, int elapsed_time) override;
   void RenderScene() override;

private:
   void SelectRenderer();

   std::shared_ptr<kinex::Window> mWindow;
   std::shared_ptr<ResourceCache> mResCache;
   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<Logic> mLogic;
//   std::shared_ptr<EventManager> mEventManager;
};

#endif // SCROLL_APP_HPP
