#ifndef UTILS_H
#define UTILS_H

#include "Log.hpp"

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

#endif // UTILS_H
