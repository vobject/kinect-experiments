#include "Player.hpp"
#include "InputDevice.hpp"
#include "Cell.hpp"
#include "Bomb.hpp"
#include "Utils.hpp"

Player::Player(
   const std::string& name,
   const std::shared_ptr<InputDevice>& input,
   const std::shared_ptr<Cell>& cell
)
   : mInput(input)
   , mParentCell(cell)
{
   SetResourceId(name);
   SetPosition({ mParentCell->GetPosition().X + 10,
                 mParentCell->GetPosition().Y + 10 });
   SetSize({ 25, 25 });
//   SetZOrder(ZOrder::zo_Layer_2);
//   SetVisible(false);
//
//   mTexture = SDL_CreateRGBSurface(SDL_SWSURFACE,
//                                   GetSize().Width,
//                                   GetSize().Height,
//                                   SDL_GetVideoSurface()->format->BitsPerPixel,
//                                   0, 0, 0, 0);
//   if (!mTexture) {
//      throw "SDL_CreateRGBSurface() failed.";
//   }
}

Player::~Player()
{
//   SDL_FreeSurface(mTexture);
}

void Player::Update(const int elapsed_time)
{
   mMoveIdleTime += elapsed_time;
   if (mMoveIdleTime > MOVE_PIXEL_DELAY)
   {
      UpdateMovement(elapsed_time);
      mMoveIdleTime = 0;
   }

   mBombIdleTime += elapsed_time;
   if ((mBombIdleTime > PLANT_BOMB_DELAY) && mInput->TestPlantBomb())
   {
      UpdateBombing(elapsed_time);
      mBombIdleTime = 0;
   }
}

std::shared_ptr<InputDevice> Player::GetInputDevice() const
{
   return mInput;
}

void Player::SetCurrentCell(const std::shared_ptr<Cell>& cell)
{
   mParentCell = cell;
}

void Player::UpdateMovement(const int elapsed_time)
{
   const Point cell_pos = mParentCell->GetPosition();
   const Size cell_size = mParentCell->GetSize();

   const int distance = 1;
   int up = 0;
   int down = 0;
   int left = 0;
   int right = 0;

   if (mInput->TestUp() && CanMoveUp(cell_pos, cell_size, distance)) {
      up++;
   }
   if (mInput->TestDown() && CanMoveDown(cell_pos, cell_size, distance)) {
      down++;
   }
   if (mInput->TestLeft() && CanMoveLeft(cell_pos, cell_size, distance)) {
      left++;
   }
   if (mInput->TestRight() && CanMoveRight(cell_pos, cell_size, distance)) {
      right++;
   }

   SetPosition({ GetPosition().X - left + right, GetPosition().Y - up + down});
}

bool Player::CanMoveUp(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().Y - distance) > cell_pos.Y)
   {
      // Movement inside the current cell is ok.
      return true;
   }

   // Player wants to walk inside the cell on top - check if that is allowed.
   const auto top_cell = mParentCell->GetTopCell();
   if (top_cell && !top_cell->IsBlocking())
   {
      // A cell exists and does not block the player.
      return true;
   }
   // TODO: Should cells with bombs also block? Probably YES!

   return false;
}

bool Player::CanMoveDown(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().Y + GetSize().Height + distance) < (cell_pos.Y + cell_size.Height))
   {
      return true;
   }

   const auto down_cell = mParentCell->GetDownCell();
   if (down_cell && !down_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

bool Player::CanMoveLeft(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().X - distance) > cell_pos.X)
   {
      return true;
   }

   const auto left_cell = mParentCell->GetLeftCell();
   if (left_cell && !left_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

bool Player::CanMoveRight(const Point& cell_pos, const Size& cell_size, const int distance) const
{
   if ((GetPosition().X + GetSize().Width + distance) < (cell_pos.X + cell_size.Width))
   {
      return true;
   }

   const auto right_cell = mParentCell->GetRightCell();
   if (right_cell && !right_cell->IsBlocking())
   {
      return true;
   }

   return false;
}

void Player::UpdateBombing(const int elapsed_time)
{
   auto bomb = std::make_shared<Bomb>("bomb_1", mParentCell);
   bomb->SetRange(3); // TODO: Set depending on players modifications.
   bomb->SetPosition({ mParentCell->GetPosition().X + 1,
                       mParentCell->GetPosition().Y + 1});
   mParentCell->SetBomb(bomb);
}

//void Player::HandleBombUpdate(const int elapsed_time)
//{
//   mBombIdleTime += elapsed_time;
//
//   if (mBombIdleTime > PLANT_BOMB_DELAY)
//   {
//      if (!mInput->TestPlantBomb()) {
//         return;
//      }
//
//      mWantToPlantBomb = true;
//      mBombIdleTime = 0;
//   }
//}

//bool Player::HasBomb() const
//{
//   return mWantToPlantBomb;
//}
//
//std::shared_ptr<Bomb> Player::GetBomb()
//{
//   mWantToPlantBomb = false;
//
//   auto bomb = std::make_shared<Bomb>("bomb_1");
//   bomb->SetRange(3); // TODO: Set depending on players modifications.
//   return bomb;
//}

//int Player::GetSpeed() const
//{
//   return mSpeed;
//}

//bool Player::MoveUp() const
//{
//   return mUpKeyPressed;
//}
//
//bool Player::MoveDown() const
//{
//   return mDownKeyPressed;
//}
//
//bool Player::MoveLeft() const
//{
//   return mLeftKeyPressed;
//}
//
//bool Player::MoveRight() const
//{
//   return mRightKeyPressed;
//}

//void Actor::SetInputData(const UserData& user)
//{
//   mUserData.reset(new UserData(user));
//}

//PlayerInput Player::GetInput()
//{
//   mInput.Update(mUserData);
//   return mInput;
//}
//
//PlayerOrientation Player::GetOrientation() const
//{
//   auto joints = mUserData.GetPerspectiveJoints();
//   const auto head = GetRelativePerspectiveJointPosition(joints[XN_SKEL_HEAD]);
//   const auto torso = GetRelativePerspectiveJointPosition(joints[XN_SKEL_TORSO]);
//   return (head.X < torso.X) ? PlayerOrientation::Left : PlayerOrientation::Right;
//}

//bool Player::CheckAttackCollision(const std::shared_ptr<SceneObject>& obj, Point& collision)
//{
//   auto joints = mUserData.GetPerspectiveJoints();
//
//   const auto left_hand = GetRelativePerspectiveJointPosition(joints[XN_SKEL_LEFT_HAND]);
//   if (CheckCollision(left_hand, *obj))
//   {
//      if (CollisionInProgress(mLeftHandAttacks, obj)) {
//         return false;
//      }
//      mLeftHandAttacks.push_back(obj);
//      collision.X = left_hand.X;
//      collision.Y = left_hand.Y;
//      return true;
//   }
//   mLeftHandAttacks.remove(obj);
//
//   const auto right_hand = GetRelativePerspectiveJointPosition(joints[XN_SKEL_RIGHT_HAND]);
//   if (CheckCollision(right_hand, *obj))
//   {
//      if (CollisionInProgress(mRightHandAttacks, obj)) {
//         return false;
//      }
//      mRightHandAttacks.push_back(obj);
//      collision.X = right_hand.X;
//      collision.Y = right_hand.Y;
//      return true;
//   }
//   mRightHandAttacks.remove(obj);
//
//   const auto left_foot = GetRelativePerspectiveJointPosition(joints[XN_SKEL_LEFT_FOOT]);
//   if (CheckCollision(left_foot, *obj))
//   {
//      if (CollisionInProgress(mLeftFootAttacks, obj)) {
//         return false;
//      }
//      mLeftFootAttacks.push_back(obj);
//      collision.X = left_foot.X;
//      collision.Y = left_foot.Y;
//      return true;
//   }
//   mLeftFootAttacks.remove(obj);
//
//   const auto right_foot = GetRelativePerspectiveJointPosition(joints[XN_SKEL_RIGHT_FOOT]);
//   if (CheckCollision(right_foot, *obj))
//   {
//      if (CollisionInProgress(mRightFootAttacks, obj)) {
//         return false;
//      }
//      mRightFootAttacks.push_back(obj);
//      collision.X = right_foot.X;
//      collision.Y = right_foot.Y;
//      return true;
//   }
//   mRightFootAttacks.remove(obj);
//
//   return false;
//}
//
//bool Player::CheckGenericCollision(const std::shared_ptr<SceneObject>& obj, Point& collision)
//{
//   return false;
//}

//int Player::GetXCenter()
//{
//   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].X;
//}
//
//int Player::GetYCenter()
//{
//   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].Y;
//}

//SDL_Surface* Player::GetFrame() const
//{
//   SDL_FillRect(mTexture, NULL, 0);
//
//   if (!IsVisible()) {
//      return mTexture;
//   }
//
//   const auto scene_meta = mKinect->GetUserPixels(mUserData);
//
//   SDL_LockSurface(mTexture);
//   char* screen_buf = static_cast<char*>(mTexture->pixels);
//   const int bytes_per_pixel = mTexture->format->BytesPerPixel;
//
//   const XnRGB24Pixel* rgb_buf = mKinect->GetImageData();
//   const XnLabel* label_buf = scene_meta->Data();
//
//   const Size kinect_res = mKinect->GetSize();
//   const int pixel_cnt = kinect_res.Width * kinect_res.Height;
//   const XnUserID current_id = mUserData.GetId();
//
//   for (int i = 0; i < pixel_cnt; i++, rgb_buf++, label_buf++)
//   {
//      if (*label_buf == current_id)
//      {
//         screen_buf[i * bytes_per_pixel]     = rgb_buf->nBlue;
//         screen_buf[i * bytes_per_pixel + 1] = rgb_buf->nGreen;
//         screen_buf[i * bytes_per_pixel + 2] = rgb_buf->nRed;
//      }
//   }
//   SDL_UnlockSurface(mTexture);
//
//   return mTexture;
//}
//
//bool Player::IsUserDataValid(const kinex::UserData& user) const
//{
//   auto joints = user.GetRealWorldJoints();
//   return (joints[XN_SKEL_TORSO].X && joints[XN_SKEL_TORSO].Y);
//}
//
//Point Player::GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const
//{
//   const int relative_x = static_cast<float>(GetSize().Width) / mKinect->GetSize().Width * pos.X + GetPosition().X;
//   const int relative_y = static_cast<float>(GetSize().Height) / mKinect->GetSize().Height * pos.Y + GetPosition().Y;
//   return {relative_x, relative_y};
//}

//bool Player::CheckCollision(const Point& pt, const SceneObject& obj) const
//{
//   return (pt.X > obj.GetPosition().X) &&
//          (pt.X < obj.GetPosition().X + obj.GetSize().Width) &&
//          (pt.Y > obj.GetPosition().Y) &&
//          (pt.Y < obj.GetPosition().Y + obj.GetSize().Height);
//}
//
//bool Player::CollisionInProgress(
//   const std::list<std::shared_ptr<SceneObject>>& collisions,
//   const std::shared_ptr<SceneObject>& obj
//) const
//{
//   const auto existing = std::find(collisions.begin(), collisions.end(), obj);
//
//   // The object to check is inside the "currently colliding with"-list.
//   // By convention we return true only for the initial collision.
//   return existing != collisions.end();
//}
