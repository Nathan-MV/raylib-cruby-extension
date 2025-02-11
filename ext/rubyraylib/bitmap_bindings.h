#ifndef BITMAP_H
#define BITMAP_H

#include <stdio.h>
#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cBitmap;
extern "C" void Init_Bitmap();

extern "C" inline Image* get_image(VALUE obj) {
  Image *img;
  Data_Get_Struct(obj, Image, img);

  return img;
}

template <typename T>
void rb_image_free(void *ptr) {
  T *obj = static_cast<T *>(ptr);

  UnloadImage(*obj);
  delete obj;
}

template <typename T>
VALUE rb_image_alloc(VALUE klass) {
  T *obj = (T *)malloc(sizeof(T));

  if (!obj) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());

    return Qnil;
  }

  return Data_Wrap_Struct(klass, nullptr, rb_image_free<T>, obj);
}

#endif // BITMAP_H
