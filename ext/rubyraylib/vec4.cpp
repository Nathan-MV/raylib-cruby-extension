#include "vec4.hpp"

VALUE rb_cVec4;

static void rb_vec4_free(void *ptr) {
  delete static_cast<Vector4*>(ptr);
}

static VALUE rb_vec4_alloc(VALUE klass) {
  Vector4* vec4 = new (std::nothrow) Vector4();
  if (!vec4) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vec4.");
    return Qnil;
  }

  return Data_Wrap_Struct(klass, NULL, rb_vec4_free, vec4);
}

Vector4* get_vec4(VALUE obj) {
  Vector4 *vec4;
  Data_Get_Struct(obj, Vector4, vec4);

  return vec4;
}

static VALUE rb_color_from_normalized(VALUE self) {
  Vector4 *vec4 = get_vec4(self);
  Color result = ColorFromNormalized(*vec4);

  return Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);
}

void initializeVec4() {
  rb_cVec4 = rb_define_class("Vec4", rb_cObject);

  rb_define_alloc_func(rb_cVec4, rb_vec4_alloc);

  rb_define_method(rb_cVec4, "from_normalize", rb_color_from_normalized, 0);
}
