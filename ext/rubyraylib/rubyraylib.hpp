#ifndef RUBYRAYLIB_H
#define RUBYRAYLIB_H 1

#include <ruby.h>
#include "raylib_values.hpp"

#include "rect.hpp"
#include "color.hpp"
#include "draw.hpp"
#include "image.hpp"
#include "kernel.hpp"
#include "texture.hpp"
#include "vec2.hpp"
#include "vec3.hpp"
#include "vec4.hpp"
#include "window.hpp"
#include "gui.hpp"
#include "ease.hpp"
#include "input.hpp"

extern "C" {
  void Init_rubyraylib(void);
}

#endif // RUBYRAYLIB_H
