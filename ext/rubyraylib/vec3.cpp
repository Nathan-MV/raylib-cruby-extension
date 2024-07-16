#include "vec3.hpp"

VALUE rb_cVec3;

// RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
static VALUE rb_color_from_hsv(VALUE self) {
  Vector3 *vec3 = get_vec3(self);

  Color result = ColorFromHSV(vec3->x, vec3->y, vec3->z);

  return Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);
}

extern "C" void initializeVec3() {
  rb_cVec3 = rb_define_class("Vec3", rb_cObject);
  rb_define_alloc_func(rb_cVec3, rb_object_alloc<Vector3>);

  rb_define_method(rb_cVec3, "from_hsv", rb_color_from_hsv, 0);
}
