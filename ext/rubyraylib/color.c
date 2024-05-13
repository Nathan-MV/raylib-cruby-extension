#include "color.h"

// Ruby method to allocate memory for a new Color
static VALUE color_alloc(VALUE klass) {
  Color *col;
  VALUE obj = Data_Make_Struct(klass, Color, 0, -1, col);
  return obj;
}

// Ruby method to create a new Color object
static VALUE rb_color_initialize(int argc, VALUE *argv, VALUE self) {
  VALUE r, g, b, a;
  Color *color;

  // Parse the arguments
  rb_scan_args(argc, argv, "31", &r, &g, &b, &a);

  // Set default value of a to 255 if not provided
  if (argc < 4) {
    a = INT2NUM(255);
  }

  Data_Get_Struct(self, Color, color);

  color->r = NUM2INT(r);
  color->g = NUM2INT(g);
  color->b = NUM2INT(b);
  color->a = NUM2INT(a);

  return self;
}

// Ruby method to get the red component of a Color object
static VALUE rb_color_get_red(VALUE self) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  return INT2NUM(color->r);
}

// Ruby method to get the green component of a Color object
static VALUE rb_color_get_green(VALUE self) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  return INT2NUM(color->g);
}

// Ruby method to get the blue component of a Color object
static VALUE rb_color_get_blue(VALUE self) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  return INT2NUM(color->b);
}

// Ruby method to get the alpha component of a Color object
static VALUE rb_color_get_alpha(VALUE self) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  return INT2NUM(color->a);
}

// Ruby method to set the red component of a Color object
static VALUE rb_color_set_red(VALUE self, VALUE value) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  color->r = NUM2INT(value);

  return self;
}

// Ruby method to set the green component of a Color object
static VALUE rb_color_set_green(VALUE self, VALUE value) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  color->g = NUM2INT(value);

  return self;
}

// Ruby method to set the blue component of a Color object
static VALUE rb_color_set_blue(VALUE self, VALUE value) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  color->b = NUM2INT(value);

  return self;
}

// Ruby method to set the alpha component of a Color object
static VALUE rb_color_set_alpha(VALUE self, VALUE value) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  color->a = NUM2INT(value);

  return self;
}

// Ruby method to convert Color to integer
static VALUE rb_color_to_int(VALUE self) {
  Color *color;
  Data_Get_Struct(self, Color, color);

  int result = ColorToInt(*color); // Call the ColorToInt function

  return INT2NUM(result);
}

void initializeColor() {
  VALUE rb_cColor = rb_define_class("Color", rb_cObject);

  rb_define_alloc_func(rb_cColor, color_alloc);
  rb_define_method(rb_cColor, "initialize", rb_color_initialize, -1);
  rb_define_method(rb_cColor, "red", rb_color_get_red, 0);
  rb_define_method(rb_cColor, "green", rb_color_get_green, 0);
  rb_define_method(rb_cColor, "blue", rb_color_get_blue, 0);
  rb_define_method(rb_cColor, "alpha", rb_color_get_alpha, 0);
  rb_define_method(rb_cColor, "red=", rb_color_set_red, 1);
  rb_define_method(rb_cColor, "green=", rb_color_set_green, 1);
  rb_define_method(rb_cColor, "blue=", rb_color_set_blue, 1);
  rb_define_method(rb_cColor, "alpha=", rb_color_set_alpha, 1);

  rb_define_method(rb_cColor, "to_int", rb_color_to_int, 0);
}
