#ifndef LOGIC_HPP
#define LOGIC_HPP

#include <memory>
#include <list>

class SDL_KeyboardEvent;

namespace kinex {
   class Nui;
}
class Renderer;
//class InputDevice;
class Match;

class Logic
{
public:
   Logic(const std::shared_ptr<Renderer>& renderer,
         const std::shared_ptr<kinex::Nui>& kinect);
   virtual ~Logic();

   Logic(const Logic&) = delete;
   Logic& operator=(const Logic&) = delete;

   virtual void ProcessInput(const SDL_KeyboardEvent& ev);
//   virtual void ProcessInput(const kinex::Nui& kinect);

   virtual void Update(int app_time, int elapsed_time);
   virtual void Render();

private:
   std::shared_ptr<Renderer> mRenderer;
//   std::shared_ptr<InputDevice> mKeyboard_1;
//   std::shared_ptr<InputDevice> mKeyboard_2;
   std::shared_ptr<Match> mMatch;
};

#endif // LOGIC_HPP
