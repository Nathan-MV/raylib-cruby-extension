#ifndef TEXTURE_H
#define TEXTURE_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "color.hpp"
#include "vec2.hpp"

// Function declarations
extern "C" void initializeTexture();

inline Texture* get_texture(VALUE obj) {
  Texture *texture;
  Data_Get_Struct(obj, Texture, texture);

  return texture;
}

// Macro to define getter methods
#define RB_TEXTURE_GETTER_INT(name, member) \
static VALUE name(VALUE self) { \
  Texture *texture = get_texture(self); \
  return INT2NUM(texture->member); \
}

// Macro to define draw methods for Texture
#define RB_DRAW_TEXTURE(name, func, ...) \
static VALUE name(VALUE self, ##__VA_ARGS__) { \
  Texture *texture = get_texture(self); \
  func; \
  return Qnil; \
}

#endif // TEXTURE_H
