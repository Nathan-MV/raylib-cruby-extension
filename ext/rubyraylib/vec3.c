#include "vec3.h"

VALUE rb_cVector3;

static void rb_vec3_free(void *ptr) {
  free(ptr);
}

static VALUE rb_vec3_alloc(VALUE klass) {
  Vector3 *vec3 = ALLOC(Vector3);
  return Data_Wrap_Struct(klass, NULL, rb_vec3_free, vec3);
}

static Vector3* get_vec3_from_value(VALUE obj) {
  Vector3 *vec3;
  Data_Get_Struct(obj, Vector3, vec3);
  return vec3;
}

static VALUE rb_color_from_hsv(VALUE self) {
  Vector3 *vec3 = get_vec3_from_value(self);

  Color result = ColorFromHSV(vec3->x, vec3->y, vec3->z);

  VALUE rb_result = Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);

  return rb_result;
}

void initializeVec3() {
  rb_cVector3 = rb_define_class("Vec3", rb_cObject);

  rb_define_alloc_func(rb_cVector3, rb_vec3_alloc);

  rb_define_method(rb_cVector3, "from_hsv", rb_color_from_hsv, 0);
}