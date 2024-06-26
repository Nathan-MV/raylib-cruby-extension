#include "vector4.h"

VALUE rb_cVector4;

static void rb_vec4_free(void *ptr) {
  free(ptr);
}

static VALUE rb_vec4_alloc(VALUE klass) {
  Vector4 *vec4 = ALLOC(Vector4);
  return Data_Wrap_Struct(klass, NULL, rb_vec4_free, vec4);
}

static VALUE rb_color_from_normalized(VALUE self) {
  Vector4 *vec4;
  Data_Get_Struct(self, Vector4, vec4);

  Color result = ColorFromNormalized(*vec4);

  VALUE rb_result = Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);

  return rb_result;
}

void initializeVec4() {
  rb_cVector4 = rb_define_class("Vec4", rb_cObject);

  rb_define_alloc_func(rb_cVector4, rb_vec4_alloc);

  rb_define_method(rb_cVector4, "from_normalize", rb_color_from_normalized, 0);
}