#include "texture.h"

static VALUE texture_alloc(VALUE klass) {
  Texture *texture;
  VALUE obj = Data_Make_Struct(klass, Texture, 0, -1, texture);
  return obj;
}

void initializeTexture() {
  VALUE rb_cTexture = rb_define_class("Texture", rb_cObject);

  rb_define_alloc_func(rb_cTexture, texture_alloc);
}
