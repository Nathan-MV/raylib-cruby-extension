#include "vec2.h"

VALUE rb_cVec2;

static void rb_vec2_free(void *ptr) {
  if (ptr) {
    Vector2 *vec2 = (Vector2 *)ptr;
    free(vec2);
  }
}

static VALUE rb_vec2_alloc(VALUE klass) {
  Vector2 *vec2 = ALLOC(Vector2);

  if (!vec2) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Vector2.");
  }

  return Data_Wrap_Struct(klass, NULL, rb_vec2_free, vec2);
}

Vector2* get_vec2(VALUE obj) {
  Vector2 *vec2;
  Data_Get_Struct(obj, Vector2, vec2);

  return vec2;
}

static VALUE rb_vec2_initialize(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

static VALUE rb_vec2_get_x(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  return INT2NUM(vec2->x);
}

static VALUE rb_vec2_get_y(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  return INT2NUM(vec2->y);
}

static VALUE rb_vec2_set_x(VALUE self, VALUE value) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(value);

  return self;
}

static VALUE rb_vec2_set_y(VALUE self, VALUE value) {
  Vector2 *vec2 = get_vec2(self);

  vec2->y = NUM2INT(value);

  return self;
}

static VALUE rb_vec2_set(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

static VALUE rb_vec2_add(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  *vec2 = Vector2Add(*vec2, *other_vec2);

  return self;
}

static VALUE rb_vec2_add_value(VALUE self, VALUE add) {
  Vector2 *vec2 = get_vec2(self);
  float add_value = NUM2DBL(add);

  *vec2 = Vector2SubtractValue(*vec2, add_value);

  return self;
}

static VALUE rb_vec2_subtract(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  *vec2 = Vector2Add(*vec2, *other_vec2);

  return self;
}

static VALUE rb_vec2_subtract_value(VALUE self, VALUE sub) {
  Vector2 *vec2 = get_vec2(self);
  float sub_value = NUM2DBL(sub);

  *vec2 = Vector2SubtractValue(*vec2, sub_value);

  return self;
}

static VALUE rb_vec2_length(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  float result = Vector2Length(*vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_length_sqr(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  float result = Vector2LengthSqr(*vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_dot_product(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  float result = Vector2DotProduct(*vec2, *other_vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_distance(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  float result = Vector2Distance(*vec2, *other_vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_distance_sqr(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  float result = Vector2DistanceSqr(*vec2, *other_vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_angle(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  float result = Vector2Angle(*vec2, *other_vec2);

  return DBL2NUM(result);
}

static VALUE rb_vec2_scale(VALUE self, VALUE scale) {
  Vector2 *vec2 = get_vec2(self);
  float scale_value = NUM2DBL(scale);

  *vec2 = Vector2Scale(*vec2, scale_value);

  return self;
}

static VALUE rb_vec2_multiply(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  *vec2 = Vector2Multiply(*vec2, *other_vec2);

  return self;
}

static VALUE rb_vec2_negate(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  *vec2 = Vector2Negate(*vec2);

  return self;
}

static VALUE rb_vec2_divide(VALUE self, VALUE other) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);

  *vec2 = Vector2Divide(*vec2, *other_vec2);

  return self;
}

static VALUE rb_vec2_normalize(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  *vec2 = Vector2Normalize(*vec2);

  return self;
}

static VALUE rb_vec2_lerp(VALUE self, VALUE other, VALUE amount) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *other_vec2 = get_vec2(other);
  float amount_value = NUM2DBL(amount);

  *vec2 = Vector2Lerp(*vec2, *other_vec2, amount_value);

  return self;
}

static VALUE rb_vec2_reflect(VALUE self, VALUE normal) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *normal_vec2 = get_vec2(normal);

  *vec2 = Vector2Reflect(*vec2, *normal_vec2);

  return self;
}

static VALUE rb_vec2_rotate(VALUE self, VALUE angle) {
  Vector2 *vec2 = get_vec2(self);
  float angle_value = NUM2DBL(angle);

  *vec2 = Vector2Rotate(*vec2, angle_value);

  return self;
}

static VALUE rb_vec2_move_towards(VALUE self, VALUE target, VALUE max_distance) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *target_vec2 = get_vec2(target);
  float max_distance_value = NUM2DBL(max_distance);

  *vec2 = Vector2MoveTowards(*vec2, *target_vec2, max_distance_value);

  return self;
}

static VALUE rb_vec2_invert(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  *vec2 = Vector2Invert(*vec2);

  return self;
}

static VALUE rb_vec2_clamp(VALUE self, VALUE min, VALUE max) {
  Vector2 *vec2 = get_vec2(self);
  Vector2 *min_vec2 = get_vec2(min);
  Vector2 *max_vec2 = get_vec2(max);

  *vec2 = Vector2Clamp(*vec2, *min_vec2, *max_vec2);

  return self;
}

static VALUE rb_vec2_clamp_value(VALUE self, VALUE min, VALUE max) {
  Vector2 *vec2 = get_vec2(self);
  float min_value = NUM2DBL(min);
  float max_value = NUM2DBL(max);

  *vec2 = Vector2ClampValue(*vec2, min_value, max_value);

  return self;
}

static VALUE rb_vec2_equals(VALUE self, VALUE q) {
  Vector2 *p_vec2 = get_vec2(self);
  Vector2 *q_vec2 = get_vec2(q);

  int result = Vector2Equals(*p_vec2, *q_vec2);

  return INT2NUM(result);
}

static VALUE rb_vec2_reverse(VALUE self) {
  Vector2 *vec2 = get_vec2(self);

  vec2->x *= -1;
  vec2->y *= -1;

  return self;
}

static VALUE rb_vec2_outside_bounds(VALUE self, VALUE size_value) {
  Vector2 *vec2 = get_vec2(self);

  double x = vec2->x;
  double y = vec2->y;
  double size;

  if (rb_obj_is_kind_of(size_value, rb_cVec2)) {
    Vector2 *size_vec2 = (Vector2 *)DATA_PTR(size_value);
    size = (size_vec2->x + size_vec2->y) / 2;
  } else {
    size = NUM2DBL(size_value);
  }

  double screen_width = GetScreenWidth();
  double screen_height = GetScreenHeight();

  if ((x + size) > screen_width || (x + size) < 0 ||
      (y + size) > screen_height || (y + size) < 0) {
    return Qtrue;
  }

  return Qfalse;
}

static VALUE rb_vec2_to_s(VALUE self) {
    Vector2 *vec2 = get_vec2(self);
    VALUE str;
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

  rb_define_method(rb_cVec2, "add", rb_vec2_add, 1);
  rb_define_method(rb_cVec2, "add_value", rb_vec2_add_value, 1);
  rb_define_method(rb_cVec2, "sub", rb_vec2_subtract, 1);
  rb_define_method(rb_cVec2, "sub_value", rb_vec2_subtract_value, 1);

  rb_define_method(rb_cVec2, "length", rb_vec2_length, 0);
  rb_define_method(rb_cVec2, "length_sqr", rb_vec2_length_sqr, 0);
  rb_define_method(rb_cVec2, "dot_product", rb_vec2_dot_product, 1);
  rb_define_method(rb_cVec2, "distance", rb_vec2_distance, 1);
  rb_define_method(rb_cVec2, "distance_sqr", rb_vec2_distance_sqr, 1);
  rb_define_method(rb_cVec2, "angle", rb_vec2_angle, 1);
  rb_define_method(rb_cVec2, "scale", rb_vec2_scale, 1);
  rb_define_method(rb_cVec2, "multiply", rb_vec2_multiply, 1);
  rb_define_method(rb_cVec2, "negate", rb_vec2_negate, 0);
  rb_define_method(rb_cVec2, "divide", rb_vec2_divide, 1);
  rb_define_method(rb_cVec2, "normalize", rb_vec2_normalize, 0);
  rb_define_method(rb_cVec2, "lerp", rb_vec2_lerp, 2);
  rb_define_method(rb_cVec2, "reflect", rb_vec2_reflect, 1);
  rb_define_method(rb_cVec2, "rotate", rb_vec2_rotate, 1);
  rb_define_method(rb_cVec2, "move_towards", rb_vec2_move_towards, 2);
  rb_define_method(rb_cVec2, "invert", rb_vec2_invert, 0);
  rb_define_method(rb_cVec2, "clamp", rb_vec2_clamp, 2);
  rb_define_method(rb_cVec2, "clamp_value", rb_vec2_clamp_value, 2);
  rb_define_method(rb_cVec2, "equals", rb_vec2_equals, 1);

  rb_define_method(rb_cVec2, "outside_bounds?", rb_vec2_outside_bounds, 1);
  rb_define_method(rb_cVec2, "reverse", rb_vec2_reverse, 0);

  rb_define_method(rb_cVec2, "to_s", rb_vec2_to_s, 0);
}