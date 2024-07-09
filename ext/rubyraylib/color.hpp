#ifndef COLOR_H
#define COLOR_H

#include <cmath>
#include <iomanip>
#include <sstream>
#include <new>
#include <ruby.h>
#include "raylib_values.hpp"
#include "vec3.hpp"
#include "vec4.hpp"

extern VALUE rb_cColor;
void initializeColor();

// Macro to get Color ptr
#define GET_COLOR(obj) \
({ \
  VALUE _obj = (obj); \
  Color *color; \
  Data_Get_Struct(_obj, Color, color); \
  color; \
})

// Macro to define getter methods
#define RB_COLOR_GETTER(name, member) \
static VALUE name(VALUE self) { \
  Color *col = GET_COLOR(self); \
  return INT2NUM(col->member); \
}

// Macro to define setter methods
#define RB_COLOR_SETTER(name, member) \
static VALUE name(VALUE self, VALUE value) { \
  Color *col = GET_COLOR(self); \
  col->member = NUM2INT(value); \
  return self; \
}

#endif // COLOR_H
