#include "image.hpp"

VALUE rb_cImage;

static void rb_image_free(void *ptr) {
  Image *img = static_cast<Image*>(ptr);
  if (img) {
    //UnloadImage(*img);
    delete img;
  }
}

static VALUE rb_image_alloc(VALUE klass) {
  Image* img = new (std::nothrow) Image();
  if (!img) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Image.");
    return Qnil;
  }

  return Data_Wrap_Struct(klass, NULL, rb_image_free, img);
}

static VALUE rb_image_initialize(VALUE self, VALUE fileName) {
  Image *img = get_image(self);
  const char *name = StringValueCStr(fileName);

  if (!img) {
    rb_raise(rb_eRuntimeError, "Image object is not initialized.");
    return Qnil;
  }

  *img = LoadImage(name);
  if (!img) {
    rb_raise(rb_eRuntimeError, "Failed to load image from file '%s'.", name);
    return Qnil;
  }

  return self;
}

static VALUE rb_unload_image(VALUE self) {
  Image *img = get_image(self);

  if (img) {
    UnloadImage(*img);
    delete img;
  }

  return Qnil;
}

void initializeImage() {
  rb_cImage = rb_define_class("Image", rb_cObject);

  rb_define_alloc_func(rb_cImage, rb_image_alloc);
  rb_define_method(rb_cImage, "initialize", rb_image_initialize, 1);
  rb_define_method(rb_cImage, "unload", rb_unload_image, 0);
}
