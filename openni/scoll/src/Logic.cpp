#include "Logic.h"
#include "View.h"
#include "Log.h"

Logic::Logic(std::shared_ptr<Renderer> renderer)
   : mView(new View(renderer))
{

}

Logic::~Logic()
{

}

void Logic::Update(const int game_time, const int elapsed_time)
{
   mView->Update(elapsed_time);
}

void Logic::Render()
{
   mView->Render();
}
