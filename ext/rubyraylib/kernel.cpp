#include "kernel.hpp"

static int fibonacci(int n) {
  if (n <= 1)
    return n;

  return fibonacci(n - 1) + fibonacci(n - 2);
}

RB_METHOD_INT_ARG(rb_fibonacci, fibonacci)
RB_METHOD_INT_ARG_2(rb_get_random_value, GetRandomValue)

extern "C" void initializeKernel() {
  rb_define_module_function(rb_mKernel, "random", rb_get_random_value, 2);
  rb_define_module_function(rb_mKernel, "fib", rb_fibonacci, 1);
}
