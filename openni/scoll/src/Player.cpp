#include "Player.h"
#include "Kinect.h"
#include "UserData.h"

Player::Player(const std::shared_ptr<Kinect>& kinect)
   : mKinect(kinect)
   , mUserData(UserData::INVALID_USER_ID)
{
   SetResourceId("player");
   SetPosition({ 0, 0 });
   SetSize({ mKinect->GetXRes(), mKinect->GetYRes() });
   SetZOrder(ZOrder::zo_Layer_2);
   SetVisible(false);

   mTexture = std::make_shared<Texture>(SDL_CreateRGBSurface(SDL_SWSURFACE,
                                                             GetSize().Width,
                                                             GetSize().Height,
                                                             32, 0, 0, 0, 0));
   if (!mTexture->GetData()) {
      throw "SDL_CreateRGBSurface() failed.";
   }
}

Player::~Player()
{

}

void Player::Update(const int elapsed_time)
{
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

bool Player::CheckCollision(const SceneObject& obj) const
{
//   auto joints = mUserData->GetRealWorldJoints();
//   const auto left_hand = joints[XN_SKEL_LEFT_HAND];
//   const auto right_hand = joints[XN_SKEL_RIGHT_HAND];
//
//   if ((left_hand.X > obj.GetXPos()) &&
//       (left_hand.X < obj.GetXPos() + obj.GetXRes()) &&
//       (left_hand.Y > obj.GetYPos()) &&
//       (left_hand.Y < obj.GetYPos() + obj.GetYRes()))
//   {
//      return true;
//   }
//
//   if ((right_hand.X > obj.GetXPos()) &&
//       (right_hand.X < obj.GetXPos() + obj.GetXRes()) &&
//       (right_hand.Y > obj.GetYPos()) &&
//       (right_hand.Y < obj.GetYPos() + obj.GetYRes()))
//   {
//      return true;
//   }
//
//   return false;
}

int Player::GetXCenter()
{
   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].X;
}

int Player::GetYCenter()
{
   return mUserData.GetRealWorldJoints()[XN_SKEL_TORSO].Y;
}

std::shared_ptr<Texture> Player::GetFrame() const
{
   SDL_Surface* frame = static_cast<SDL_Surface*>(mTexture->GetData());
   SDL_FillRect(frame, NULL, 0);

   if (!IsVisible()) {
      return mTexture;
   }

   const auto scene_meta = mKinect->GetUserPixels(mUserData);

   SDL_LockSurface(frame);
   char* screen_buf = static_cast<char*>(frame->pixels);
   const int bytes_per_pixel = frame->format->BytesPerPixel;

   const XnRGB24Pixel* rgb_buf = mKinect->GetImageData();
   const XnLabel* label_buf = scene_meta->Data();

   const int pixel_cnt = mKinect->GetYRes() * mKinect->GetXRes();
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
   SDL_UnlockSurface(frame);

   return mTexture;
}

bool Player::IsUserDataValid(const UserData& user) const
{
   auto joints = user.GetRealWorldJoints();
   return (joints[XN_SKEL_TORSO].X && joints[XN_SKEL_TORSO].Y);
}
