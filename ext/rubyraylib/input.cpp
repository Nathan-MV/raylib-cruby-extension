#include "input.hpp"

RB_METHOD_BOOL_ARG_INT(rb_key_pressed, IsKeyPressed)
RB_METHOD_BOOL_ARG_INT(rb_key_pressed_repeat, IsKeyPressedRepeat)
RB_METHOD_BOOL_ARG_INT(rb_key_down, IsKeyDown)
RB_METHOD_BOOL_ARG_INT(rb_key_released, IsKeyReleased)
RB_METHOD_BOOL_ARG_INT(rb_key_up, IsKeyUp)
RB_METHOD_INT(rb_get_key_pressed, GetKeyPressed)
RB_METHOD_INT(rb_get_char_pressed, GetCharPressed)
RB_METHOD_ARG_INT(rb_set_exit_key, SetExitKey)

void initializeInput() {
  VALUE rb_mInput = rb_define_module("Input");

  rb_define_module_function(rb_mInput, "pressed?", rb_key_pressed, 1);
	rb_define_module_function(rb_mInput, "repeat?", rb_key_pressed_repeat, 1);
	rb_define_module_function(rb_mInput, "down?", rb_key_down, 1);
	rb_define_module_function(rb_mInput, "released?", rb_key_released, 1);
	rb_define_module_function(rb_mInput, "up?", rb_key_up, 1);
	rb_define_module_function(rb_mInput, "key_pressed", rb_get_key_pressed, 0);
	rb_define_module_function(rb_mInput, "char_pressed", rb_get_char_pressed, 0);
	rb_define_module_function(rb_mInput, "exit_key=", rb_set_exit_key, 1);
}
