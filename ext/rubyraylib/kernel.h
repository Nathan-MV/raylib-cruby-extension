#ifndef KERNEL_H
#define KERNEL_H

#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include "raylib_values.h"

float GetRandomFloat(float min, float max);
int fibonnaci(int number);
int levenshtein_distance(const std::string& str1, const std::string& str2);

#endif  // KERNEL_H
