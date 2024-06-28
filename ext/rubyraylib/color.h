#ifndef COLOR_H
#define COLOR_H

#include "ruby.h"
#include "raylib_values.h"
#include "vec3.h"
#include "vec4.h"

extern VALUE rb_cColor;
Color* get_color(VALUE obj);
void initializeColor();

#endif // COLOR_H
