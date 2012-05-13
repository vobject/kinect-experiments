#ifndef PAINT_APP_HPP
#define PAINT_APP_HPP

#include "KinectApp.hpp"

#include <vector>
#include <list>

namespace kinex {
   class Window;
}
class KinectBackground;
class Point;
class Size;

struct Status
{
   bool drawing = false;
   std::vector<std::vector<Point>> lines;
   std::vector<Point> active_line;
};

class PaintApp : public KinectApp
{
public:
   PaintApp();
   virtual ~PaintApp();

   PaintApp(const PaintApp&) = delete;
   PaintApp& operator=(const PaintApp&) = delete;

protected:
   void Initialize() override;
   void UpdateScene(int app_time, int elapsed_time) override;
   void RenderScene() override;

private:
   void ProcessInput();
   void ProcessKinectInput();

   std::shared_ptr<kinex::Window> mWindow;
//   std::shared_ptr<Renderer> mRenderer;

   std::shared_ptr<KinectBackground> mKinectBg;
   Status mState;
};

#endif // PAINT_APP_HPP