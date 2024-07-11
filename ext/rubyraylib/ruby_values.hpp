#ifndef RUBY_VALUES_H
#define RUBY_VALUES_H

#include <ruby.h>
#include <typeinfo>
#include <type_traits>
#include "vec2.hpp"
#include "image.hpp"

template <typename T>
void rb_object_free(void *ptr) {
  delete static_cast<T *>(ptr);
}

template <typename T>
VALUE rb_object_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_object_free<T>, obj);
  } catch (const std::bad_alloc& e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

// self

#define RB_METHOD(name, func) \
  static VALUE name(VALUE self) { \
    func(); \
    return self; \
  }

template<void (*Func)()>
static VALUE rb_method(VALUE self) {
  Func();
  return Qnil;
}

#define RB_METHOD_ARG_STR(name, func)  \
	static VALUE name(VALUE self, VALUE text) { \
		const char *txt = StringValueCStr(text); \
		func(txt); \
		return self; \
	}

template<void (*Func)(const char*)>
static VALUE rb_method_arg_string(VALUE self, VALUE value) {
  const char *val = StringValueCStr(value);
  Func(val);
  return Qnil;
}

#define RB_METHOD_ARG_INT(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		int val = NUM2INT(value); \
		func(val); \
		return self; \
	}

#define RB_METHOD_ARG_INT_2(name, func)  \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		int val1 = NUM2INT(value1); \
		int val2 = NUM2INT(value2); \
		func(val1, val2); \
		return self; \
	}

#define RB_METHOD_ARG_INT_FLOAT_2(name, func)  \
	static VALUE name(VALUE self, VALUE value1, VALUE value2, VALUE value3) { \
		int val1 = NUM2INT(value1); \
		float val2 = NUM2DBL(value2); \
    float val3 = NUM2DBL(value3); \
		func(val1, val2, val3); \
		return self; \
	}

#define RB_METHOD_ARG_UINT(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		unsigned int val = NUM2UINT(value); \
		func(val); \
		return self; \
	}

#define RB_METHOD_ARG_UINT_2(name, func)  \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		unsigned int val1 = NUM2UINT(value1); \
		unsigned int val2 = NUM2UINT(value2); \
		func(val1, val2); \
		return self; \
	}

#define RB_METHOD_ARG_FLOAT(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		float val = NUM2DBL(value); \
		func(val); \
		return self; \
	}

#define RB_METHOD_ARG_FLOAT_2(name, func)  \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		float val1 = NUM2DBL(value1); \
		float val2 = NUM2DBL(value2); \
		func(val1, val2); \
		return self; \
	}

#define RB_METHOD_ARG_IMAGE(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		Image *val = get_image(value); \
		func(*val); \
		return self; \
	}

// Boolean

#define RB_METHOD_BOOL(name, func) \
	static VALUE name(VALUE self) { \
  	return func() ? Qtrue : Qfalse; \
	}

#define RB_METHOD_BOOL_ARG_INT(name, func) \
  static VALUE name(VALUE self, VALUE value) { \
	int val = NUM2INT(value); \
  	return func(val) ? Qtrue : Qfalse; \
  }

#define RB_METHOD_BOOL_ARG_INT_2(name, func) \
  static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
	int val1 = NUM2INT(value1); \
  int val2 = NUM2INT(value2); \
  	return func(val1, val2) ? Qtrue : Qfalse; \
  }

#define RB_METHOD_BOOL_ARG_UINT(name, func) \
	static VALUE name(VALUE self, VALUE value) { \
	unsigned int val = NUM2UINT(value); \
  	return func(val) ? Qtrue : Qfalse; \
	}

// int

#define RB_METHOD_INT(name, func) \
	static VALUE name(VALUE self) { \
		int result = func(); \
		return INT2NUM(result); \
	}

#define RB_METHOD_INT_ARG(name, func) \
	static VALUE name(VALUE self, VALUE value) { \
		int val = NUM2INT(value); \
		int result = func(val); \
		return INT2NUM(result); \
	}

#define RB_METHOD_INT_ARG_2(name, func) \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		int val1 = NUM2INT(value1); \
		int val2 = NUM2INT(value2); \
		int result = func(val1, val2); \
		return INT2NUM(result); \
	}

#define RB_METHOD_INT_ARG_STR(name, func)  \
	static VALUE name(VALUE self, VALUE text) { \
		const char *txt = StringValueCStr(text); \
		int result = func(txt); \
		return INT2NUM(result); \
	}

// unsigned int

#define RB_METHOD_UINT(name, func) \
	static VALUE name(VALUE self) { \
		int result = func(); \
		return UINT2NUM(result); \
	}

// float

#define RB_METHOD_FLOAT(name, func) \
	static VALUE name(VALUE self) { \
		float result = func(); \
		return DBL2NUM(result); \
	}

#define RB_METHOD_FLOAT_ARG(name, func) \
	static VALUE name(VALUE self, VALUE value) { \
		float val = NUM2DBL(value); \
		float result = func(val); \
		return DBL2NUM(result); \
	}

#define RB_METHOD_FLOAT_ARG_2(name, func) \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		float val1 = NUM2DBL(value1); \
		float val2 = NUM2DBL(value2); \
		float result = func(val1, val2); \
		return DBL2NUM(result); \
	}

#define RB_METHOD_FLOAT_ARG_INT_2(name, func) \
	static VALUE name(VALUE self, VALUE value1, VALUE value2) { \
		int val1 = NUM2INT(value1); \
		int val2 = NUM2INT(value2); \
		float result = func(val1, val2); \
		return DBL2NUM(result); \
	}

// String

#define RB_METHOD_STR(name, func)  \
	static VALUE name(VALUE self) { \
		const char *text = func(); \
		return rb_str_new_cstr(text); \
	}

#define RB_METHOD_STR_ARG_INT(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		int val = NUM2INT(value); \
		const char *result = func(val); \
		return rb_str_new_cstr(result); \
	}

// Wrappers

#define RB_METHOD_VEC2(name, func)  \
	static VALUE name(VALUE self) { \
		Vector2 result = func(); \
		return Data_Wrap_Struct(rb_cVec2, NULL, NULL, &result); \
	}

#define RB_METHOD_VEC2_ARG_INT(name, func)  \
	static VALUE name(VALUE self, VALUE value) { \
		int val = NUM2INT(value); \
		Vector2 result = func(val); \
		return Data_Wrap_Struct(rb_cVec2, NULL, NULL, &result); \
	}

#endif // RUBY_VALUES_H
