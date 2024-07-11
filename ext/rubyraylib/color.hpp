#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <iomanip>
#include <sstream>
#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

extern VALUE rb_cColor;
extern "C" void initializeColor();

inline Color* get_color(VALUE obj) {
  Color *color;
  Data_Get_Struct(obj, Color, color);

  return color;
}

// Macro to define getter methods
#define RB_COLOR_GETTER(name, member) \
static VALUE name(VALUE self) { \
  Color *col = get_color(self); \
  return INT2NUM(col->member); \
}

// Macro to define setter methods
#define RB_COLOR_SETTER(name, member) \
static VALUE name(VALUE self, VALUE value) { \
  Color *col = get_color(self); \
  col->member = NUM2INT(value); \
  return self; \
}

#endif // COLOR_H
