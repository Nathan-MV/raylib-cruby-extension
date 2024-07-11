#ifndef EASE_H
#define EASE_H

#include "ruby_values.hpp"
#include "raylib_values.hpp"

extern "C" void initializeEase();

// Macro to define easing methods
#define RB_EASE(name, func) \
static VALUE name(VALUE self, VALUE symbol, VALUE t, VALUE b, VALUE c, VALUE d) { \
  float t_val = NUM2DBL(t); \
  float b_val = NUM2DBL(b); \
  float c_val = NUM2DBL(c); \
  float d_val = NUM2DBL(d); \
  \
  float result; \
  \
  ID id = SYM2ID(symbol); \
  if (id == rb_intern("in")) { \
      result = func##In(t_val, b_val, c_val, d_val); \
  } else if (id == rb_intern("out")) { \
      result = func##Out(t_val, b_val, c_val, d_val); \
  } else if (id == rb_intern("inout")) { \
      result = func##InOut(t_val, b_val, c_val, d_val); \
  } else { \
      rb_raise(rb_eArgError, "Unknown easing type: %" PRIsVALUE, symbol); \
  } \
  \
  return DBL2NUM(result); \
}

#endif // EASE_H
