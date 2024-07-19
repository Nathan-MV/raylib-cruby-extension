#include "vec2.hpp"

VALUE rb_cVec2;

static VALUE rb_vec2_initialize(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

RB_VEC2_GETTER(rb_vec2_get_x, x)
RB_VEC2_GETTER(rb_vec2_get_y, y)
RB_VEC2_SETTER(rb_vec2_set_x, y)
RB_VEC2_SETTER(rb_vec2_set_y, y)
RB_VEC2_FLOAT(rb_vec2_length, Vector2Length)
RB_VEC2_FLOAT(rb_vec2_length_sqr, Vector2LengthSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_dot_product, Vector2DotProduct)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance, Vector2Distance)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance_sqr, Vector2DistanceSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_angle, Vector2Angle)
RB_VEC2(rb_vec2_negate, Vector2Negate)
RB_VEC2(rb_vec2_normalize, Vector2Normalize)

static VALUE rb_vec2_lerp(VALUE self, VALUE other, VALUE amount) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);
  float amt = NUM2DBL(amount);

  *vec2 = Vector2Lerp(*vec2, *other_vec2, amt);

  return self;
}

RB_VEC2_OTHER(rb_vec2_reflect, Vector2Reflect)

static VALUE rb_vec2_rotate(VALUE self, VALUE angle) {
  Vector2 *vec2 = get_vec2(self);
  float ang = NUM2DBL(angle);

  *vec2 = Vector2Rotate(*vec2, ang);

  return self;
}

static VALUE rb_vec2_move_towards(VALUE self, VALUE target, VALUE max_distance) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *tarGET_VEC2 = get_vec2(target);
  float max = NUM2DBL(max_distance);

  *vec2 = Vector2MoveTowards(*vec2, *tarGET_VEC2, max);

  return self;
}

RB_VEC2(rb_vec2_invert, Vector2Invert)

static VALUE rb_vec2_clamp(int argc, VALUE *argv, VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  if (argc == 1) {
    VALUE arg = argv[0];

    if (rb_obj_is_kind_of(arg, rb_cVec2)) {
      Vector2 *clamp_vec = get_vec2(arg);

      Vector2 result = {
          std::clamp(vec2->x, 0.0f, clamp_vec->x),
          std::clamp(vec2->y, 0.0f, clamp_vec->y)
      };
      *vec2 = result;
    } else {
      rb_raise(rb_eArgError, "Invalid argument type");
    }
  } else if (argc == 2) {
    VALUE arg1 = argv[0];
    VALUE arg2 = argv[1];

    if (rb_obj_is_kind_of(arg1, rb_cVec2) && rb_obj_is_kind_of(arg2, rb_cVec2)) {
      Vector2 *min_vec2 = get_vec2(arg1);
      Vector2 *max_vec2 = get_vec2(arg2);
      *vec2 = Vector2Clamp(*vec2, *min_vec2, *max_vec2);
    } else if (RB_FLOAT_TYPE_P(arg1) && RB_FLOAT_TYPE_P(arg2)) {
      float min = NUM2DBL(arg1);
      float max = NUM2DBL(arg2);
      *vec2 = Vector2ClampValue(*vec2, min, max);
    } else {
      rb_raise(rb_eArgError, "Invalid argument types");
    }
  } else {
    rb_raise(rb_eArgError, "Invalid number of arguments");
  }

  return self;
}

RB_VEC2_OTHER_INT(rb_vec2_equals, Vector2Equals)

static VALUE rb_vec2_set(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

// Divide Vec2 by an integer
static Vector2 Vector2DivideValue(Vector2 v, float div)
{
    Vector2 result = { v.x / div, v.y / div };

    return result;
}

RB_VEC2_SCALAR(rb_vec2_add_scalar, Vector2Add, Vector2AddValue)
RB_VEC2_SCALAR(rb_vec2_subtract_scalar, Vector2Subtract, Vector2SubtractValue)
RB_VEC2_SCALAR(rb_vec2_multiply_scalar, Vector2Multiply, Vector2Scale)
RB_VEC2_SCALAR(rb_vec2_divide_scalar, Vector2Divide, Vector2DivideValue)

static VALUE rb_vec2_screen_bounds(VALUE self, VALUE size_val) {
  Vector2 *vec2 = get_vec2(self);
  double x = vec2->x;
  double y = vec2->y;
  double size_x;
  double size_y;

  if (rb_obj_is_kind_of(size_val, rb_cVec2)) {
    Vector2 *size_vec2 = get_vec2(size_val);
    size_x = size_vec2->x;
    size_y = size_vec2->y;
  } else if (rb_obj_is_kind_of(size_val, rb_cTexture)) {
    Texture *texture = get_texture(size_val);
    size_x = texture->width;
    size_y = texture->height;
  } else {
    size_x = NUM2DBL(size_val);
    size_y = NUM2DBL(size_val);
  }
  double width = GetScreenWidth();
  double height = GetScreenHeight();

  if (x == 0 || x == (width - size_x) ||
      y == 0 || y == (height - size_y)) {
    return Qtrue;
  }

  return Qfalse;
}

static VALUE rb_random_movement(VALUE self, VALUE direction, VALUE speed) {
    Vector2* position = get_vec2(self);
    Vector2 direction_range = *get_vec2(direction);
    float speed_value = NUM2DBL(speed);

    Vector2 random_direction = {GetRandomFloat(direction_range.x, direction_range.y), GetRandomFloat(direction_range.x, direction_range.y)};
    Vector2 velocity = Vector2Scale(random_direction, speed_value);
    Vector2 delta_direction = Vector2Scale(velocity, GetFrameTime());

    *position = Vector2Add(*position, delta_direction);

    return self;
}

static VALUE rb_vec2_zero(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  bool result = (vec2->x == 0 && vec2->y == 0);

  return result ? Qtrue : Qfalse;
}

static VALUE rb_vec2_to_s(VALUE self) {
    Vector2 *vec2 = get_vec2(self);
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "Vec2(x: %.2f, y: %.2f)", vec2->x, vec2->y);

    return rb_str_new_cstr(buffer);
}

extern "C" void initializeVec2() {
  rb_cVec2 = rb_define_class_under(rb_mRl, "Vec2", rb_cObject);
  rb_define_alloc_func(rb_cVec2, rb_object_alloc<Vector2>);

  rb_define_method(rb_cVec2, "initialize", rb_vec2_initialize, 2);
  rb_define_method(rb_cVec2, "x", rb_vec2_get_x, 0);
  rb_define_method(rb_cVec2, "y", rb_vec2_get_y, 0);
  rb_define_method(rb_cVec2, "x=", rb_vec2_set_x, 1);
  rb_define_method(rb_cVec2, "y=", rb_vec2_set_y, 1);
  rb_define_method(rb_cVec2, "set", rb_vec2_set, 2);

  rb_define_method(rb_cVec2, "+", rb_vec2_add_scalar, 1);
  rb_define_method(rb_cVec2, "-", rb_vec2_subtract_scalar, 1);
  rb_define_method(rb_cVec2, "*", rb_vec2_multiply_scalar, 1);
  rb_define_method(rb_cVec2, "/", rb_vec2_divide_scalar, 1);
  rb_define_method(rb_cVec2, "==", rb_vec2_equals, 1);

  rb_define_method(rb_cVec2, "length", rb_vec2_length, 0);
  rb_define_method(rb_cVec2, "length_sqr", rb_vec2_length_sqr, 0);
  rb_define_method(rb_cVec2, "dot", rb_vec2_dot_product, 1);
  rb_define_method(rb_cVec2, "distance", rb_vec2_distance, 1);
  rb_define_method(rb_cVec2, "distance_sqr", rb_vec2_distance_sqr, 1);
  rb_define_method(rb_cVec2, "angle", rb_vec2_angle, 1);
  rb_define_method(rb_cVec2, "negate", rb_vec2_negate, 0);
  rb_define_method(rb_cVec2, "normalize", rb_vec2_normalize, 0);
  rb_define_method(rb_cVec2, "lerp", rb_vec2_lerp, 2);
  rb_define_method(rb_cVec2, "reflect", rb_vec2_reflect, 1);
  rb_define_method(rb_cVec2, "rotate", rb_vec2_rotate, 1);
  rb_define_method(rb_cVec2, "move_towards", rb_vec2_move_towards, 2);
  rb_define_method(rb_cVec2, "invert", rb_vec2_invert, 0);
  rb_define_method(rb_cVec2, "eql?", rb_vec2_equals, 1);

  rb_define_method(rb_cVec2, "clamp", rb_vec2_clamp, -1);
  rb_define_method(rb_cVec2, "screen_bounds?", rb_vec2_screen_bounds, 1);
  rb_define_method(rb_cVec2, "random_movement", rb_random_movement, 2);
  rb_define_method(rb_cVec2, "zero?", rb_vec2_zero, 0);
  rb_define_method(rb_cVec2, "to_s", rb_vec2_to_s, 0);
}
