#ifndef VEC3_H
#define VEC3_H

#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cVec3;
extern "C" void Init_Vec3();

inline Vector3* get_vec3(VALUE obj) {
  Vector3 *vec3;
  Data_Get_Struct(obj, Vector3, vec3);

  return vec3;
}

#endif // VEC3_H
