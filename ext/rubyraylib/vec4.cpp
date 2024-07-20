#include "vec4.hpp"

VALUE rb_cVec4;

// RLAPI Vector4 ColorNormalize(Color color);                                  // Get Color normalized as float [0..1]
static VALUE rb_color_from_normalized(VALUE self) {
  Vector4 *vec4 = get_vec4(self);
  Color result = ColorFromNormalized(*vec4);

  return Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);
}

extern "C" void initializeVec4() {
  rb_cVec4 = rb_define_class_under(rb_mRL, "Vec4", rb_cObject);
  rb_define_alloc_func(rb_cVec4, rb_object_alloc<Vector4>);

  rb_define_method(rb_cVec4, "from_normalize", rb_color_from_normalized, 0);
}
