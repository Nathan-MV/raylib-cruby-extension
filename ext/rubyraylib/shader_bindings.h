#ifndef SHADER_H
#define SHADER_H

#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cShader;
extern "C" void Init_Shader();

inline Shader *get_shader(VALUE obj) {
  Shader *shader;
  Data_Get_Struct(obj, Shader, shader);

  return shader;
}

template <typename T> void rb_shader_free(void *ptr) {
  T *obj = static_cast<T *>(ptr);
  UnloadShader(*obj);
  delete obj;
}

template <typename T> VALUE rb_shader_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_shader_free<T>, obj);
  } catch (const std::bad_alloc &e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

#endif // SHADER_H
