#include "gestures.hpp"

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

extern "C" void initializeGestures() {
  VALUE rb_mGestures = rb_define_module_under(rb_mRL, "Gestures");

  rb_define_module_function(rb_mGestures, "enabled=", rb_set_gestures_enabled, 1);
  rb_define_module_function(rb_mGestures, "detected?", rb_gesture_detected, 1);
  rb_define_module_function(rb_mGestures, "detected", rb_get_gesture_detected, 0);
  rb_define_module_function(rb_mGestures, "hold_duration", rb_get_gesture_hold_duration, 0);
  rb_define_module_function(rb_mGestures, "drag_vector", rb_get_gesture_drag_vector, 0);
  rb_define_module_function(rb_mGestures, "drag_angle", rb_get_gesture_drag_angle, 0);
  rb_define_module_function(rb_mGestures, "pinch_vector", rb_get_gesture_pinch_vector, 0);
  rb_define_module_function(rb_mGestures, "pinch_angle", rb_get_gesture_pinch_angle, 0);
}
