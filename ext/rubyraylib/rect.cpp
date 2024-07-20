#include "rect.hpp"

VALUE rb_cRect;

static VALUE rb_rect_initialize(VALUE self, VALUE x, VALUE y, VALUE width, VALUE height) {
  RayRectangle *rect = get_rect(self);

  rect->x = NUM2DBL(x);
  rect->y = NUM2DBL(y);
  rect->width = NUM2DBL(width);
  rect->height = NUM2DBL(height);

  return self;
}

RB_RECT_GETTER(rb_rect_get_x, x)
RB_RECT_GETTER(rb_rect_get_y, y)
RB_RECT_GETTER(rb_rect_get_width, width)
RB_RECT_GETTER(rb_rect_get_height, height)
RB_RECT_SETTER(rb_rect_set_x, x)
RB_RECT_SETTER(rb_rect_set_y, y)
RB_RECT_SETTER(rb_rect_set_width, width)
RB_RECT_SETTER(rb_rect_set_height, height)

// Draw a color-filled rectangle (RayRectangle version)
static VALUE rb_draw_rectangle_rec(VALUE self, VALUE color) {
  RayRectangle *rec = get_rect(self);
  Color *col = get_color(color);

  DrawRectangleRec(*rec, *col);

  return Qnil;
}

extern "C" void initializeRect() {
  rb_cRect = rb_define_class_under(rb_mRL, "Rect", rb_cObject);
  rb_define_alloc_func(rb_cRect, rb_object_alloc<RayRectangle>);

  rb_define_method(rb_cRect, "initialize", rb_rect_initialize, 4);
  rb_define_method(rb_cRect, "x", rb_rect_get_x, 0);
  rb_define_method(rb_cRect, "y", rb_rect_get_y, 0);
  rb_define_method(rb_cRect, "width", rb_rect_get_width, 0);
  rb_define_method(rb_cRect, "height", rb_rect_get_height, 0);

  rb_define_method(rb_cRect, "x=", rb_rect_set_x, 1);
  rb_define_method(rb_cRect, "y=", rb_rect_set_y, 1);
  rb_define_method(rb_cRect, "width=", rb_rect_set_width, 1);
  rb_define_method(rb_cRect, "height=", rb_rect_set_height, 1);

  rb_define_method(rb_cRect, "draw", rb_draw_rectangle_rec, 1);
}
