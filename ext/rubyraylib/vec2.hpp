#ifndef VEC2_H
#define VEC2_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "texture.hpp"

extern VALUE rb_cVec2;
extern "C" void initializeVec2();

inline Vector2* get_vec2(VALUE obj) {
  Vector2 *vec2;
  Data_Get_Struct(obj, Vector2, vec2);

  return vec2;
}

#define RB_VEC2_GETTER(name, member) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		\
		return INT2NUM(vec2->member); \
	}

#define RB_VEC2_SETTER(name, member) \
	static VALUE name(VALUE self, VALUE value) { \
		Vector2 *vec2 = get_vec2(self); \
		vec2->member = NUM2INT(value); \
		return self; \
	}

#define RB_VEC2(name, func) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		*vec2 = func(*vec2); \
		return self; \
	}

#define RB_VEC2_FLOAT(name, func) \
	static VALUE name(VALUE self) { \
		Vector2 *vec2 = get_vec2(self); \
		float result = func(*vec2); \
		return DBL2NUM(result); \
	}

#define RB_VEC2_OTHER(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2 = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		*vec2 = func(*vec2, *other_vec2); \
		return self; \
	}

#define RB_VEC2_OTHER_INT(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2_ptr = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		int result = func(*vec2_ptr, *other_vec2); \
		return INT2NUM(result); \
	}

#define RB_VEC2_OTHER_FLOAT(name, func) \
	static VALUE name(VALUE self, VALUE other) { \
		Vector2 *vec2_ptr = get_vec2(self); \
		Vector2 *other_vec2 = get_vec2(other); \
		float result = func(*vec2_ptr, *other_vec2); \
		return DBL2NUM(result); \
	}

#define RB_VEC2_SCALAR(name, func1, func2) \
  static VALUE name(VALUE self, VALUE value) { \
    Vector2 *vec2 = get_vec2(self); \
    if (rb_obj_is_kind_of(value, rb_cVec2)) { \
      Vector2 *val = get_vec2(value); \
      *vec2 = func1(*vec2, *val); \
    } else { \
      float val = NUM2DBL(value); \
      *vec2 = func2(*vec2, val); \
    } \
    return self; \
  }

#endif // VEC2_H
