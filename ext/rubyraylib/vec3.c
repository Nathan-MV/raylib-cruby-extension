#include "vec3.h"

VALUE rb_cVector3;

static void rb_vec3_free(void *ptr) {
  free(ptr);
}

static VALUE rb_vec3_alloc(VALUE klass) {
  Vector3 *vec3 = ALLOC(Vector3);
  return Data_Wrap_Struct(klass, NULL, rb_vec3_free, vec3);
}

void initializeVec3() {
  rb_cVector3 = rb_define_class("Vec3", rb_cObject);

  rb_define_alloc_func(rb_cVector3, rb_vec3_alloc);
}