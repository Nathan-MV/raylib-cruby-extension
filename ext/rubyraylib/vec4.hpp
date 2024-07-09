#ifndef VEC4_H
#define VEC4_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"
#include "color.hpp"

extern VALUE rb_cVec4;
Vector4* get_vec4(VALUE obj);
void initializeVec4();

#endif // VEC4_H
