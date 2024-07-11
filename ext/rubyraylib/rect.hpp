#ifndef RECT_H
#define RECT_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"

extern "C" void initializeRect();

inline Rectangle* get_rect(VALUE obj) {
  Rectangle *rect;
  Data_Get_Struct(obj, Rectangle, rect);

  return rect;
}

#endif // RECT_H
