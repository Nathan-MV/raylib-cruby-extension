#include "raylib_values.hpp"

VALUE rb_mRL;

extern "C" void initializeRaylib() { rb_mRL = rb_define_module("RL"); }
