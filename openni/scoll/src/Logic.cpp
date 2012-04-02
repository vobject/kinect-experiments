#include "Logic.h"
#include "View.h"
#include "Sprite.h"
#include "Log.h"

#include <iostream>

static void print_commands()
{
   std::cout << "Commands:\n"
//             << "\tm - Toggle image/depth mode\n"
//             << "\tf - Seek 100 frames forward\n"
//             << "\tb - Seek 100 frames backward\n"
//             << "\ti - Increase depth by 20cm\n"
//             << "\to - Decrease depth by 20cm\n"
//             << "\tu - Toggle user tracking mode\n"
//             << "\td - Toggle debug overlay mode\n"
//             << "\th - Print this help message\n"
             << "\tESC - Exit program\n"
             << std::endl;
}

Logic::Logic(std::shared_ptr<Renderer> renderer)
   : mView(new View(renderer))
{

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
      case SDLK_f:
         {
            static int i = 10;
            i += 10;

            std::shared_ptr<SceneObject> obj(new Sprite());
            obj->SetResource("Rectangle");
            obj->SetPos(i, i);
            obj->SetSize(i, i);
            obj->SetZOrder(1);
            mView->AddObject(obj);
         }
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

void Logic::Update(const int game_time, const int elapsed_time)
{
   mView->Update(elapsed_time);
}

void Logic::Render()
{
   mView->Render();
}
