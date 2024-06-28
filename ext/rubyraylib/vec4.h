#ifndef VEC4_H
#define VEC4_H

#include "ruby.h"
#include "raylib_values.h"
#include "color.h"

extern VALUE rb_cVec4;
Vector4* get_vec4(VALUE obj);
void initializeVec4();

#endif // VEC4_H
