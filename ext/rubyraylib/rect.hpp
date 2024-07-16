#ifndef RECT_H
#define RECT_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "color.hpp"

extern "C" void initializeRect();

inline Rectangle* get_rect(VALUE obj) {
  Rectangle *rect;
  Data_Get_Struct(obj, Rectangle, rect);

  return rect;
}

#define RB_RECT_GETTER(name, member) \
	static VALUE name(VALUE self) { \
		Rectangle *rect = get_rect(self); \
		\
		return DBL2NUM(rect->member); \
	}

#define RB_RECT_SETTER(name, member) \
	static VALUE name(VALUE self, VALUE value) { \
		Rectangle *rect = get_rect(self); \
		rect->member = NUM2DBL(value); \
		return self; \
	}

#endif // RECT_H
