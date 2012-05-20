#ifndef UTILS_HPP
#define UTILS_HPP

#include "Log.hpp"

#include <memory>
#include <utility>

enum class VideoMode
{
   Software,
   OpenGL
};

struct Point
{
   constexpr Point(int x, int y) : X(x), Y(y) { }

   int X;
   int Y;
};

struct Size
{
   constexpr Size(int width, int height) : Width(width), Height(height) { }

   int Width;
   int Height;
};

struct Rect
{
   constexpr Rect(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) { }

   int X;
   int Y;
   int Width;
   int Height;
};

constexpr int operator"" _pt(unsigned long long point_size)
{
   return point_size;
}

constexpr int operator"" _px(unsigned long long pixels)
{
   return pixels;
}

constexpr int operator"" _ms(unsigned long long milliseconds)
{
   return milliseconds;
}

constexpr int operator"" _mm(unsigned long long millimeters)
{
   return millimeters;
}

// http://herbsutter.com/gotw/_102/
// http://stackoverflow.com/questions/10149840/c-arrays-and-make-unique
template<typename T, typename ...Args>
typename std::enable_if<!std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(Args&& ...args)
{
   return std::unique_ptr<T>(new T(std::forward<Args>(args)...));
}

template<typename T>
typename std::enable_if<std::is_array<T>::value, std::unique_ptr<T>>::type
make_unique(std::size_t n)
{
   typedef typename std::remove_extent<T>::type RT;
   return std::unique_ptr<T>(new RT[n]);
}

#endif // UTILS_HPP
