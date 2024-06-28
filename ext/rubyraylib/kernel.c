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

static VALUE rb_get_random_value(VALUE self, VALUE min_val, VALUE max_val) {
  int min = NUM2INT(min_val);
  int max = NUM2INT(max_val);

  int random = GetRandomValue(min, max);

  return INT2NUM(random);
}

void initializeKernel() {
  rb_define_module_function(rb_mKernel, "random", rb_get_random_value, 2);
  rb_define_module_function(rb_mKernel, "fib", rb_fibonacci, 1);
}
