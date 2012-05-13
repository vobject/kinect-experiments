//#ifndef GL_WINDOW_HPP
//#define GL_WINDOW_HPP
//
//#include "Window.hpp"
//#include "GlFont.hpp"
//#include "Utils.hpp"
//
//#include <SDL.h>
//
//#include <memory>
//#include <string>
//#include <sstream>
//
//class GlWindow : public Window
//{
//public:
//   GlWindow(const Size& res, const std::string& text);
//   virtual ~GlWindow();
//
//   GlWindow(const GlWindow&) = delete;
//   GlWindow& operator=(const GlWindow&) = delete;
//
//   void Blit(const void* data, const Size& data_size, const Point& dest) override;
//   void Clear() override;
//   void Flip() override;
//
//   void DrawRect(const Point& pos, int size) override;
//   void DrawLine(const Point& src_pos, const Point& dest_pos) override;
//   void WriteText(const std::string& text, const Point& point) override;
//
//private:
//   static Uint32 FrameTimerCallback(Uint32 interval, void *param);
//
////   void DrawPixel(int x, int y, unsigned int color = 0xffffffff);
//
//   SDL_Surface* mScreen = nullptr;
//   SDL_TimerID mFrameTimer = nullptr;
//   int mFrameCount = 0;
//   int mFPS = 0;
//   std::ostringstream mTextBuf;
//   std::unique_ptr<GlFont> mGlFont;
//};
//
//#endif // GL_WINDOW_HPP
