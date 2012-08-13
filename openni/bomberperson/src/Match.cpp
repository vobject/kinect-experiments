#include "Match.hpp"
//#include "ResourceCache.hpp"
////#include "Kinect.hpp"
//#include "Sprite.hpp"
//#include "Background.h"
#include "Field.hpp"
#include "Cell.hpp"
#include "Player.hpp"
#include "Bomb.hpp"
#include "Explosion.hpp"
////#include "Enemy.hpp"
#include "Utils.hpp"

Match::Match(
   const std::shared_ptr<Field>& playing_field,
   const std::vector<std::shared_ptr<Player>>& players
)
   : mField(playing_field)
   , mPlayers(players)
{

//   mBackground = std::make_shared<Background>(mResCache->GetBackground("bg1"));
//
//   auto obj1 = std::make_shared<Sprite>(mResCache->GetSprite("ken"), true);
//   obj1->SetMsPerFrame(100);
//   obj1->SetSize({ 224_px, 600_px });
//   obj1->SetPosition({ 660, 158 });
//   mEnemies.push_back(obj1);

//   auto obj2 = std::make_shared<Sprite>(mResCache->GetSprite("hulk"), true);
//   obj2->SetMsPerFrame(100);
//   obj2->SetSize({ 250_px, 230_px });
//   obj2->SetPosition({ 10, 230 });
//   mEnemies.push_back(obj2);
//   mHitMap[obj2] = false;

//   auto obj2 = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//   obj2->SetSize({ 64_px, 64_px });
//   obj2->SetPosition({ 100, 30 });
//   mSprites.push_back(obj2);
//
//   auto obj3 = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//   obj3->SetSize({ 32_px, 32_px });
//   obj3->SetPosition({ 400, 400 });
//   mSprites.push_back(obj3);
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
      player->SetCurrentCell(cell);
      player->Update(elapsed_time);
   }

//   for (auto& player : mPlayers)
//   {
//      HandlePlayerUpdate(player, elapsed_time);
//   }

//   HandleBombUpdate(elapsed_time);
//   HandleExplosionUpdate(elapsed_time);
}

std::shared_ptr<Field> Match::GetField() const
{
   return mField;
}

std::vector<std::shared_ptr<Player>> Match::GetPlayers() const
{
   return mPlayers;
}

//std::vector<std::shared_ptr<Bomb>> Match::GetBombs() const
//{
//   return mBombs;
//}

std::vector<std::shared_ptr<Explosion>> Match::GetExplosions() const
{
   return mExplosions;
}

std::shared_ptr<Cell> Match::GetCellFromObject(const std::shared_ptr<SceneObject>& obj) const
{
   const Point pos = { obj->GetPosition().X + (obj->GetSize().Width / 2),
                       obj->GetPosition().Y + (obj->GetSize().Height / 2) };
   return mField->GetCellFromPosition(pos);
}

////int Level::GetRows() const
////{
////   return mCells.size();
////}
////
////int Level::GetColumns() const
////{
////   return GetRows() ? mCells[0].size() : 0;
////}
//
//int Match::GetCellWidth() const
//{
//   return GetSize().Width / mField->GetXCells();
//}
//
//int Match::GetCellHeight() const
//{
//   return GetSize().Height / mField->GetYCells();
//}
//
//void Match::HandlePlayerUpdate(std::shared_ptr<Player>& player, const int elapsed_time)
//{
//   const Point old_pos = player->GetPosition();
//   player->Update(elapsed_time);
//
//   const Size size = player->GetSize();
//   Point pos = player->GetPosition();
//
//   int cell_x;
//   int cell_y;
//   std::tie(cell_x, cell_y) = GetCellCoordinate(player);
//
//   const int cell_width = GetCellWidth();
//   const int cell_height = GetCellHeight();
//
//   const auto above_cell = mField->GetCellAboveOf(cell_x, cell_y);
//   if (above_cell && above_cell->Blocking())
//   {
//      if (pos.Y <= (cell_y * cell_height))
//      {
//         pos.Y = old_pos.Y;
//      }
//   }
//
//   const auto below_cell = mField->GetCellBelowOf(cell_x, cell_y);
//   if (below_cell && below_cell->Blocking())
//   {
//      if ((pos.Y + size.Height) >= (cell_y * cell_height + cell_height))
//      {
//         pos.Y = old_pos.Y;
//      }
//   }
//
//   const auto left_cell = mField->GetCellLeftOf(cell_x, cell_y);
//   if (left_cell && left_cell->Blocking())
//   {
//      if (pos.X <= (cell_x * cell_width))
//      {
//         pos.X = old_pos.X;
//      }
//   }
//
//   const auto right_cell = mField->GetCellRightOf(cell_x, cell_y);
//   if (right_cell && right_cell->Blocking())
//   {
//      if ((pos.X + size.Width) >= (cell_x * cell_width + cell_width))
//      {
//         pos.X = old_pos.X;
//      }
//   }
//
//   player->SetPosition(pos);
//
////   // TODO: This currently checks ALL cells, but it would be enough to
////   //  check the cells next to the players current cell(s).
////   for (int y = 0; y < mField->GetYCells(); y++)
////   {
////      for (int x = 0; x < mField->GetXCells(); x++)
////      {
////         if (CellType::Floor == mField->GetCell(x, y)->GetType()) {
////            continue;
////         }
////
////         const Point cell_pos(cell_width * x, cell_height * y);
////
////         // Player approaches from the left or from the right:
////         if (((pos.X + size.Width) >= cell_pos.X) &&
////             (pos.X <= (cell_pos.X + cell_width)) &&
////             ((pos.Y + size.Height) >= cell_pos.Y) &&
////             (pos.Y <= (cell_pos.Y + cell_height)))
////         {
////            pos.X = old_pos.X;
////         }
////
////         // Player approaches from the top or from the bottom:
////         if (((pos.Y + size.Height) >= cell_pos.Y) &&
////             (pos.Y <= (cell_pos.Y + cell_height)) &&
////             ((pos.X + size.Width) >= cell_pos.X) &&
////             (pos.X <= (cell_pos.X + cell_width)))
////         {
////            pos.Y = old_pos.Y;
////         }
////
////         player->SetPosition(pos);
////      }
////   }
//
//   if (player->HasBomb())
//   {
//      auto bomb = player->GetBomb();
//      bomb->SetPosition({cell_x * cell_width + 1, cell_y * cell_height + 1});
//      mBombs.push_back(bomb);
//   }
//}
//
//void Match::HandleBombUpdate(const int elapsed_time)
//{
//   auto bomb = std::begin(mBombs);
//   while (bomb != std::end(mBombs))
//   {
//       if ((*bomb)->IsAlive())
//       {
//          (*bomb)->Update(elapsed_time);
//          bomb++;
//       }
//       else
//       {
//          auto center_exp = (*bomb)->GetExplosion();
//          mExplosions.push_back(center_exp);
//
//          int cell_x;
//          int cell_y;
//          std::tie(cell_x, cell_y) = GetCellCoordinate(center_exp);
//
//          for (int i = 1; i <= (*bomb)->GetRange(); i++)
//          {
//             const auto above_cell = mField->GetCellAboveOf(cell_x, cell_y - (i - 1));
//
//             if (!above_cell || (CellType::IndestructibleWall == above_cell->GetType())) {
//                break;
//             }
//
//             auto above_range_exp = std::make_shared<Explosion>("explosion_left");
//             above_range_exp->SetPosition({center_exp->GetPosition().X, center_exp->GetPosition().Y - GetCellHeight() * i});
//             mExplosions.push_back(above_range_exp);
//
//             if (CellType::DestructibleWall == above_cell->GetType())
//             {
//                above_cell->SetType(CellType::Floor);
//                break;
//             }
//          }
//
//          for (int i = 1; i <= (*bomb)->GetRange(); i++)
//          {
//             const auto below_cell = mField->GetCellBelowOf(cell_x, cell_y + (i - 1));
//
//             if (!below_cell || (CellType::IndestructibleWall == below_cell->GetType())) {
//                break;
//             }
//
//             auto below_range_exp = std::make_shared<Explosion>("explosion_left");
//             below_range_exp->SetPosition({center_exp->GetPosition().X, center_exp->GetPosition().Y + GetCellHeight() * i});
//             mExplosions.push_back(below_range_exp);
//
//             if (CellType::DestructibleWall == below_cell->GetType())
//             {
//                below_cell->SetType(CellType::Floor);
//                break;
//             }
//          }
//
//          for (int i = 1; i <= (*bomb)->GetRange(); i++)
//          {
//             const auto left_cell = mField->GetCellLeftOf(cell_x - (i - 1), cell_y);
//
//             if (!left_cell || (CellType::IndestructibleWall == left_cell->GetType())) {
//                break;
//             }
//
//             auto left_range_exp = std::make_shared<Explosion>("explosion_left");
//             left_range_exp->SetPosition({center_exp->GetPosition().X - (GetCellWidth() * i), center_exp->GetPosition().Y});
//             mExplosions.push_back(left_range_exp);
//
//             if (CellType::DestructibleWall == left_cell->GetType())
//             {
//                left_cell->SetType(CellType::Floor);
//                break;
//             }
//          }
//
//          for (int i = 1; i <= (*bomb)->GetRange(); i++)
//          {
//             const auto right_cell = mField->GetCellRightOf(cell_x + (i - 1), cell_y);
//
//             if (!right_cell || (CellType::IndestructibleWall == right_cell->GetType())) {
//                break;
//             }
//
//             auto right_range_exp = std::make_shared<Explosion>("explosion_right");
//             right_range_exp->SetPosition({center_exp->GetPosition().X + (GetCellWidth() * i), center_exp->GetPosition().Y});
//             mExplosions.push_back(right_range_exp);
//
//             if (CellType::DestructibleWall == right_cell->GetType())
//             {
//                right_cell->SetType(CellType::Floor);
//                break;
//             }
//          }
//          bomb = mBombs.erase(bomb);
//       }
//   }
//}
//
//void Match::HandleExplosionUpdate(const int elapsed_time)
//{
//   auto explosion = std::begin(mExplosions);
//   while (explosion != std::end(mExplosions))
//   {
//       if ((*explosion)->IsAlive())
//       {
//          (*explosion)->Update(elapsed_time);
//          explosion++;
//       }
//       else
//       {
//          explosion = mExplosions.erase(explosion);
//       }
//   }
//}
//
//std::tuple<int, int> Match::GetCellCoordinate(const std::shared_ptr<SceneObject>& obj) const
//{
//   const auto x_cell = (obj->GetPosition().X + (obj->GetSize().Width / 2)) / GetCellWidth();
//   const auto y_cell = (obj->GetPosition().Y + (obj->GetSize().Height / 2)) / GetCellHeight();
//   return std::make_tuple(x_cell, y_cell);
//}
//
//std::tuple<int, int> Match::GetParentCell(const std::shared_ptr<SceneObject>& obj) const
//{
//   // A player can only have one parent cell.
//   // It is the one where he would plant bombs or from which he would
//   //  take damage if a bomb hit it.
//
//   const Point obj_center(obj->GetPosition().X + (obj->GetSize().Width / 2),
//                          obj->GetPosition().Y + (obj->GetSize().Height / 2));
//
//   for (int y = 0; y < mField->GetYCells(); y++)
//   {
//      for (int x = 0; x < mField->GetXCells(); x++)
//      {
//         const Rect cell_rect(GetCellWidth() * x,
//                              GetCellHeight() * y,
//                              GetCellWidth(),
//                              GetCellHeight());
//
//         if ((obj_center.X >= cell_rect.X) &&
//             (obj_center.X <= (cell_rect.X + cell_rect.Width)) &&
//             (obj_center.Y >= cell_rect.Y) &&
//             (obj_center.Y <= (cell_rect.Y + cell_rect.Height)))
//         {
//            return std::make_tuple(x, y);
//         }
//      }
//   }
//   throw "Unable to find the parent cell of a player. Yes, this is bad!";
//}
//
////void Level::ProcessInput(const PlayerInput& input)
////{
////   const auto punch_l = input.LeftPunch();
////   if (punch_l.present) {
////      HandlePunch(punch_l.pos, mSpriteContacts["hand_left"]);
////   }
////
////   const auto punch_r = input.RightPunch();
////   if (punch_r.present) {
////      HandlePunch(punch_r.pos, mSpriteContacts["hand_right"]);
////   }
////
////   const auto kick_l = input.LeftKick();
////   if (kick_l.present) {
////      HandlePunch(kick_l.pos, mSpriteContacts["foot_left"]);
////   }
////
////   const auto kick_r = input.RightKick();
////   if (kick_r.present) {
////      HandlePunch(kick_r.pos, mSpriteContacts["foot_right"]);
////   }
////
////   const auto hadouken = input.Hadouken();
////   if (hadouken.present && hadouken.first) {
////      auto hadouken_obj = std::make_shared<Sprite>(mResCache->GetSprite("fireball"), true);
////      hadouken_obj->SetSize({ 256_px, 192_px });
////      hadouken_obj->SetPosition({ hadouken.pos.X - (hadouken_obj->GetSize().Width / 2), hadouken.pos.Y - (hadouken_obj->GetSize().Height / 2) });
////      hadouken_obj->SetDirection(1, 0);
////      hadouken_obj->SetSpeed(4, 0);
////      mSprites.push_back(hadouken_obj);
////   }
////}
//
////void Logic::Update(const int app_time, const int elapsed_time)
////{
////   const Uint8* keystate = SDL_GetKeyState(nullptr);
////
////   if (keystate[SDLK_LEFT])
////   {
////      mBackground->ScrollLeft(1);
////   }
////
////   if (keystate[SDLK_RIGHT])
////   {
////      mBackground->ScrollRight(1);
////   }
////
////   UpdateBackground(app_time, elapsed_time);
////   UpdatePlayer(app_time, elapsed_time);
////   UpdateEnemies(app_time, elapsed_time);
////
//////   if(rand() % 1000 == 0)
//////   {
//////      auto obj = std::make_shared<Sprite>(mResCache->GetSprite("arcanister"));
//////      obj->SetSize({ 50_px, 50_px });
//////      obj->SetPosition({ rand() % mXScreen, rand() % mYScreen });
//////      obj->SetDirection(-1, 0);
//////      obj->SetSpeed(2, 2);
//////      mSprites.push_back(obj);
//////   }
////}
