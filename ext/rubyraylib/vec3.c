#include "vec3.h"

VALUE rb_cVec3;

static void rb_vec3_free(void *ptr) {
  Vector3 *vec3 = (Vector3 *)ptr;

  if (vec3 != NULL) {
    free(vec3);
  }
}

static VALUE rb_vec3_alloc(VALUE klass) {
  Vector3 *vec3 = ALLOC(Vector3);

  if (vec3 != NULL) {
    return Data_Wrap_Struct(klass, NULL, rb_vec3_free, vec3);
  } else {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vector3.");
  }
}

static VALUE rb_color_from_hsv(VALUE self) {
  Vector3 *vec3 = (Vector3 *)DATA_PTR(self);
  Color result = ColorFromHSV(vec3->x, vec3->y, vec3->z);
  VALUE rb_result = Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);

  return rb_result;
}

void initializeVec3() {
  rb_cVec3 = rb_define_class("Vec3", rb_cObject);

  rb_define_alloc_func(rb_cVec3, rb_vec3_alloc);
  rb_define_method(rb_cVec3, "from_hsv", rb_color_from_hsv, 0);
}