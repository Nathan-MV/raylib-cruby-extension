#include "image.h"

VALUE rb_cImage;

static void rb_image_free(void *ptr)
{
  Image *img = (Image *)ptr;

  if (img != NULL)
  {
    free(img);
  }
}

static VALUE rb_image_alloc(VALUE klass)
{
  Image *img = ALLOC(Image);

  if (img != NULL)
  {
    return Data_Wrap_Struct(klass, NULL, rb_image_free, img);
  }
  else
  {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Image.");
  }
}

static VALUE rb_image_initialize(VALUE self, VALUE fileName)
{
  const char *file_name_str = StringValueCStr(fileName);

  Image *img = ALLOC(Image);
  *img = LoadImage(file_name_str);

  return Data_Wrap_Struct(rb_cImage, NULL, rb_image_free, img);
}

static VALUE rb_load_image(VALUE self, VALUE fileName)
{
  const char *file_name_str = StringValueCStr(fileName);

  Image *img = ALLOC(Image);
  *img = LoadImage(file_name_str);

  return Data_Wrap_Struct(rb_cImage, NULL, rb_image_free, img);
}

static VALUE rb_unload_image(VALUE self, VALUE image)
{
  Image *img = (Image *)DATA_PTR(image);

  if (img != NULL)
  {
    UnloadImage(*img);
    free(img);
  }

  return Qnil;
}

void initializeImage()
{
  rb_cImage = rb_define_class("Image", rb_cObject);

  rb_define_alloc_func(rb_cImage, rb_image_alloc);
  rb_define_method(rb_cImage, "initialize", rb_image_initialize, 1);
  rb_define_singleton_method(rb_cImage, "load", rb_load_image, 1);
  rb_define_singleton_method(rb_cImage, "unload", rb_unload_image, 1);
}