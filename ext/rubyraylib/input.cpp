#include "input.hpp"

VALUE rb_mInput;

extern "C" void initializeInput() {
  rb_mInput = rb_define_module("Input");
}
