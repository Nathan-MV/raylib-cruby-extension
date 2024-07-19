#include "raylib_values.hpp"

VALUE rb_mRl;

extern "C" void initializeRaylib() { rb_mRl = rb_define_module("Rl"); }
