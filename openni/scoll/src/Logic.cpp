#include "Logic.h"
#include "Kinect.h"
#include "View.h"
#include "Sprite.h"
#include "Background.h"
#include "Log.h"

#include <iostream>

static void print_commands()
{
   std::cout << "Commands:\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

Logic::Logic(std::shared_ptr<Renderer> renderer, std::shared_ptr<Kinect> kinect)
   : mView(new View(renderer))
   , mKinect(kinect)
{
   std::shared_ptr<SceneObject> bg(new Background());
   mView->AddObject(bg);

//   std::shared_ptr<SceneObject> act(new Actor());
//   mView->AddObject(act);
}

Logic::~Logic()
{

}

void Logic::ProcessInput(const SDL_KeyboardEvent& ev)
{
   if (SDL_KEYDOWN == ev.type)
   {
      switch (ev.keysym.sym)
      {
      case SDLK_h:
         print_commands();
         break;
      default:
         break;
      }
   }
   else if (SDL_KEYDOWN == ev.type)
   {
      switch (ev.keysym.sym)
      {
      default:
         break;
      }
   }
}

void Logic::ProcessInput(const SDL_MouseButtonEvent& ev)
{
   if ((SDL_MOUSEBUTTONUP == ev.type) && (SDL_BUTTON_LEFT == ev.button))
   {
      std::shared_ptr<Sprite> obj(new Sprite());
      obj->SetResourceId("Rectangle");
      obj->SetSize(20, 20);
      obj->SetPos(ev.x - (obj->GetWidth() / 2), ev.y - (obj->GetHeight() / 2));
      mView->AddObject(obj);
   }
}

void Logic::Update(const int game_time, const int elapsed_time)
{
   mView->Update(elapsed_time);
}

void Logic::Render()
{
   mView->Render();
}
