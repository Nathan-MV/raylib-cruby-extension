#ifndef VEC2_H
#define VEC2_H

#include <algorithm>
#include <string>
#include <tuple>
#include "raylib_values.h"
#include "kernel.h"

Vector2 Vector2DivideValue(Vector2 v, float div);
Vector2 Vector2RandomMovement(Vector2 &position, float speed, const std::string &direction);
bool Vector2IsZero(const Vector2 &vec2);
std::string Vector2ToString(const Vector2 &vec2);

#endif  // VEC2_H
