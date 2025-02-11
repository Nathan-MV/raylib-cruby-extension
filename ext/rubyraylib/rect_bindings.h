#ifndef MRI_RECT_H
#define MRI_RECT_H

#include "ruby_values.h"
#include "raylib_values.h"
#include "rect.h"

extern VALUE rb_cRect;
extern "C" void Init_Rect();

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

#endif // MRI_RECT_H
