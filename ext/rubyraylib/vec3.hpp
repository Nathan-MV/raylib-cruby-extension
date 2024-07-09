#ifndef VEC3_H
#define VEC3_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"
#include "color.hpp"

extern VALUE rb_cVec3;
Vector3* get_vec3(VALUE obj);
void initializeVec3();

#endif // VEC3_H
