#include "kernel.h"

static int fibonacci(int n) {
  if (n <= 1)
    return n;

  return fibonacci(n - 1) + fibonacci(n - 2);
}

static VALUE rb_fibonacci(VALUE self, VALUE num) {
  int n = NUM2INT(num);
  int result = fibonacci(n);

  return INT2NUM(result);
}

static VALUE rb_get_random_value(VALUE self, VALUE min, VALUE max) {
  int minValue = NUM2INT(min);
  int maxValue = NUM2INT(max);
  int randomValue = GetRandomValue(minValue, maxValue);

  return INT2NUM(randomValue);
}

void initializeKernel() {
  rb_define_module_function(rb_mKernel, "random", rb_get_random_value, 2);
  rb_define_module_function(rb_mMath, "fib", rb_fibonacci, 1);
}
