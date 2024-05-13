#include "image.h"

static VALUE image_alloc(VALUE klass) {
  Image *img;
  VALUE obj = Data_Make_Struct(klass, Image, 0, -1, img);
  return obj;
}

void initializeImage() {
  VALUE rb_cImage = rb_define_class("Image", rb_cObject);

  rb_define_alloc_func(rb_cImage, image_alloc);
}
