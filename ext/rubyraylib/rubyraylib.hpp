#ifndef RUBYRAYLIB_H
#define RUBYRAYLIB_H 1

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>

#include "ruby_values.hpp"
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
#include "keyboard.hpp"
#include "mouse.hpp"
#include "gamepad.hpp"
#include "touch.hpp"
#include "gestures.hpp"
#include "texture_atlas.hpp"
#include "shapes.hpp"

extern "C" {
  void Init_rubyraylib(void);
}

#endif // RUBYRAYLIB_H
