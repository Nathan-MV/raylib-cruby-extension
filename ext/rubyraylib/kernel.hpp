#ifndef KERNEL_H
#define KERNEL_H

#include "ruby_values.hpp"
#include "raylib_values.hpp"

extern "C" void initializeKernel();
float GetRandomFloat(float min, float max);

#endif // KERNEL_H
