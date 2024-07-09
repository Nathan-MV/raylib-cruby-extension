#include "input.hpp"

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard
// RLAPI bool IsKeyPressed(int key);                             // Check if a key has been pressed once
RB_METHOD_BOOL_ARG_INT(rb_key_pressed, IsKeyPressed)
// RLAPI bool IsKeyPressedRepeat(int key);                       // Check if a key has been pressed again (Only PLATFORM_DESKTOP)
RB_METHOD_BOOL_ARG_INT(rb_key_pressed_repeat, IsKeyPressedRepeat)
// RLAPI bool IsKeyDown(int key);                                // Check if a key is being pressed
RB_METHOD_BOOL_ARG_INT(rb_key_down, IsKeyDown)
// RLAPI bool IsKeyReleased(int key);                            // Check if a key has been released once
RB_METHOD_BOOL_ARG_INT(rb_key_released, IsKeyReleased)
// RLAPI bool IsKeyUp(int key);                                  // Check if a key is NOT being pressed
RB_METHOD_BOOL_ARG_INT(rb_key_up, IsKeyUp)
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
RB_METHOD_INT(rb_get_key_pressed, GetKeyPressed)
// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
RB_METHOD_INT(rb_get_char_pressed, GetCharPressed)
// RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
RB_METHOD_ARG_INT(rb_set_exit_key, SetExitKey)

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

// Input-related functions: touch
// RLAPI int GetTouchX(void);                                    // Get touch position X for touch point 0 (relative to screen size)
RB_METHOD_INT(rb_get_touch_x, GetTouchX)
// RLAPI int GetTouchY(void);                                    // Get touch position Y for touch point 0 (relative to screen size)
RB_METHOD_INT(rb_get_touch_y, GetTouchY)
// RLAPI Vector2 GetTouchPosition(int index);                    // Get touch position XY for a touch point index (relative to screen size)
RB_METHOD_VEC2_ARG_INT(rb_get_touch_position, GetTouchPosition)
// RLAPI int GetTouchPointId(int index);                         // Get touch point identifier for given index
RB_METHOD_INT_ARG(rb_get_touch_point_id, GetTouchPointId)
// RLAPI int GetTouchPointCount(void);                           // Get number of touch points
RB_METHOD_INT(rb_get_touch_point_count, GetTouchPointCount)

//------------------------------------------------------------------------------------
// Gestures and Touch Handling Functions (Module: rgestures)
//------------------------------------------------------------------------------------
// RLAPI void SetGesturesEnabled(unsigned int flags);      // Enable a set of gestures using flags
RB_METHOD_ARG_UINT(rb_set_gestures_enabled, SetGesturesEnabled)
// RLAPI bool IsGestureDetected(unsigned int gesture);     // Check if a gesture have been detected
RB_METHOD_BOOL_ARG_UINT(rb_gesture_detected, IsGestureDetected)
// RLAPI int GetGestureDetected(void);                     // Get latest detected gesture
RB_METHOD_INT(rb_get_gesture_detected, GetGestureDetected)
// RLAPI float GetGestureHoldDuration(void);               // Get gesture hold time in milliseconds
RB_METHOD_FLOAT(rb_get_gesture_hold_duration, GetGestureHoldDuration)
// RLAPI Vector2 GetGestureDragVector(void);               // Get gesture drag vector
RB_METHOD_VEC2(rb_get_gesture_drag_vector, GetGestureDragVector)
// RLAPI float GetGestureDragAngle(void);                  // Get gesture drag angle
RB_METHOD_FLOAT(rb_get_gesture_drag_angle, GetGestureDragAngle)
// RLAPI Vector2 GetGesturePinchVector(void);              // Get gesture pinch delta
RB_METHOD_VEC2(rb_get_gesture_pinch_vector, GetGesturePinchVector)
// RLAPI float GetGesturePinchAngle(void);                 // Get gesture pinch angle
RB_METHOD_FLOAT(rb_get_gesture_pinch_angle, GetGesturePinchAngle)

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

  rb_define_module_function(rb_mInput, "gamepad_available?", rb_gamepad_available, 1);
  rb_define_module_function(rb_mInput, "gamepad_name", rb_gamepad_name, 1);
  rb_define_module_function(rb_mInput, "gamepad_button_pressed?", rb_gamepad_button_pressed, 2);
  rb_define_module_function(rb_mInput, "gamepad_button_down?", rb_gamepad_button_down, 2);
  rb_define_module_function(rb_mInput, "gamepad_button_released", rb_gamepad_button_released, 2);
  rb_define_module_function(rb_mInput, "gamepad_button_up?", rb_gamepad_button_up, 2);
  rb_define_module_function(rb_mInput, "gamepad_button_pressed", rb_get_gamepad_button_pressed, 0);
  rb_define_module_function(rb_mInput, "gamepad_axis_count", rb_gamepad_axis_count, 1);
  rb_define_module_function(rb_mInput, "gamepad_axis_movement", rb_gamepad_axis_movement, 2);
  rb_define_module_function(rb_mInput, "gamepad_mappings", rb_set_gamepad_mappings, 1);
  rb_define_module_function(rb_mInput, "gamepad_vibration", rb_set_gamepad_vibration, 3);

  rb_define_module_function(rb_mInput, "mouse_button_pressed?", rb_mouse_button_pressed, 1);
  rb_define_module_function(rb_mInput, "mouse_button_down?", rb_mouse_button_down, 1);
  rb_define_module_function(rb_mInput, "mouse_button_released?", rb_mouse_button_released, 1);
  rb_define_module_function(rb_mInput, "mouse_button_up?", rb_mouse_button_up, 1);
  rb_define_module_function(rb_mInput, "mouse_x", rb_get_mouse_x, 0);
  rb_define_module_function(rb_mInput, "mouse_y", rb_get_mouse_y, 0);
  rb_define_module_function(rb_mInput, "mouse_position", rb_get_mouse_position, 0);
  rb_define_module_function(rb_mInput, "mouse_delta", rb_get_mouse_delta, 0);
  rb_define_module_function(rb_mInput, "mouse_position=", rb_set_mouse_position, 2);
  rb_define_module_function(rb_mInput, "mouse_offset=", rb_set_mouse_offset, 2);
  rb_define_module_function(rb_mInput, "mouse_scale=", rb_set_mouse_scale, 2);
  rb_define_module_function(rb_mInput, "mouse_wheel_move", rb_get_mouse_wheel_move, 0);
  rb_define_module_function(rb_mInput, "mouse_wheel_move_v", rb_get_mouse_wheel_move, 0);
  rb_define_module_function(rb_mInput, "mouse_cursor=", rb_set_mouse_cursor, 1);

  rb_define_module_function(rb_mInput, "touch_x", rb_get_touch_x, 0);
  rb_define_module_function(rb_mInput, "touch_y", rb_get_touch_y, 0);
  rb_define_module_function(rb_mInput, "touch_position", rb_get_touch_position, 1);
  rb_define_module_function(rb_mInput, "touch_point_id", rb_get_touch_point_id, 1);
  rb_define_module_function(rb_mInput, "touch_point_count", rb_get_touch_point_count, 0);

  rb_define_module_function(rb_mInput, "gestures_enabled=", rb_set_gestures_enabled, 1);
  rb_define_module_function(rb_mInput, "gesture_detected?", rb_gesture_detected, 1);
  rb_define_module_function(rb_mInput, "gesture_detected", rb_get_gesture_detected, 0);
  rb_define_module_function(rb_mInput, "gesture_hold_duration", rb_get_gesture_hold_duration, 0);
  rb_define_module_function(rb_mInput, "gesture_drag_vector", rb_get_gesture_drag_vector, 0);
  rb_define_module_function(rb_mInput, "gesture_drag_angle", rb_get_gesture_drag_angle, 0);
  rb_define_module_function(rb_mInput, "gesture_pinch_vector", rb_get_gesture_pinch_vector, 0);
  rb_define_module_function(rb_mInput, "gesture_pinch_angle", rb_get_gesture_pinch_angle, 0);
}
