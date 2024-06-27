#include "vec4.h"

VALUE rb_cVec4;

static void rb_vec4_free(void *ptr) {
  Vector4 *vec4 = (Vector4 *)ptr;

  if (vec4 != NULL) {
    free(vec4);
  }
}

static VALUE rb_vec4_alloc(VALUE klass) {
  Vector4 *vec4 = ALLOC(Vector4);

  if (vec4 != NULL) {
    return Data_Wrap_Struct(klass, NULL, rb_vec4_free, vec4);
  } else {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vector4.");
  }
}

static VALUE rb_color_from_normalized(VALUE self) {
  Vector4 *vec4 = (Vector4 *)DATA_PTR(self);
  Color result = ColorFromNormalized(*vec4);
  VALUE rb_result = Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);

  return rb_result;
}

void initializeVec4() {
  rb_cVec4 = rb_define_class("Vec4", rb_cObject);

  rb_define_alloc_func(rb_cVec4, rb_vec4_alloc);

  rb_define_method(rb_cVec4, "from_normalize", rb_color_from_normalized, 0);
}