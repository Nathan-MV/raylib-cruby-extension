#include "rect.hpp"

VALUE rb_cRect;

static VALUE rb_rect_initialize(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height) {
  Rectangle *rect = get_rect(self);

  rect->x = NUM2INT(x);
  rect->y = NUM2INT(y);
  rect->width = NUM2INT(y);
  rect->height = NUM2INT(y);

  return self;
}

static VALUE rb_rect_get_x(VALUE self) {
  Rectangle *rect = get_rect(self);

  return INT2NUM(rect->x);
}

static VALUE rb_rect_get_y(VALUE self) {
  Rectangle *rect = get_rect(self);

  return INT2NUM(rect->y);
}

static VALUE rb_rect_get_width(VALUE self) {
  Rectangle *rect = get_rect(self);

  return INT2NUM(rect->width);
}

static VALUE rb_rect_get_height(VALUE self) {
  Rectangle *rect = get_rect(self);

  return INT2NUM(rect->height);
}

static VALUE rb_rect_set_x(VALUE self, VALUE value) {
  Rectangle *rect = get_rect(self);

  rect->x = NUM2INT(value);

  return self;
}

static VALUE rb_rect_set_y(VALUE self, VALUE value) {
  Rectangle *rect = get_rect(self);

  rect->y = NUM2INT(value);

  return self;
}

static VALUE rb_rect_set_width(VALUE self, VALUE value) {
  Rectangle *rect = get_rect(self);

  rect->width = NUM2INT(value);

  return self;
}

static VALUE rb_rect_set_height(VALUE self, VALUE value) {
  Rectangle *rect = get_rect(self);

  rect->height = NUM2INT(value);

  return self;
}

extern "C" void initializeRect() {
  rb_cRect = rb_define_class("Rect", rb_cObject);
  rb_define_alloc_func(rb_cRect, rb_object_alloc<Rectangle>);

  rb_define_method(rb_cRect, "initialize", rb_rect_initialize, 4);
  rb_define_method(rb_cRect, "x", rb_rect_get_x, 0);
  rb_define_method(rb_cRect, "y", rb_rect_get_y, 0);
  rb_define_method(rb_cRect, "width", rb_rect_get_width, 0);
  rb_define_method(rb_cRect, "height", rb_rect_get_height, 0);
  rb_define_method(rb_cRect, "x=", rb_rect_set_x, 1);
  rb_define_method(rb_cRect, "y=", rb_rect_set_y, 1);
  rb_define_method(rb_cRect, "width=", rb_rect_set_width, 1);
  rb_define_method(rb_cRect, "height=", rb_rect_set_height, 1);
}
