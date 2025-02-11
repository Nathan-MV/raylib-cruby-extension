#include "vec2.h"

// Divide Vec2 by an integer
Vector2 Vector2DivideValue(Vector2 v, float div) {
  Vector2 result = {v.x / div, v.y / div};

  return result;
}

Vector2 Vector2RandomMovement(Vector2 &position, float speed, const std::string &direction) {
  Vector2 random_direction = {GetRandomFloat(-1.0f, 1.0f), GetRandomFloat(-1.0f, 1.0f)};

  if (direction == "up") {
    random_direction.y = GetRandomFloat(-1.0f, 0.0f);
  } else if (direction == "down") {
    random_direction.y = GetRandomFloat(0.0f, 1.0f);
  } else if (direction == "right") {
    random_direction.x = GetRandomFloat(0.0f, 1.0f);
  } else if (direction == "left") {
    random_direction.x = GetRandomFloat(-1.0f, 0.0f);
  }

  auto velocity = Vector2Scale(random_direction, speed);
  auto delta_velocity = Vector2Scale(velocity, GetFrameTime());
  Vector2 new_position = Vector2Add(position, delta_velocity);

  new_position.x = Clamp(new_position.x, 0.0f, static_cast<float>(GetScreenWidth()));
  new_position.y = Clamp(new_position.y, 0.0f, static_cast<float>(GetScreenHeight()));

  return new_position;
}

bool Vector2IsZero(const Vector2 &vec2) { return (vec2.x == 0 && vec2.y == 0); }

std::string Vector2ToString(const Vector2 &vec2) {
  char buffer[50];

  snprintf(buffer, sizeof(buffer), "Vec2(x: %.2f, y: %.2f)", vec2.x, vec2.y);

  return std::string(buffer);
}
