#include "touch.hpp"

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

void initializeTouch() {
  VALUE rb_mTouch = rb_define_module("Touch");

  rb_define_module_function(rb_mTouch, "x", rb_get_touch_x, 0);
  rb_define_module_function(rb_mTouch, "y", rb_get_touch_y, 0);
  rb_define_module_function(rb_mTouch, "position", rb_get_touch_position, 1);
  rb_define_module_function(rb_mTouch, "point_id", rb_get_touch_point_id, 1);
  rb_define_module_function(rb_mTouch, "point_count", rb_get_touch_point_count, 0);

  rb_define_module_function(rb_mTouch, "enabled=", rb_set_gestures_enabled, 1);
  rb_define_module_function(rb_mTouch, "detected?", rb_gesture_detected, 1);
  rb_define_module_function(rb_mTouch, "detected", rb_get_gesture_detected, 0);
  rb_define_module_function(rb_mTouch, "hold_duration", rb_get_gesture_hold_duration, 0);
  rb_define_module_function(rb_mTouch, "drag_vector", rb_get_gesture_drag_vector, 0);
  rb_define_module_function(rb_mTouch, "drag_angle", rb_get_gesture_drag_angle, 0);
  rb_define_module_function(rb_mTouch, "pinch_vector", rb_get_gesture_pinch_vector, 0);
  rb_define_module_function(rb_mTouch, "pinch_angle", rb_get_gesture_pinch_angle, 0);
}
