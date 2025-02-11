#ifndef COLOR_BINDIGNS_H
#define COLOR_BINDIGNS_H

#include <cmath>
#include <iomanip>
#include <sstream>
#include "ruby_values.h"
#include "raylib_values.h"
#include "color.h"

extern VALUE rb_cColor;
extern "C" void Init_Color();

inline Color* get_color(VALUE obj) {
  Color *color;
  Data_Get_Struct(obj, Color, color);

  return color;
}

// Macro to define getter methods
#define RB_COLOR_GETTER(name, member) \
static VALUE name(VALUE self) { \
  Color *col = get_color(self); \
  return CHR2FIX(col->member); \
}

// Macro to define setter methods
#define RB_COLOR_SETTER(name, member) \
static VALUE name(VALUE self, VALUE value) { \
  Color *col = get_color(self); \
  int val = NUM2INT(value); \
  if (val < 0 || val > 255) { \
    rb_raise(rb_eArgError, "value must be between 0 and 255"); \
  } \
  col->member = (unsigned char)val; \
  return self; \
}

#endif // COLOR_BINDIGNS_H
