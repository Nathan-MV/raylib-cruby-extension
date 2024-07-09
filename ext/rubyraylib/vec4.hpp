#ifndef VEC4_H
#define VEC4_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"
#include "color.hpp"

extern VALUE rb_cVec4;
void initializeVec4();

inline Vector4* get_vec4(VALUE obj) {
  Vector4 *vec4;
  Data_Get_Struct(obj, Vector4, vec4);

  return vec4;
}

#endif // VEC4_H
