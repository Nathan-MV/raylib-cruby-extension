#ifndef RUBYRAYLIB_H
#define RUBYRAYLIB_H 1

#include <fstream>
#include <iostream>
#include <stdexcept>
#include <string>

#include "ruby_values.h"
#include "raylib_values.h"

#include "rect_bindings.h"
#include "color_bindings.h"
#include "draw_bindings.h"
#include "bitmap_bindings.h"
#include "kernel_bindings.h"
#include "sprite_bindings.h"
#include "render_texture_bindings.h"
#include "shader_bindings.h"
#include "vec2_bindings.h"
#include "vec3_bindings.h"
#include "vec4_bindings.h"
#include "table_bindings.h"
#include "graphics_bindings.h"
#include "gui_bindings.h"
#include "ease_bindings.h"
#include "keyboard_bindings.h"
#include "mouse_bindings.h"
#include "gamepad_bindings.h"
#include "touch_bindings.h"
#include "gestures_bindings.h"
#include "shapes_bindings.h"
#include "font_bindings.h"
#include "audio_bindings.h"
#include "camera_bindings.h"

extern "C" {
  void Init_rubyraylib(void);
}

#endif // RUBYRAYLIB_H
