#include <vec3_bindings.h>

VALUE rb_cVec3;

// RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for a Color, hue [0..360], saturation/value [0..1]
static auto rb_color_from_hsv(VALUE self) {
  auto *vec3 = get_vec3(self);

  auto result = ColorFromHSV(vec3->x, vec3->y, vec3->z);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, &result);
}

extern "C" void Init_Vec3() {
  rb_cVec3 = rb_define_class_under(rb_mRL, "Vec3", rb_cObject);
  rb_define_alloc_func(rb_cVec3, rb_object_alloc<Vector3>);

  rb_define_method(rb_cVec3, "from_hsv", rb_color_from_hsv, 0);
}
