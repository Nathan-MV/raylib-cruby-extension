#include "image.hpp"

VALUE rb_cImage;

static VALUE rb_image_initialize(VALUE self, VALUE fileName) {
  Image *img = get_image(self);
  const char *name = StringValueCStr(fileName);

  *img = LoadImage(name);

  return self;
}

static VALUE rb_unload_image(VALUE self) {
  Image *img = get_image(self);

  if (img != nullptr) {
    UnloadImage(*img);
    delete img;
  }

  return Qnil;
}

extern "C" void initializeImage() {
  rb_cImage = rb_define_class("Image", rb_cObject);
  rb_define_alloc_func(rb_cImage, rb_object_alloc<Image>);

  rb_define_method(rb_cImage, "initialize", rb_image_initialize, 1);
  rb_define_method(rb_cImage, "unload", rb_unload_image, 0);
}
