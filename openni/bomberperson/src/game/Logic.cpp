#include "Logic.hpp"
#include "Match.hpp"
#include "FieldGenerator.hpp"
#include "Field.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include "../input/KeyboardInput.hpp"
#include "../render/Renderer.hpp"
#include "../utils/Utils.hpp"

#include <SDL_events.h>

Logic::Logic(const std::shared_ptr<Renderer>& renderer)
   : mRenderer(renderer)
{
   // Create a new game and start it.
   // This should usually just be done when the app cahnges from mainmenu-state
   //  or from the choose-match-options-state into the actual game-state.

   const int player_count = 2;
   const int arena_size_x = 16;
   const int arena_size_y = 16;

   mFieldGen = std::make_shared<FieldGenerator>();
   mFieldGen->SetFieldPosition({ 30, 30 });
   mFieldGen->SetFieldSize({ 512, 512 });

   const std::vector<std::shared_ptr<Player>> players = {
      std::make_shared<Player>("player_1")
    , std::make_shared<Player>("player_2")
   };
   auto area = mFieldGen->GetDefaultArena(arena_size_x, arena_size_y, player_count);
   const auto cell_size = area->GetCellSize();

   const auto input_p1 = std::make_shared<KeyboardInput>(SDLK_UP, SDLK_DOWN, SDLK_LEFT, SDLK_RIGHT, SDLK_SPACE);
   const auto parent_cell_p1 = area->GetCellFromCoordinates(1, 1);
   players[0]->SetInputDevice(input_p1);
   players[0]->SetParentCell(parent_cell_p1);
   players[0]->SetPosition(parent_cell_p1->GetPosition());
   players[0]->SetSize({ static_cast<int>(cell_size.Width * .7f),
                         static_cast<int>(cell_size.Height * .7f) });

   const auto input_p2 = std::make_shared<KeyboardInput>(SDLK_w, SDLK_s, SDLK_a, SDLK_d, SDLK_LCTRL);
   const auto parent_cell_p2 = area->GetCellFromCoordinates(arena_size_x - 2, arena_size_y - 2);
   players[1]->SetInputDevice(input_p2);
   players[1]->SetParentCell(parent_cell_p2);
   players[1]->SetPosition(parent_cell_p2->GetPosition());
   players[1]->SetSize({ static_cast<int>(cell_size.Width * .7f),
                         static_cast<int>(cell_size.Height * .7f) });

   mMatch = std::make_shared<Match>(area, players);
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
