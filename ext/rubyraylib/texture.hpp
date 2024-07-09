#ifndef TEXTURE_H
#define TEXTURE_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"
#include "color.hpp"
#include "vec2.hpp"

// Function declarations
void initializeTexture();

// Macro to get Texture ptr
#define GET_TEXTURE(obj) \
({ \
  VALUE _obj = (obj); \
  Texture *texture; \
  Data_Get_Struct(_obj, Texture, texture); \
  texture; \
})

// Macro to define getter methods
#define RB_TEXTURE_GETTER(name, member) \
static VALUE name(VALUE self) { \
  Texture *texture = GET_TEXTURE(self); \
  return INT2NUM(texture->member); \
}

// Macro to define draw methods for Texture
#define RB_DRAW_TEXTURE(name, func, ...) \
static VALUE name(VALUE self, ##__VA_ARGS__) { \
  Texture *texture = GET_TEXTURE(self); \
  func; \
  return Qnil; \
}

#endif // TEXTURE_H
