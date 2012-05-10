#ifndef UTILS_H
#define UTILS_H

#include "Log.h"

// TODO:
// Vector 2/3 class

struct Point
{
   Point(int x, int y) : X(x), Y(y) { }

   int X;
   int Y;
};

struct Size
{
   Size(int width, int height) : Width(width), Height(height) { }

   int Width;
   int Height;
};

struct Rect
{
   Rect(int x, int y, int w, int h) : X(x), Y(y), Width(w), Height(h) { }

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

#endif // UTILS_H
