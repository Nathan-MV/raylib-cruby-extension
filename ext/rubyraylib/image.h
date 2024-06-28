#ifndef IMAGE_H
#define IMAGE_H

#include "ruby.h"
#include "raylib_values.h"

extern VALUE rb_cImage;
Image* get_image(VALUE obj);
void initializeImage();

#endif // IMAGE_H
