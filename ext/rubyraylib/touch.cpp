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

extern "C" void initializeTouch() {
  VALUE rb_mTouch = rb_define_module_under(rb_mInput, "Touch");

  rb_define_module_function(rb_mTouch, "x", rb_get_touch_x, 0);
  rb_define_module_function(rb_mTouch, "y", rb_get_touch_y, 0);
  rb_define_module_function(rb_mTouch, "position", rb_get_touch_position, 1);
  rb_define_module_function(rb_mTouch, "point_id", rb_get_touch_point_id, 1);
  rb_define_module_function(rb_mTouch, "point_count", rb_get_touch_point_count, 0);
}
