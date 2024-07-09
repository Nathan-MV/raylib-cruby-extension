#include "vec3.hpp"

VALUE rb_cVec3;

static void rb_vec3_free(void *ptr) {
  delete static_cast<Vector3*>(ptr);
}

static VALUE rb_vec3_alloc(VALUE klass) {
  Vector3* vec3 = new (std::nothrow) Vector3();
  if (!vec3) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vec3.");
    return Qnil;
  }

  return Data_Wrap_Struct(klass, NULL, rb_vec3_free, vec3);
}

Vector3* get_vec3(VALUE obj) {
  Vector3 *vec3;
  Data_Get_Struct(obj, Vector3, vec3);

  return vec3;
}

static VALUE rb_color_from_hsv(VALUE self) {
  Vector3 *vec3 = get_vec3(self);

  Color result = ColorFromHSV(vec3->x, vec3->y, vec3->z);

  return Data_Wrap_Struct(rb_cColor, NULL, NULL, &result);
}

void initializeVec3() {
  rb_cVec3 = rb_define_class("Vec3", rb_cObject);

  rb_define_alloc_func(rb_cVec3, rb_vec3_alloc);
  rb_define_method(rb_cVec3, "from_hsv", rb_color_from_hsv, 0);
}
