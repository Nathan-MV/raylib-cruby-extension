#include "vec2.h"

VALUE rb_cVector2;

static void rb_vec2_free(void *ptr) {
  free(ptr);
}

static VALUE rb_vec2_alloc(VALUE klass) {
  Vector2 *vec2 = ALLOC(Vector2);

  return Data_Wrap_Struct(klass, NULL, rb_vec2_free, vec2);
}

static VALUE rb_vec2_initialize(VALUE self, VALUE x, VALUE y) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->x = NUM2INT(x);
  vec2->y = NUM2INT(y);

  return self;
}

static VALUE rb_vec2_get_x(VALUE self) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  return INT2NUM(vec2->x);
}

static VALUE rb_vec2_get_y(VALUE self) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  return INT2NUM(vec2->y);
}

static VALUE rb_vec2_set_x(VALUE self, VALUE value) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->x = NUM2INT(value);

  return self;
}

static VALUE rb_vec2_set_y(VALUE self, VALUE value) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->y = NUM2INT(value);

  return self;
}

static VALUE rb_vec2_add_bang(VALUE self, VALUE other) {
  Vector2 *vec1 = (Vector2 *)DATA_PTR(self);
  Vector2 *vec2 = (Vector2 *)DATA_PTR(other);

  vec1->x += vec2->x;
  vec1->y += vec2->y;

  return self;
}

static VALUE rb_vec2_reverse_x(VALUE self) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->x *= -1;

  return self;
}

static VALUE rb_vec2_reverse_y(VALUE self) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->y *= -1;

  return self;
}

static VALUE rb_vec2_reverse(VALUE self) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  vec2->x *= -1;
  vec2->y *= -1;

  return self;
}

static VALUE rb_vec2_outside_bounds(VALUE self, VALUE size_value) {
  Vector2 *vec2 = (Vector2 *)DATA_PTR(self);

  double x = vec2->x;
  double y = vec2->y;
  double size;

  if (rb_obj_is_kind_of(size_value, rb_cVector2)) {
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

void initializeVec2() {
  rb_cVector2 = rb_define_class("Vec2", rb_cObject);

  rb_define_alloc_func(rb_cVector2, rb_vec2_alloc);
  rb_define_method(rb_cVector2, "initialize", rb_vec2_initialize, 2);
  rb_define_method(rb_cVector2, "x", rb_vec2_get_x, 0);
  rb_define_method(rb_cVector2, "y", rb_vec2_get_y, 0);
  rb_define_method(rb_cVector2, "x=", rb_vec2_set_x, 1);
  rb_define_method(rb_cVector2, "y=", rb_vec2_set_y, 1);

  rb_define_method(rb_cVector2, "add!", rb_vec2_add_bang, 1);
  rb_define_method(rb_cVector2, "outside_bounds?", rb_vec2_outside_bounds, 1);
  rb_define_method(rb_cVector2, "reverse!", rb_vec2_reverse, 0);
}