#include "raylib_values.h"

VALUE rb_mRL;

extern "C" void Init_Raylib() { rb_mRL = rb_define_module("RL"); }
