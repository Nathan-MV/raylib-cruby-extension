#ifndef IMAGE_H
#define IMAGE_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"

extern VALUE rb_cImage;

extern "C" void initializeImage();

inline Image* get_image(VALUE obj) {
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
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_image_free<T>, obj);
  } catch (const std::bad_alloc& e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

#endif // IMAGE_H
