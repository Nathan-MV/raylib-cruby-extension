#include "image.h"

VALUE rb_cImage;

static void rb_image_free(void *ptr) {
  if (ptr) {
    Image *img = (Image *)ptr;
    free(img);
  }
}

static VALUE rb_image_alloc(VALUE klass) {
  Image *img = ALLOC(Image);

  if (!img) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Image.");
  }

  return Data_Wrap_Struct(klass, NULL, rb_image_free, img);
}

Image* get_image(VALUE obj) {
  Image *img;
  Data_Get_Struct(obj, Image, img);

  return img;
}

static VALUE rb_image_initialize(VALUE self, VALUE fileName) {
  Image *img = get_image(self);
  const char *file_name_str = StringValueCStr(fileName);

  *img = LoadImage(file_name_str);

  return self;
}

static VALUE rb_unload_image(VALUE self) {
  Image *img = get_image(self);

  if (img != NULL) {
    UnloadImage(*img);
    free(img);
  }

  return Qnil;
}

void initializeImage() {
  rb_cImage = rb_define_class("Image", rb_cObject);

  rb_define_alloc_func(rb_cImage, rb_image_alloc);
  rb_define_method(rb_cImage, "initialize", rb_image_initialize, 1);
  rb_define_method(rb_cImage, "unload", rb_unload_image, 0);
}