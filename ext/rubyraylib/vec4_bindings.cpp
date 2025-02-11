#include <vec4_bindings.h>

VALUE rb_cVec4;

// RLAPI Vector4 ColorNormalize(Color color);                                  // Get Color normalized as float [0..1]
static auto rb_color_from_normalized(VALUE self) {
  auto *vec4 = get_vec4(self);
  auto result = ColorFromNormalized(*vec4);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, &result);
}

extern "C" void Init_Vec4() {
  rb_cVec4 = rb_define_class_under(rb_mRL, "Vec4", rb_cObject);
  rb_define_alloc_func(rb_cVec4, rb_object_alloc<Vector4>);

  rb_define_method(rb_cVec4, "from_normalize", rb_color_from_normalized, 0);
}
