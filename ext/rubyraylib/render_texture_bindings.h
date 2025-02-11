#ifndef RENDER_TEXTURE_H
#define RENDER_TEXTURE_H

#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cRenderTexture;
extern "C" void Init_RenderTexture();

inline RenderTexture2D *get_render_texture(VALUE obj) {
  RenderTexture2D *texture;
  if (!obj || !rb_obj_is_kind_of(obj, rb_cRenderTexture)) {
    rb_raise(rb_eTypeError, "Expected a RenderTexture object.");
    return nullptr;
  }
  Data_Get_Struct(obj, RenderTexture2D, texture);
  if (!texture) {
    rb_raise(rb_eRuntimeError, "Failed to retrieve RenderTexture data.");
  }
  return texture;
}

template <typename T> void rb_render_texture_free(void *ptr) {
  T *obj = static_cast<T *>(ptr);
  if (obj) {
    UnloadRenderTexture(*obj);
    delete obj;
  }
}

template <typename T> VALUE rb_render_texture_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_render_texture_free<T>, obj);
  } catch (const std::bad_alloc &e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  } catch (...) {
    rb_raise(rb_eRuntimeError, "An unexpected error occurred while allocating RenderTexture.");
    return Qnil;
  }
}

// Macro to define getter methods
#define RB_RENDER_TEXTURE_GETTER_UINT(name, member)             \
  static VALUE name(VALUE self) {                               \
    RenderTexture2D *render_texture = get_render_texture(self); \
    if (!render_texture) return Qnil;                           \
    return UINT2NUM(render_texture->member);                 \
  }

#define RB_RENDER_TEXTURE_GETTER_TEXTURE(name, member)                    \
  static VALUE name(VALUE self) {                                         \
    RenderTexture2D *render_texture = get_render_texture(self);           \
    if (!render_texture) return Qnil;                                     \
    return Data_Wrap_Struct(rb_cSprite, nullptr, rb_object_free<Texture2D>, \
                            &render_texture->member);                     \
  }

#endif  // RENDER_TEXTURE_H
