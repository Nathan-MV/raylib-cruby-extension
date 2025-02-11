#ifndef MRI_VEC2_H
#define MRI_VEC2_H

#include <algorithm>
#include <string>
#include <tuple>
#include "ruby_values.h"
#include "vec2.h"
#include "raylib_values.h"

extern VALUE rb_cVec2;
extern "C" void Init_Vec2();

inline auto *get_vec2(VALUE obj) {
  Vector2 *vec2;
  Data_Get_Struct(obj, Vector2, vec2);

  return vec2;
}

#define RB_VEC2_GETTER(name, member) \
  static auto name(VALUE self) {     \
    auto *vec2 = get_vec2(self);     \
                                     \
    return INT2NUM(vec2->member);    \
  }

#define RB_VEC2_SETTER(name, member)          \
  static auto name(VALUE self, VALUE value) { \
    auto *vec2 = get_vec2(self);              \
    vec2->member = NUM2INT(value);            \
    return self;                              \
  }

#define RB_VEC2(name, func)      \
  static auto name(VALUE self) { \
    auto *vec2 = get_vec2(self); \
    *vec2 = func(*vec2);         \
    return self;                 \
  }

#define RB_VEC2_FLOAT(name, func) \
  static auto name(VALUE self) {  \
    auto *vec2 = get_vec2(self);  \
    auto result = func(*vec2);    \
    return DBL2NUM(result);       \
  }

#define RB_VEC2_OTHER(name, func)             \
  static auto name(VALUE self, VALUE other) { \
    auto *vec2 = get_vec2(self);              \
    auto *other_vec2 = get_vec2(other);       \
    *vec2 = func(*vec2, *other_vec2);         \
    return self;                              \
  }

#define RB_VEC2_OTHER_INT(name, func)           \
  static auto name(VALUE self, VALUE other) {   \
    auto *vec2_ptr = get_vec2(self);            \
    auto *other_vec2 = get_vec2(other);         \
    auto result = func(*vec2_ptr, *other_vec2); \
    return INT2NUM(result);                     \
  }

#define RB_VEC2_OTHER_FLOAT(name, func)         \
  static auto name(VALUE self, VALUE other) {   \
    auto *vec2_ptr = get_vec2(self);            \
    auto *other_vec2 = get_vec2(other);         \
    auto result = func(*vec2_ptr, *other_vec2); \
    return DBL2NUM(result);                     \
  }

#define RB_VEC2_SCALAR(name, func1, func2)    \
  static auto name(VALUE self, VALUE value) { \
    auto *vec2 = get_vec2(self);              \
    if (rb_obj_is_kind_of(value, rb_cVec2)) { \
      auto *val = get_vec2(value);            \
      *vec2 = func1(*vec2, *val);             \
    } else {                                  \
      auto val = NUM2DBL(value);              \
      *vec2 = func2(*vec2, val);              \
    }                                         \
    return self;                              \
  }

#endif  // MRI_VEC2_H
