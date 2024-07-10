#include "gamepad.hpp"

// Input-related functions: gamepads
// RLAPI bool IsGamepadAvailable(int gamepad);                                        // Check if a gamepad is available
RB_METHOD_BOOL_ARG_INT(rb_gamepad_available, IsGamepadAvailable)
// RLAPI const char *GetGamepadName(int gamepad);                                     // Get gamepad internal name id
RB_METHOD_STR_ARG_INT(rb_gamepad_name, GetGamepadName)
// RLAPI bool IsGamepadButtonPressed(int gamepad, int button);                        // Check if a gamepad button has been pressed once
RB_METHOD_BOOL_ARG_INT_2(rb_gamepad_button_pressed, IsGamepadButtonPressed)
// RLAPI bool IsGamepadButtonDown(int gamepad, int button);                           // Check if a gamepad button is being pressed
RB_METHOD_BOOL_ARG_INT_2(rb_gamepad_button_down, IsGamepadButtonDown)
// RLAPI bool IsGamepadButtonReleased(int gamepad, int button);                       // Check if a gamepad button has been released once
RB_METHOD_BOOL_ARG_INT_2(rb_gamepad_button_released, IsGamepadButtonReleased)
// RLAPI bool IsGamepadButtonUp(int gamepad, int button);                             // Check if a gamepad button is NOT being pressed
RB_METHOD_BOOL_ARG_INT_2(rb_gamepad_button_up, IsGamepadButtonUp)
// RLAPI int GetGamepadButtonPressed(void);                                           // Get the last gamepad button pressed
RB_METHOD_INT(rb_get_gamepad_button_pressed, GetGamepadButtonPressed)
// RLAPI int GetGamepadAxisCount(int gamepad);                                        // Get gamepad axis count for a gamepad
RB_METHOD_INT_ARG(rb_gamepad_axis_count, GetGamepadAxisCount)
// RLAPI float GetGamepadAxisMovement(int gamepad, int axis);                         // Get axis movement value for a gamepad axis
RB_METHOD_FLOAT_ARG_INT_2(rb_gamepad_axis_movement, GetGamepadAxisMovement)
// RLAPI int SetGamepadMappings(const char *mappings);                                // Set internal gamepad mappings (SDL_GameControllerDB)
RB_METHOD_INT_ARG_STR(rb_set_gamepad_mappings, SetGamepadMappings)
// RLAPI void SetGamepadVibration(int gamepad, float leftMotor, float rightMotor);    // Set gamepad vibration for both motors
RB_METHOD_ARG_INT_FLOAT_2(rb_set_gamepad_vibration, SetGamepadVibration)

void initializeGamepad() {
  VALUE rb_mGamepad = rb_define_module("Gamepad");

  rb_define_module_function(rb_mGamepad, "available?", rb_gamepad_available, 1);
  rb_define_module_function(rb_mGamepad, "name", rb_gamepad_name, 1);
  rb_define_module_function(rb_mGamepad, "button_pressed?", rb_gamepad_button_pressed, 2);
  rb_define_module_function(rb_mGamepad, "button_down?", rb_gamepad_button_down, 2);
  rb_define_module_function(rb_mGamepad, "button_released?", rb_gamepad_button_released, 2);
  rb_define_module_function(rb_mGamepad, "button_up?", rb_gamepad_button_up, 2);
  rb_define_module_function(rb_mGamepad, "button_pressed", rb_get_gamepad_button_pressed, 0);
  rb_define_module_function(rb_mGamepad, "axis_count", rb_gamepad_axis_count, 1);
  rb_define_module_function(rb_mGamepad, "axis_movement", rb_gamepad_axis_movement, 2);
  rb_define_module_function(rb_mGamepad, "mappings=", rb_set_gamepad_mappings, 1);
  rb_define_module_function(rb_mGamepad, "vibration=", rb_set_gamepad_vibration, 3);

  // Define gamepad button constants
  rb_define_const(rb_mGamepad, "BUTTON_UNKNOWN", INT2NUM(0));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_FACE_UP", INT2NUM(1));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_FACE_RIGHT", INT2NUM(2));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_FACE_DOWN", INT2NUM(3));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_FACE_LEFT", INT2NUM(4));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_FACE_UP", INT2NUM(5));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_FACE_RIGHT", INT2NUM(6));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_FACE_DOWN", INT2NUM(7));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_FACE_LEFT", INT2NUM(8));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_TRIGGER_1", INT2NUM(9));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_TRIGGER_2", INT2NUM(10));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_TRIGGER_1", INT2NUM(11));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_TRIGGER_2", INT2NUM(12));
  rb_define_const(rb_mGamepad, "BUTTON_MIDDLE_LEFT", INT2NUM(13));
  rb_define_const(rb_mGamepad, "BUTTON_MIDDLE", INT2NUM(14));
  rb_define_const(rb_mGamepad, "BUTTON_MIDDLE_RIGHT", INT2NUM(15));
  rb_define_const(rb_mGamepad, "BUTTON_LEFT_THUMB", INT2NUM(16));
  rb_define_const(rb_mGamepad, "BUTTON_RIGHT_THUMB", INT2NUM(17));

  // Define gamepad axis constants
  rb_define_const(rb_mGamepad, "AXIS_LEFT_X", INT2NUM(0));
  rb_define_const(rb_mGamepad, "AXIS_LEFT_Y", INT2NUM(1));
  rb_define_const(rb_mGamepad, "AXIS_RIGHT_X", INT2NUM(2));
  rb_define_const(rb_mGamepad, "AXIS_RIGHT_Y", INT2NUM(3));
  rb_define_const(rb_mGamepad, "AXIS_LEFT_TRIGGER", INT2NUM(4));
  rb_define_const(rb_mGamepad, "AXIS_RIGHT_TRIGGER", INT2NUM(5));
}
