#include "image.h"

static void rb_image_free(void *ptr) {
  Image *image = (Image *)ptr;
  if (image) {
    UnloadImage(*image);
    free(image);
  }
}

static VALUE rb_image_alloc(VALUE klass) {
  Image *image = ALLOC(Image);
  return Data_Wrap_Struct(klass, NULL, rb_image_free, image);
}

void initializeImage() {
  VALUE rb_cImage = rb_define_class("Image", rb_cObject);

  rb_define_alloc_func(rb_cImage, rb_image_alloc);
}
