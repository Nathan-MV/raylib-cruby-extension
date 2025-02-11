#include <vec2_bindings.h>
#include <tuple>

VALUE rb_cVec2;

static auto rb_vec2_initialize(int argc, VALUE *argv, VALUE self) {
  auto *vec2 = get_vec2(self);

  // Default values
  auto x = 0.0f;
  auto y = 0.0f;

  // Parse arguments
  if (argc > 0) {
    x = NUM2DBL(argv[0]);
    y = NUM2DBL(argv[1]);
  }

  vec2->x = x;
  vec2->y = y;

  return self;
}

RB_VEC2_GETTER(rb_vec2_get_x, x)
RB_VEC2_GETTER(rb_vec2_get_y, y)
RB_VEC2_SETTER(rb_vec2_set_x, x)
RB_VEC2_SETTER(rb_vec2_set_y, y)
RB_VEC2_FLOAT(rb_vec2_length, Vector2Length)
RB_VEC2_FLOAT(rb_vec2_length_sqr, Vector2LengthSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_dot_product, Vector2DotProduct)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance, Vector2Distance)
RB_VEC2_OTHER_FLOAT(rb_vec2_distance_sqr, Vector2DistanceSqr)
RB_VEC2_OTHER_FLOAT(rb_vec2_angle, Vector2Angle)
RB_VEC2(rb_vec2_negate, Vector2Negate)
RB_VEC2(rb_vec2_normalize, Vector2Normalize)

static auto rb_vec2_lerp(VALUE self, VALUE other, VALUE amount) {
  auto *vec2 = get_vec2(self);
  auto *other_vec2 = get_vec2(other);
  auto amt = NUM2DBL(amount);

  *vec2 = Vector2Lerp(*vec2, *other_vec2, amt);

  return self;
}

RB_VEC2_OTHER(rb_vec2_reflect, Vector2Reflect)

static auto rb_vec2_rotate(VALUE self, VALUE angle) {
  auto *vec2 = get_vec2(self);
  auto ang = NUM2DBL(angle);

  *vec2 = Vector2Rotate(*vec2, ang);

  return self;
}

static auto rb_vec2_move_towards(VALUE self, VALUE target, VALUE max_distance) {
  auto *vec2 = get_vec2(self);
  auto *tarGET_VEC2 = get_vec2(target);
  auto max = NUM2DBL(max_distance);

  *vec2 = Vector2MoveTowards(*vec2, *tarGET_VEC2, max);

  return self;
}

RB_VEC2(rb_vec2_invert, Vector2Invert)

static auto rb_vec2_clamp(int argc, VALUE *argv, VALUE self) {
  auto *vec2 = get_vec2(self);

  if (argc == 1) {
    VALUE arg = argv[0];

    if (rb_obj_is_kind_of(arg, rb_cVec2)) {
      auto *clamp_vec = get_vec2(arg);

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
      auto *min_vec2 = get_vec2(arg1);
      auto *max_vec2 = get_vec2(arg2);
      *vec2 = Vector2Clamp(*vec2, *min_vec2, *max_vec2);
    } else if (RB_FLOAT_TYPE_P(arg1) && RB_FLOAT_TYPE_P(arg2)) {
      auto min = NUM2DBL(arg1);
      auto max = NUM2DBL(arg2);
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

static auto rb_vec2_set(VALUE self, VALUE x, VALUE y) {
  auto *vec2 = get_vec2(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

RB_VEC2_SCALAR(rb_vec2_add_scalar, Vector2Add, Vector2AddValue)
RB_VEC2_SCALAR(rb_vec2_subtract_scalar, Vector2Subtract, Vector2SubtractValue)
RB_VEC2_SCALAR(rb_vec2_multiply_scalar, Vector2Multiply, Vector2Scale)
RB_VEC2_SCALAR(rb_vec2_divide_scalar, Vector2Divide, Vector2DivideValue)

static auto rb_vec2_screen_bounds(VALUE self, VALUE size_val) {
  auto *vec2 = get_vec2(self);
  auto [x, y] = std::make_pair(vec2->x, vec2->y);
  double size_x, size_y;

  if (rb_obj_is_kind_of(size_val, rb_cVec2)) {
    auto *size_vec2 = get_vec2(size_val);
    std::tie(size_x, size_y) = std::make_pair(size_vec2->x, size_vec2->y);
  } else if (rb_obj_is_kind_of(size_val, rb_cSprite)) {
    auto *texture = get_texture(size_val);
    std::tie(size_x, size_y) = std::make_pair(texture->width, texture->height);
  } else {
    size_x = size_y = NUM2DBL(size_val);
  }

  auto [width, height] = std::make_pair(GetScreenWidth(), GetScreenHeight());

  if (x == 0 || x == (width - size_x) || y == 0 || y == (height - size_y)) {
    return Qtrue;
  }

  return Qfalse;
}

static auto rb_random_movement(int argc, VALUE *argv, VALUE self) {
  auto *position = get_vec2(self);
  VALUE direction_sym = Qnil, speed;
  rb_scan_args(argc, argv, "11", &speed, &direction_sym);

  auto speed_value = NUM2DBL(speed);
  std::string direction;

  if (!NIL_P(direction_sym)) {
    ID dir_id = SYM2ID(direction_sym);
    if (dir_id == rb_intern("up")) {
      direction = "up";
    } else if (dir_id == rb_intern("down")) {
      direction = "down";
    } else if (dir_id == rb_intern("right")) {
      direction = "right";
    } else if (dir_id == rb_intern("left")) {
      direction = "left";
    } else {
      rb_raise(rb_eArgError, "Invalid direction symbol");
    }
  }

  Vector2RandomMovement(*position, speed_value, direction);

  return self;
}

static auto rb_vec2_is_zero(VALUE self) {
  auto *vec2 = get_vec2(self);

  auto result = Vector2IsZero(*vec2);

  return result ? Qtrue : Qfalse;
}

static auto rb_vec2_to_string(VALUE self) {
  auto *vec2 = get_vec2(self);

  auto buffer = Vector2ToString(*vec2);

  return rb_str_new_cstr(buffer.c_str());
}

extern "C" void Init_Vec2() {
  rb_cVec2 = rb_define_class_under(rb_mRL, "Vec2", rb_cObject);
  rb_define_alloc_func(rb_cVec2, rb_object_alloc<Vector2>);

  rb_define_method(rb_cVec2, "initialize", rb_vec2_initialize, -1);
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
  rb_define_method(rb_cVec2, "rand_move", rb_random_movement, -1);
  rb_define_method(rb_cVec2, "zero?", rb_vec2_is_zero, 0);
  rb_define_method(rb_cVec2, "to_s", rb_vec2_to_string, 0);
}
