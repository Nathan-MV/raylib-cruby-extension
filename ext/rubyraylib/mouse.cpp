#include "mouse.hpp"

// Input-related functions: mouse
// RLAPI bool IsMouseButtonPressed(int button);                  // Check if a mouse button has been pressed once
RB_METHOD_BOOL_ARG_INT(rb_mouse_button_pressed, IsMouseButtonPressed)
// RLAPI bool IsMouseButtonDown(int button);                     // Check if a mouse button is being pressed
RB_METHOD_BOOL_ARG_INT(rb_mouse_button_down, IsMouseButtonDown)
// RLAPI bool IsMouseButtonReleased(int button);                 // Check if a mouse button has been released once
RB_METHOD_BOOL_ARG_INT(rb_mouse_button_released, IsMouseButtonReleased)
// RLAPI bool IsMouseButtonUp(int button);                       // Check if a mouse button is NOT being pressed
RB_METHOD_BOOL_ARG_INT(rb_mouse_button_up, IsMouseButtonUp)
// RLAPI int GetMouseX(void);                                    // Get mouse position X
RB_METHOD_INT(rb_get_mouse_x, GetMouseX)
// RLAPI int GetMouseY(void);                                    // Get mouse position Y
RB_METHOD_INT(rb_get_mouse_y, GetMouseY)
// RLAPI Vector2 GetMousePosition(void);                         // Get mouse position XY
RB_METHOD_VEC2(rb_get_mouse_position, GetMousePosition)
// RLAPI Vector2 GetMouseDelta(void);                            // Get mouse delta between frames
RB_METHOD_VEC2(rb_get_mouse_delta, GetMouseDelta)
// RLAPI void SetMousePosition(int x, int y);                    // Set mouse position XY
RB_METHOD_ARG_INT_2(rb_set_mouse_position, SetMousePosition)
// RLAPI void SetMouseOffset(int offsetX, int offsetY);          // Set mouse offset
RB_METHOD_ARG_INT_2(rb_set_mouse_offset, SetMouseOffset)
// RLAPI void SetMouseScale(float scaleX, float scaleY);         // Set mouse scaling
RB_METHOD_ARG_FLOAT_2(rb_set_mouse_scale, SetMouseScale)
// RLAPI float GetMouseWheelMove(void);                          // Get mouse wheel movement for X or Y, whichever is larger
RB_METHOD_FLOAT(rb_get_mouse_wheel_move, GetMouseWheelMove)
// RLAPI Vector2 GetMouseWheelMoveV(void);                       // Get mouse wheel movement for both X and Y
RB_METHOD_VEC2(rb_get_mouse_wheel_move_v, GetMouseWheelMoveV)
// RLAPI void SetMouseCursor(int cursor);                        // Set mouse cursor
RB_METHOD_ARG_INT(rb_set_mouse_cursor, SetMouseCursor)

extern "C" void initializeMouse() {
  VALUE rb_mMouse = rb_define_module_under(rb_mRL, "Mouse");

  rb_define_module_function(rb_mMouse, "button_pressed?", rb_mouse_button_pressed, 1);
  rb_define_module_function(rb_mMouse, "button_down?", rb_mouse_button_down, 1);
  rb_define_module_function(rb_mMouse, "button_released?", rb_mouse_button_released, 1);
  rb_define_module_function(rb_mMouse, "button_up?", rb_mouse_button_up, 1);
  rb_define_module_function(rb_mMouse, "x", rb_get_mouse_x, 0);
  rb_define_module_function(rb_mMouse, "y", rb_get_mouse_y, 0);
  rb_define_module_function(rb_mMouse, "position", rb_get_mouse_position, 0);
  rb_define_module_function(rb_mMouse, "delta", rb_get_mouse_delta, 0);
  rb_define_module_function(rb_mMouse, "position=", rb_set_mouse_position, 2);
  rb_define_module_function(rb_mMouse, "offset=", rb_set_mouse_offset, 2);
  rb_define_module_function(rb_mMouse, "scale=", rb_set_mouse_scale, 2);
  rb_define_module_function(rb_mMouse, "wheel_move", rb_get_mouse_wheel_move, 0);
  rb_define_module_function(rb_mMouse, "wheel_move_v", rb_get_mouse_wheel_move, 0);
  rb_define_module_function(rb_mMouse, "cursor=", rb_set_mouse_cursor, 1);

  // Define mouse button constants
  rb_define_const(rb_mMouse, "BUTTON_LEFT", INT2NUM(0));
  rb_define_const(rb_mMouse, "BUTTON_RIGHT", INT2NUM(1));
  rb_define_const(rb_mMouse, "BUTTON_MIDDLE", INT2NUM(2));
  rb_define_const(rb_mMouse, "BUTTON_SIDE", INT2NUM(3));
  rb_define_const(rb_mMouse, "BUTTON_EXTRA", INT2NUM(4));
  rb_define_const(rb_mMouse, "BUTTON_FORWARD", INT2NUM(5));
  rb_define_const(rb_mMouse, "BUTTON_BACK", INT2NUM(6));

  // Define mouse cursor constants
  rb_define_const(rb_mMouse, "CURSOR_DEFAULT", INT2NUM(0));
  rb_define_const(rb_mMouse, "CURSOR_ARROW", INT2NUM(1));
  rb_define_const(rb_mMouse, "CURSOR_IBEAM", INT2NUM(2));
  rb_define_const(rb_mMouse, "CURSOR_CROSSHAIR", INT2NUM(3));
  rb_define_const(rb_mMouse, "CURSOR_POINTING_HAND", INT2NUM(4));
  rb_define_const(rb_mMouse, "CURSOR_RESIZE_EW", INT2NUM(5));
  rb_define_const(rb_mMouse, "CURSOR_RESIZE_NS", INT2NUM(6));
  rb_define_const(rb_mMouse, "CURSOR_RESIZE_NWSE", INT2NUM(7));
  rb_define_const(rb_mMouse, "CURSOR_RESIZE_NESW", INT2NUM(8));
  rb_define_const(rb_mMouse, "CURSOR_RESIZE_ALL", INT2NUM(9));
  rb_define_const(rb_mMouse, "CURSOR_NOT_ALLOWED", INT2NUM(10));
}
