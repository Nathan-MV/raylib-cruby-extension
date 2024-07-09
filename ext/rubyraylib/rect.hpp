#ifndef RECT_H
#define RECT_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"

Rectangle* get_rect(VALUE obj);
void initializeRect();

#endif // RECT_H
