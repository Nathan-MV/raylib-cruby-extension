#ifndef VEC4_H
#define VEC4_H

#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cVec4;
extern "C" void Init_Vec4();

inline Vector4* get_vec4(VALUE obj) {
  Vector4 *vec4;
  Data_Get_Struct(obj, Vector4, vec4);

  return vec4;
}

#endif // VEC4_H
