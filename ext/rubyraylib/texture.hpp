#ifndef TEXTURE_H
#define TEXTURE_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "color.hpp"
#include "vec2.hpp"
#include "rect.hpp"

extern VALUE rb_cTexture;
extern "C" void initializeTexture();

inline Texture* get_texture(VALUE obj) {
  Texture *texture;
  Data_Get_Struct(obj, Texture, texture);

  return texture;
}

inline RenderTexture2D* get_render_texture(VALUE obj) {
  RenderTexture2D *texture;
  Data_Get_Struct(obj, RenderTexture2D, texture);

  return texture;
}

template <typename T>
void rb_texture_free(void *ptr) {
  T *obj = static_cast<T *>(ptr);
  UnloadTexture(*obj);
  delete obj;
}

template <typename T>
VALUE rb_texture_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_texture_free<T>, obj);
  } catch (const std::bad_alloc& e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

// Macro to define getter methods
#define RB_TEXTURE_GETTER_INT(name, member) \
static VALUE name(VALUE self) { \
  Texture *texture = get_texture(self); \
  return INT2NUM(texture->member); \
}

#endif // TEXTURE_H
