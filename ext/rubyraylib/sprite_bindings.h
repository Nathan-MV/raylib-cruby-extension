#ifndef SPRITE_H
#define SPRITE_H

#include <stdio.h>
#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cSprite;
extern "C" void Init_Sprite();

inline Texture2D *get_texture(VALUE obj) {
  Texture2D *texture;
  Data_Get_Struct(obj, Texture2D, texture);

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
  static VALUE name(VALUE self) {           \
    Texture2D *texture = get_texture(self); \
    return INT2NUM(texture->member);        \
  }

#endif // SPRITE_H
