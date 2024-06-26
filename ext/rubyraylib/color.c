#include "color.h"

VALUE rb_cColor;

static void rb_color_free(void *ptr) {
  free(ptr);
}

static VALUE rb_color_alloc(VALUE klass) {
  Color *col = ALLOC(Color);
  return Data_Wrap_Struct(klass, NULL, rb_color_free, col);
}

static Color* get_color_from_value(VALUE obj) {
  Color *color;
  Data_Get_Struct(obj, Color, color);
  return color;
}

static VALUE rb_color_initialize(int argc, VALUE *argv, VALUE self) {
  VALUE r, g, b, a;
  Color *color = get_color_from_value(self);

  // Parse the arguments
  rb_scan_args(argc, argv, "31", &r, &g, &b, &a);

  // Set default value of a to 255 if not provided
  if (argc < 4) {
    a = INT2NUM(255);
  }

  color->r = NUM2INT(r);
  color->g = NUM2INT(g);
  color->b = NUM2INT(b);
  color->a = NUM2INT(a);

  return self;
}

static VALUE rb_color_get_red(VALUE self) {
  Color *color = get_color_from_value(self);

  return INT2NUM(color->r);
}

static VALUE rb_color_get_green(VALUE self) {
  Color *color = get_color_from_value(self);

  return INT2NUM(color->g);
}

static VALUE rb_color_get_blue(VALUE self) {
  Color *color = get_color_from_value(self);

  return INT2NUM(color->b);
}

// Ruby method to get the alpha component of a Color object
static VALUE rb_color_get_alpha(VALUE self) {
  Color *color = get_color_from_value(self);

  return INT2NUM(color->a);
}

static VALUE rb_color_set_red(VALUE self, VALUE value) {
  Color *color = get_color_from_value(self);

  color->r = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_green(VALUE self, VALUE value) {
  Color *color = get_color_from_value(self);

  color->g = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_blue(VALUE self, VALUE value) {
  Color *color = get_color_from_value(self);

  color->b = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_alpha(VALUE self, VALUE value) {
  Color *color = get_color_from_value(self);

  color->a = NUM2INT(value);

  return self;
}

static VALUE rb_fade(VALUE self, VALUE alpha) {
  Color *color = get_color_from_value(self);
  float alpha_value = NUM2DBL(alpha);

  *color = Fade(*color, alpha_value);

  return self;
}

static VALUE rb_color_to_int(VALUE self) {
  Color *color = get_color_from_value(self);

  int result = ColorToInt(*color);

  return INT2NUM(result);
}

static VALUE rb_color_normalize(VALUE self) {
  Color *color = get_color_from_value(self);

  Vector4 result = ColorNormalize(*color);

  VALUE rb_result = Data_Wrap_Struct(rb_cVector4, NULL, NULL, &result);

  return rb_result;
}

static VALUE rb_color_tint(VALUE self, VALUE tint) {
  Color *color = get_color_from_value(self);
  Color *tint_value = get_color_from_value(tint);

  *color = ColorTint(*color, *tint_value);

  return self;
}

void initializeColor() {
  rb_cColor = rb_define_class("Color", rb_cObject);

  rb_define_alloc_func(rb_cColor, rb_color_alloc);
  rb_define_method(rb_cColor, "initialize", rb_color_initialize, -1);
  rb_define_method(rb_cColor, "red", rb_color_get_red, 0);
  rb_define_method(rb_cColor, "green", rb_color_get_green, 0);
  rb_define_method(rb_cColor, "blue", rb_color_get_blue, 0);
  rb_define_method(rb_cColor, "alpha", rb_color_get_alpha, 0);
  rb_define_method(rb_cColor, "red=", rb_color_set_red, 1);
  rb_define_method(rb_cColor, "green=", rb_color_set_green, 1);
  rb_define_method(rb_cColor, "blue=", rb_color_set_blue, 1);
  rb_define_method(rb_cColor, "alpha=", rb_color_set_alpha, 1);

  rb_define_method(rb_cColor, "fade", rb_fade, 1);
  rb_define_method(rb_cColor, "to_int", rb_color_to_int, 0);
  rb_define_method(rb_cColor, "normalize", rb_color_normalize, 0);
  rb_define_method(rb_cColor, "tint", rb_color_tint, 1);
}
