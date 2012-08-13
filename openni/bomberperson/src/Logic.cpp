#include "Logic.hpp"
#include "Renderer.hpp"
#include "Match.hpp"
#include "KeyboardInput.hpp"
#include "Kinect.hpp"
#include "Field.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include "Utils.hpp"

#include <SDL_events.h>

Logic::Logic(
   const std::shared_ptr<Renderer>& renderer,
   const std::shared_ptr<kinex::Nui>& kinect
)
   : mRenderer(renderer)
{
   // Create a new game and start it.
   // This should usually just be done when the app cahnges from mainmenu-state
   //  or from the choose-match-options-state into the actual game-state.

   Point field_pos(30, 30);
   Size field_size(480, 480);
   auto playing_field = std::make_shared<Field>("test_field",
                                                field_pos,
                                                field_size);

   const std::vector<std::shared_ptr<Player>> players = {
      std::make_shared<Player>("player_1",
                               std::make_shared<KeyboardInput>(SDLK_UP,
                                                               SDLK_DOWN,
                                                               SDLK_LEFT,
                                                               SDLK_RIGHT,
                                                               SDLK_SPACE),
                               playing_field->GetCellFromCoordinates(1, 1))
//    , std::make_shared<Player>("player_2",
//                               std::make_shared<KeyboardInput>(SDLK_w,
//                                                               SDLK_s,
//                                                               SDLK_a,
//                                                               SDLK_d,
//                                                               SDLK_LCTRL),
//                               playing_field->GetCellFromCoordinates(2, 1))
   };

   mMatch = std::make_shared<Match>(playing_field, players);
}

Logic::~Logic()
{

}

void Logic::ProcessInput(const SDL_KeyboardEvent& ev)
{
   // TODO: Find out if non-Up/Down Handling is a better choice: GetKeystate()

   const auto players = mMatch->GetPlayers();

   if (SDL_KEYDOWN == ev.type)
   {
      for (auto& player : players)
      {
         player->GetInputDevice()->Press(ev.keysym.sym);
      }
   }
   else if (SDL_KEYUP == ev.type)
   {
      for (auto& player : players)
      {
         player->GetInputDevice()->Release(ev.keysym.sym);
      }
   }
}

//void Logic::ProcessInput(const kinex::Nui& kinect)
//{
////   // FIXME: This gets input data from one frame ago instead of the current one.
////   mKinectInput->Pressed(mPlayer->GetInput());
//}

void Logic::Update(const int app_time, const int elapsed_time)
{
   mMatch->Update(elapsed_time);
}

void Logic::Render()
{
   mRenderer->PreRender();

   const auto playing_field = mMatch->GetField();
   mRenderer->Render(playing_field);

   // Collect all bombs and explosions from the cells for later rendering.
   std::vector<std::shared_ptr<Bomb>> bombs;
   std::vector<std::shared_ptr<Explosion>> explosions;

   for (const auto& cell : playing_field->GetCells()) {
      mRenderer->Render(cell);

      if (cell->HasBomb()) {
         bombs.push_back(cell->GetBomb());
      }

      if (cell->HasExplosion()) {
         explosions.push_back(cell->GetExplosion());
      }
   }

   for (const auto& bomb : bombs) {
      mRenderer->Render(bomb);
   }

   for (const auto& player : mMatch->GetPlayers()) {
      mRenderer->Render(player);
   }

   for (const auto& explosion : explosions) {
      mRenderer->Render(explosion);
   }

   mRenderer->PostRender();
}
