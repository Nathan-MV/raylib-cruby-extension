#ifndef VEC3_H
#define VEC3_H

#include "ruby.h"
#include "raylib_values.h"
#include "color.h"

extern VALUE rb_cVec3;
Vector3* get_vec3(VALUE obj);
void initializeVec3();

#endif // VEC3_H
