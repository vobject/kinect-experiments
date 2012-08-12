#ifndef BOMBERPERSON_APP_HPP
#define BOMBERPERSON_APP_HPP

#include "KinectApp.hpp"

namespace kinex {
   class Window;
}
class Renderer;
class Logic;

class BomberPersonApp : public kinex::KinectApp
{
public:
   BomberPersonApp();
   virtual ~BomberPersonApp();

   BomberPersonApp(const BomberPersonApp&) = delete;
   BomberPersonApp& operator=(const BomberPersonApp&) = delete;

protected:
   void Initialize() override;
   void UpdateScene(int app_time, int elapsed_time) override;
   void RenderScene() override;

private:
   void SelectRenderer();
   void ProcessInput();

   std::shared_ptr<kinex::Window> mWindow;
   std::shared_ptr<Renderer> mRenderer;
   std::shared_ptr<Logic> mLogic;
};

#endif // BOMBERPERSON_APP_HPP
