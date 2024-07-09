#ifndef IMAGE_H
#define IMAGE_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"

extern VALUE rb_cImage;
void initializeImage();

inline Image* get_image(VALUE obj) {
  Image *img;
  Data_Get_Struct(obj, Image, img);
  return img;
}

#endif // IMAGE_H
