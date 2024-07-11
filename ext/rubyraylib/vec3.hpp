#ifndef VEC3_H
#define VEC3_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "color.hpp"

extern VALUE rb_cVec3;
extern "C" void initializeVec3();

inline Vector3* get_vec3(VALUE obj) {
  Vector3 *vec3;
  Data_Get_Struct(obj, Vector3, vec3);

  return vec3;
}

#endif // VEC3_H
