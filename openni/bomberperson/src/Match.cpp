#include "Match.hpp"
#include "Field.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include "Utils.hpp"

Match::Match(
   const std::shared_ptr<Field>& playing_field,
   const std::vector<std::shared_ptr<Player>>& players
)
   : mField(playing_field)
   , mPlayers(players)
{

}

Match::~Match()
{

}

void Match::Update(const int elapsed_time)
{
   mField->Update(elapsed_time);

   for (auto& player : mPlayers)
   {
      const auto cell = GetCellFromObject(player);
      player->SetParentCell(cell);
      player->Update(elapsed_time);
   }
}

std::shared_ptr<Field> Match::GetField() const
{
   return mField;
}

std::vector<std::shared_ptr<Player>> Match::GetPlayers() const
{
   return mPlayers;
}

std::shared_ptr<Cell> Match::GetCellFromObject(const std::shared_ptr<SceneObject>& obj) const
{
   const Point pos = { obj->GetPosition().X + (obj->GetSize().Width / 2),
                       obj->GetPosition().Y + (obj->GetSize().Height / 2) };
   return mField->GetCellFromPosition(pos);
}
