#ifndef WINDOW_HPP
#define WINDOW_HPP

#include "Utils.hpp"

#include <string>

class Window
{
public:
   Window(const Size& res) : mRes(res) { }
   virtual ~Window() { }

   Size GetSize() const { return mRes; }

   // TODO: replace data and data_size with another data structure (texture?)
   virtual void Blit(const void* data, const Size& data_size, const Point& dest) = 0;
   virtual void Clear() = 0;
   virtual void Flip() = 0;

   virtual void DrawRect(const Point& pos, int size) = 0;
   virtual void DrawLine(const Point& src_pos, const Point& dest_pos) = 0;
   virtual void WriteText(const std::string& text, const Point& point) = 0;

protected:
   const Size mRes;
};

#endif // WINDOW_HPP
