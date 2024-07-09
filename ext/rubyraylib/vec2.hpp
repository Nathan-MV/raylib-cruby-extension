#ifndef VEC2_H
#define VEC2_H

#include <new>
#include <ruby.h>
#include "raylib_values.hpp"

// Function declarations
extern VALUE rb_cVec2;
void initializeVec2();

inline Vector2* get_vec2(VALUE obj) {
  Vector2 *vec2;
  Data_Get_Struct(obj, Vector2, vec2);

  return vec2;
}

// Macro to define getter methods
#define RB_VEC2_GETTER(name, member) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		\
		return INT2NUM(vec2->member); \
	}

// Macro to define setter methods
#define RB_VEC2_SETTER(name, member) \
	static VALUE name(VALUE self, VALUE value) { \
		Vector2 *vec2 = get_vec2(self); \
		vec2->member = NUM2INT(value); \
		return self; \
	}

// Macro to define methods
#define RB_VEC2(name, func) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		*vec2 = func(*vec2); \
		return self; \
	}

// Macro to define methods for calculating length of Vec2
#define RB_VEC2_FLOAT(name, func) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		float result = func(*vec2); \
		return DBL2NUM(result); \
	}

// Macro to define func methods for Vec2
#define RB_VEC2_OTHER(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2 = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		*vec2 = func(*vec2, *other_vec2); \
		return self; \
	}

// Macro to define comparison methods for Vec2
#define RB_VEC2_OTHER_INT(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2_ptr = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		int result = func(*vec2_ptr, *other_vec2); \
		return INT2NUM(result); \
	}

// Macro to define methods for calculating distance between two Vec2
#define RB_VEC2_OTHER_FLOAT(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2_ptr = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		float result = func(*vec2_ptr, *other_vec2); \
		return DBL2NUM(result); \
	}

// Macro to define value func methods for Vec2
#define RB_VEC2_VALUE(name, func) \
	static VALUE name(VALUE self, VALUE value) { \
		Vector2 *vec2 = get_vec2(self); \
		float val = NUM2DBL(value); \
		*vec2 = func(*vec2, val); \
		return self; \
	}

#endif // VEC2_H