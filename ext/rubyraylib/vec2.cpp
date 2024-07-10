#include "vec2.hpp"

VALUE rb_cVec2;

static void rb_vec2_free(void *ptr) {
  delete static_cast<Vector2*>(ptr);
}

static VALUE rb_vec2_alloc(VALUE klass) {
  Vector2* vec2 = new (std::nothrow) Vector2();
  if (!vec2) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vec2.");
    return Qnil;
  }

  return Data_Wrap_Struct(klass, NULL, rb_vec2_free, vec2);
}

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
RB_VEC2_OTHER(rb_vec2_add, Vector2Add)
RB_VEC2_VALUE(rb_vec2_add_value, Vector2AddValue)
RB_VEC2_OTHER(rb_vec2_subtract, Vector2Subtract)
RB_VEC2_VALUE(rb_vec2_subtract_value, Vector2SubtractValue)
RB_VEC2_FLOAT(rb_vec2_length, Vector2Length)
RB_VEC2_FLOAT(rb_vec2_length_sqr, Vector2LengthSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_dot_product, Vector2DotProduct)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance, Vector2Distance)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance_sqr, Vector2DistanceSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_angle, Vector2Angle)
RB_VEC2_VALUE(rb_vec2_scale, Vector2Scale)
RB_VEC2_OTHER(rb_vec2_multiply, Vector2Multiply)
RB_VEC2(rb_vec2_negate, Vector2Negate)
RB_VEC2_OTHER(rb_vec2_divide, Vector2Divide)
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

static VALUE rb_vec2_clamp(VALUE self, VALUE min, VALUE max) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *min_vec2 = get_vec2(min);
  Vector2 *max_vec2 = get_vec2(max);

  *vec2 = Vector2Clamp(*vec2, *min_vec2, *max_vec2);

  return self;
}

static VALUE rb_vec2_clamp_value(VALUE self, VALUE min_val, VALUE max_val) {
  Vector2 *vec2 = get_vec2(self);
  float min = NUM2DBL(min_val);
  float max = NUM2DBL(max_val);

  *vec2 = Vector2ClampValue(*vec2, min, max);

  return self;
}

RB_VEC2_OTHER_INT(rb_vec2_equals, Vector2Equals)

static VALUE rb_vec2_set(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

// Multiply Vec2 by a float value
static Vector2 Vector2MultiplyValue(Vector2 v, float mult)
{
    Vector2 result = { v.x * mult, v.y * mult };

    return result;
}

// Multiply Vec2 by an integer
static VALUE rb_vec2_multiply_value(VALUE self, VALUE value) {
    Vector2 *vec2 = get_vec2(self);
    float val = NUM2DBL(value);

    *vec2 = Vector2MultiplyValue(*vec2, val);

    return self;
}

// Divide Vec2 by an integer
static Vector2 Vector2DivideValue(Vector2 v, float div)
{
    Vector2 result = { v.x / div, v.y / div };

    return result;
}

// Divide Vec2 by an integer
static VALUE rb_vec2_divide_value(VALUE self, VALUE value) {
    Vector2 *vec2 = get_vec2(self);
    float val = NUM2DBL(value);

    *vec2 = Vector2DivideValue(*vec2, val);

    return self;
}

RB_VEC2_SCALAR(rb_vec2_add_scalar, Vector2Add, Vector2AddValue)
RB_VEC2_SCALAR(rb_vec2_subtract_scalar, Vector2Subtract, Vector2SubtractValue)
RB_VEC2_SCALAR(rb_vec2_multiply_scalar, Vector2Multiply, Vector2MultiplyValue)
RB_VEC2_SCALAR(rb_vec2_divide_scalar, Vector2Divide, Vector2DivideValue)

static VALUE rb_vec2_reverse(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x *= -1;
  vec2->y *= -1;

  return self;
}

static VALUE rb_vec2_outside_bounds(VALUE self, VALUE size_val) {
  Vector2 *vec2 = get_vec2(self);

  double x = vec2->x;
  double y = vec2->y;
  double size;

  if (rb_obj_is_kind_of(size_val, rb_cVec2)) {
    Vector2 *size_vec2 = get_vec2(size_val);
    size = (size_vec2->x + size_vec2->y) / 2;
  } else {
    size = NUM2DBL(size_val);
  }

  double width = GetScreenWidth();
  double height = GetScreenHeight();

  if ((x + size) > width || (x + size) < 0 ||
      (y + size) > height || (y + size) < 0) {
    return Qtrue;
  }

  return Qfalse;
}

static VALUE rb_vec2_to_s(VALUE self) {
    Vector2 *vec2 = get_vec2(self);
    char buffer[50];

    snprintf(buffer, sizeof(buffer), "Vec2(x: %.2f, y: %.2f)", vec2->x, vec2->y);

    return rb_str_new_cstr(buffer);
}

void initializeVec2() {
  rb_cVec2 = rb_define_class("Vec2", rb_cObject);

  rb_define_alloc_func(rb_cVec2, rb_vec2_alloc);
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

  rb_define_method(rb_cVec2, "add", rb_vec2_add, 1);
  rb_define_method(rb_cVec2, "add_val", rb_vec2_add_value, 1);
  rb_define_method(rb_cVec2, "sub", rb_vec2_subtract, 1);
  rb_define_method(rb_cVec2, "sub_val", rb_vec2_subtract_value, 1);
  rb_define_method(rb_cVec2, "multiply", rb_vec2_multiply, 1);
  rb_define_method(rb_cVec2, "multiply_val", rb_vec2_multiply_value, 1);
  rb_define_method(rb_cVec2, "divide", rb_vec2_divide, 1);
  rb_define_method(rb_cVec2, "divide_val", rb_vec2_divide_value, 1);

  rb_define_method(rb_cVec2, "length", rb_vec2_length, 0);
  rb_define_method(rb_cVec2, "length_sqr", rb_vec2_length_sqr, 0);
  rb_define_method(rb_cVec2, "dot_product", rb_vec2_dot_product, 1);
  rb_define_method(rb_cVec2, "distance", rb_vec2_distance, 1);
  rb_define_method(rb_cVec2, "distance_sqr", rb_vec2_distance_sqr, 1);
  rb_define_method(rb_cVec2, "angle", rb_vec2_angle, 1);
  rb_define_method(rb_cVec2, "scale", rb_vec2_scale, 1);
  rb_define_method(rb_cVec2, "negate", rb_vec2_negate, 0);
  rb_define_method(rb_cVec2, "normalize", rb_vec2_normalize, 0);
  rb_define_method(rb_cVec2, "lerp", rb_vec2_lerp, 2);
  rb_define_method(rb_cVec2, "reflect", rb_vec2_reflect, 1);
  rb_define_method(rb_cVec2, "rotate", rb_vec2_rotate, 1);
  rb_define_method(rb_cVec2, "move_towards", rb_vec2_move_towards, 2);
  rb_define_method(rb_cVec2, "invert", rb_vec2_invert, 0);
  rb_define_method(rb_cVec2, "clamp", rb_vec2_clamp, 2);
  rb_define_method(rb_cVec2, "clamp_val", rb_vec2_clamp_value, 2);
  rb_define_method(rb_cVec2, "equals", rb_vec2_equals, 1);

  rb_define_method(rb_cVec2, "outside_bounds?", rb_vec2_outside_bounds, 1);
  rb_define_method(rb_cVec2, "reverse", rb_vec2_reverse, 0);
  rb_define_method(rb_cVec2, "to_s", rb_vec2_to_s, 0);
}
