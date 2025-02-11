#ifndef RUBY_VALUES_H
#define RUBY_VALUES_H

#include <type_traits>
#include <typeinfo>
#include "ruby.h"
#include "ruby/encoding.h"
#include "ruby/version.h"
#include "bitmap_bindings.h"
#include "color_bindings.h"
#include "font_bindings.h"
#include "render_texture_bindings.h"
#include "shader_bindings.h"
#include "sprite_bindings.h"
#include "rect_bindings.h"
#include "table_bindings.h"
#include "vec2_bindings.h"
#include "vec3_bindings.h"
#include "vec4_bindings.h"

template <class T> auto rb_object_free(void *ptr) { delete static_cast<T *>(ptr); }

template <class T> auto rb_object_alloc(VALUE klass) {
  try {
    T *obj = new T();
    return Data_Wrap_Struct(klass, nullptr, rb_object_free<T>, obj);
  } catch (const std::bad_alloc &e) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for %s.", typeid(T).name());
    return Qnil;
  }
}

// Convert Ruby array to C int array
static int *get_int_array(VALUE rb_array) {
  if (TYPE(rb_array) != T_ARRAY) {
    rb_raise(rb_eTypeError, "Expected an array");
  }

  long length = RARRAY_LEN(rb_array);
  if (length == 0) {
    return NULL;  // No need to allocate memory for an empty array
  }

  int *int_array = (int *)malloc(length * sizeof(int));  // Use malloc for heap allocation
  if (int_array == NULL) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory");
  }

  for (long i = 0; i < length; i++) {
    int_array[i] = NUM2INT(RARRAY_AREF(rb_array, i));  // Use RARRAY_AREF for direct access
  }

  return int_array;  // Safe to return as it's allocated on the heap
}

// Base macro to define a Ruby method
#define RB_METHOD(name, func)    \
  static auto name(VALUE self) { \
    func();                      \
    return self;                 \
  }

// Common macro for single argument methods
#define RB_METHOD_ARG(name, func, ret, argtype) \
  static auto name(VALUE self, VALUE arg) {     \
    func(argtype(arg));                         \
    return ret;                                 \
  }

// Specific argument type macros
#define RB_METHOD_ARG_STR(name, func, ret) RB_METHOD_ARG(name, func, ret, StringValueCStr)
#define RB_METHOD_ARG_INT(name, func, ret) RB_METHOD_ARG(name, func, ret, NUM2INT)
#define RB_METHOD_ARG_UINT(name, func, ret) RB_METHOD_ARG(name, func, ret, NUM2UINT)
#define RB_METHOD_ARG_FLOAT(name, func, ret) RB_METHOD_ARG(name, func, ret, NUM2DBL)
#define RB_METHOD_ARG_IMG(name, func, ret) RB_METHOD_ARG(name, func, ret, *get_image)

// Common macro for two argument methods
#define RB_METHOD_ARG_2(name, func, ret, argtype1, argtype2) \
  static auto name(VALUE self, VALUE arg1, VALUE arg2) {     \
    func(argtype1(arg1), argtype2(arg2));                    \
    return ret;                                              \
  }

// Specific argument type macro for two arguments
#define RB_METHOD_ARG_INT_INT(name, func, ret) RB_METHOD_ARG_2(name, func, ret, NUM2INT, NUM2INT)
#define RB_METHOD_ARG_FLOAT_FLOAT(name, func, ret) RB_METHOD_ARG_2(name, func, ret, NUM2DBL, NUM2DBL)
#define RB_METHOD_ARG_IMG_INT(name, func, ret) \
  RB_METHOD_ARG_2(name, func, ret, get_image, NUM2INT)

// Common macro for three argument methods
#define RB_METHOD_ARG_3(name, func, ret, argtype1, argtype2, argtype3) \
  static auto name(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3) {  \
    func(argtype1(arg1), argtype2(arg2), argtype3(arg3));              \
    return ret;                                                       \
  }

// Specific argument type macro for three arguments
#define RB_METHOD_ARG_INT_INT_INT(name, func, ret) \
  RB_METHOD_ARG_3(name, func, ret, NUM2INT, NUM2INT, NUM2INT)
#define RB_METHOD_ARG_INT_INT_STR(name, func, ret) \
  RB_METHOD_ARG_3(name, func, ret, NUM2INT, NUM2INT, StringValueCStr)

// Common macro for four argument methods
#define RB_METHOD_ARG_4(name, func, ret, argtype1, argtype2, argtype3, argtype4) \
  static auto name(VALUE self, VALUE arg1, VALUE arg2, VALUE arg3, VALUE arg4) {  \
    func(argtype1(arg1), argtype2(arg2), argtype3(arg3), argtype4(arg4));              \
    return ret;                                                       \
  }

#define RB_METHOD_ARG_INT_FLOAT_FLOAT_FLOAT(name, func, ret) \
  RB_METHOD_ARG_4(name, func, ret, NUM2INT, NUM2DBL, NUM2DBL, NUM2DBL)

// Base macro to define a Ruby method with result
#define RB_METHOD_RESULT(name, func, ret)    \
  static auto name(VALUE self) { \
    auto result = func();                      \
    return ret(result);                 \
  }

#define RB_METHOD_INT(name, func) RB_METHOD_RESULT(name, func, INT2NUM)
#define RB_METHOD_FLOAT(name, func) RB_METHOD_RESULT(name, func, DBL2NUM)

// Base macro to define a Ruby method with result constant
#define RB_METHOD_RESULT_CONST(name, func, ret) \
  static auto name(VALUE self) {                \
    const auto *result = func();                \
    return ret(result);                         \
  }

#define RB_METHOD_CONST_STR(name, func) RB_METHOD_RESULT_CONST(name, func, rb_str_new_cstr)

// Common macro for single argument methods with result
#define RB_METHOD_RESULT_ARG(name, func, ret, argtype) \
  static auto name(VALUE self, VALUE arg) {     \
    auto result = func(argtype(arg));                         \
    return ret(result);                                 \
  }

// Specific argument type macros for one argument with result
#define RB_METHOD_INT_ARG(name, func) RB_METHOD_RESULT_ARG(name, func, INT2NUM, NUM2INT)

#define RB_METHOD_INT_ARG_STR(name, func) \
  RB_METHOD_RESULT_ARG(name, func, INT2NUM, StringValueCStr)

// Common macro for single argument methods with result constant
#define RB_METHOD_RESULT_CONST_ARG(name, func, ret, argtype) \
  static auto name(VALUE self, VALUE arg) {                  \
    const auto *result = func(argtype(arg));                 \
    return ret(result);                                      \
  }

#define RB_METHOD_CONST_STR_ARG_INT(name, func) \
  RB_METHOD_RESULT_CONST_ARG(name, func, rb_str_new_cstr, NUM2INT)

// Common macro for two argument methods with result
#define RB_METHOD_RESULT_ARG_2(name, func, ret, argtype1, argtype2) \
  static auto name(VALUE self, VALUE arg1, VALUE arg2) {     \
    auto result = func(argtype1(arg1), argtype2(arg2));                    \
    return ret(result);                                              \
  }

// Specific argument type macros for two arguments with result
#define RB_METHOD_INT_ARG_INT_INT(name, func) \
  RB_METHOD_RESULT_ARG_2(name, func, INT2NUM, NUM2INT, NUM2INT)

#define RB_METHOD_FLOAT_ARG_INT_INT(name, func) \
  RB_METHOD_RESULT_ARG_2(name, func, DBL2NUM, NUM2INT, NUM2INT)

// Boolean

#define RB_METHOD_BOOL(name, func) \
  static auto name(VALUE self) { return func() ? Qtrue : Qfalse; }

#define RB_METHOD_BOOL_ARG_INT(name, func)    \
  static auto name(VALUE self, VALUE value) { \
    auto val = NUM2INT(value);                \
    return func(val) ? Qtrue : Qfalse;        \
  }

#define RB_METHOD_BOOL_ARG_INT_INT(name, func)                 \
  static auto name(VALUE self, VALUE value1, VALUE value2) { \
    auto val1 = NUM2INT(value1);                             \
    auto val2 = NUM2INT(value2);                             \
    return func(val1, val2) ? Qtrue : Qfalse;                \
  }

#define RB_METHOD_BOOL_ARG_UINT(name, func)   \
  static auto name(VALUE self, VALUE value) { \
    auto val = NUM2UINT(value);               \
    return func(val) ? Qtrue : Qfalse;        \
  }

// Wrappers

#define RB_METHOD_VEC2(name, func)                                    \
  static auto name(VALUE self) {                                      \
    auto result = func();                                             \
    return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, &result); \
  }

#define RB_METHOD_VEC2_ARG_INT(name, func)                                     \
  static auto name(VALUE self, VALUE value) {                                  \
    auto val = NUM2INT(value);                                                 \
    auto result = func(val);                                                   \
    return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, &result); \
  }

#endif  // RUBY_VALUES_H
