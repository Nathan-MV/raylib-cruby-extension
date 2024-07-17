#ifndef RECT_H
#define RECT_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "color.hpp"

extern "C" void initializeRect();

inline RayRectangle* get_rect(VALUE obj) {
  RayRectangle *rect;
  Data_Get_Struct(obj, RayRectangle, rect);

  return rect;
}

#define RB_RECT_GETTER(name, member) \
	static VALUE name(VALUE self) { \
		RayRectangle *rect = get_rect(self); \
		\
		return DBL2NUM(rect->member); \
	}

#define RB_RECT_SETTER(name, member) \
	static VALUE name(VALUE self, VALUE value) { \
		RayRectangle *rect = get_rect(self); \
		rect->member = NUM2DBL(value); \
		return self; \
	}

#endif // RECT_H
