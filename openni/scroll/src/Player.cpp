#include "Player.hpp"
#include "Kinect.hpp"
#include "UserData.hpp"

Player::Player(const std::shared_ptr<kinex::Nui>& kinect)
   : mKinect(kinect)
   , mUserData(kinex::UserData::INVALID_USER_ID)
{
   SetResourceId("player");
   SetPosition({ 0, 0 });
   SetSize(mKinect->GetSize());
   SetZOrder(ZOrder::zo_Layer_2);
   SetVisible(false);

   mTexture = SDL_CreateRGBSurface(SDL_SWSURFACE,
                                   GetSize().Width,
                                   GetSize().Height,
                                   SDL_GetVideoSurface()->format->BitsPerPixel,
                                   0, 0, 0, 0);
   if (!mTexture) {
      throw "SDL_CreateRGBSurface() failed.";
   }
}

Player::~Player()
{
   SDL_FreeSurface(mTexture);
}

void Player::Update(const int elapsed_time)
{
   (void) elapsed_time;

   const auto users = mKinect->GetUsers();
   if (users.empty() || !IsUserDataValid(users[0])) {
      SetVisible(false);
      return;
   }

   mUserData = users[0];
   SetVisible(true);
}

//void Actor::SetInputData(const UserData& user)
//{
//   mUserData.reset(new UserData(user));
//}

bool Player::CheckCollision(const SceneObject& obj, Point& collision) const
{
   auto joints = mUserData.GetPerspectiveJoints();
   const auto left_hand = GetRelativePerspectiveJointPosition(joints[XN_SKEL_LEFT_HAND]);
   const auto right_hand = GetRelativePerspectiveJointPosition(joints[XN_SKEL_RIGHT_HAND]);

   if ((left_hand.X > obj.GetPosition().X) &&
       (left_hand.X < obj.GetPosition().X + obj.GetSize().Width) &&
       (left_hand.Y > obj.GetPosition().Y) &&
       (left_hand.Y < obj.GetPosition().Y + obj.GetSize().Height))
   {
      collision.X = left_hand.X;
      collision.Y = left_hand.Y;
      return true;
   }

   if ((right_hand.X > obj.GetPosition().X) &&
       (right_hand.X < obj.GetPosition().X + obj.GetSize().Width) &&
       (right_hand.Y > obj.GetPosition().Y) &&
       (right_hand.Y < obj.GetPosition().Y + obj.GetSize().Height))
   {
      collision.X = right_hand.X;
      collision.Y = right_hand.Y;
      return true;
   }

   return false;
}

int Player::GetXCenter()
{
   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].X;
}

int Player::GetYCenter()
{
   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].Y;
}

SDL_Surface* Player::GetFrame() const
{
   SDL_FillRect(mTexture, NULL, 0);

   if (!IsVisible()) {
      return mTexture;
   }

   const auto scene_meta = mKinect->GetUserPixels(mUserData);

   SDL_LockSurface(mTexture);
   char* screen_buf = static_cast<char*>(mTexture->pixels);
   const int bytes_per_pixel = mTexture->format->BytesPerPixel;

   const XnRGB24Pixel* rgb_buf = mKinect->GetImageData();
   const XnLabel* label_buf = scene_meta->Data();

   const Size kinect_res = mKinect->GetSize();
   const int pixel_cnt = kinect_res.Width * kinect_res.Height;
   const XnUserID current_id = mUserData.GetId();

   for (int i = 0; i < pixel_cnt; i++, rgb_buf++, label_buf++)
   {
      if (*label_buf == current_id)
      {
         screen_buf[i * bytes_per_pixel]     = rgb_buf->nBlue;
         screen_buf[i * bytes_per_pixel + 1] = rgb_buf->nGreen;
         screen_buf[i * bytes_per_pixel + 2] = rgb_buf->nRed;
      }
   }
   SDL_UnlockSurface(mTexture);

   return mTexture;
}

bool Player::IsUserDataValid(const kinex::UserData& user) const
{
   auto joints = user.GetRealWorldJoints();
   return (joints[XN_SKEL_TORSO].X && joints[XN_SKEL_TORSO].Y);
}

Point Player::GetRelativePerspectiveJointPosition(const XnPoint3D& pos) const
{
   const int relative_x = static_cast<float>(GetSize().Width) / mKinect->GetSize().Width * pos.X + GetPosition().X;
   const int relative_y = static_cast<float>(GetSize().Height) / mKinect->GetSize().Height * pos.Y + GetPosition().Y;
   return {relative_x, relative_y};
}
