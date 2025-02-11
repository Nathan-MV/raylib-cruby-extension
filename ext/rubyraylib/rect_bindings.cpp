#include <rect_bindings.h>

VALUE rb_cRect;

static auto rb_rect_initialize(int argc, VALUE *argv, VALUE self) {
  auto *rect = get_rect(self);

  // Default values
  auto x = 0.0f;
  auto y = 0.0f;
  auto width = 0.0f;
  auto height = 0.0f;

  // Parse arguments
  if (argc > 0) {
    x = NUM2DBL(argv[0]);
    y = NUM2DBL(argv[1]);
    width = NUM2DBL(argv[2]);
    height = NUM2DBL(argv[3]);
  }

  rect->x = x;
  rect->y = y;
  rect->width = width;
  rect->height = height;

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

// RLAPI void DrawRectangle(int posX, int posY, int width, int height, Color color);                        // Draw a color-filled rectangle
static auto rb_draw_rectangle(VALUE self, VALUE rb_pos_x, VALUE rb_pos_y, VALUE rb_width,
                              VALUE rb_height, VALUE rb_color) {
  auto posX = NUM2INT(rb_pos_x);
  auto posY = NUM2INT(rb_pos_y);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto *color = get_color(rb_color);

  DrawRectangle(posX, posY, width, height, *color);

  return Qnil;
}
// RLAPI void DrawRectangleV(Vector2 position, Vector2 size, Color color);                                  // Draw a color-filled rectangle (Vector version)
static auto rb_draw_rectangle_v(VALUE self, VALUE rb_position, VALUE rb_size, VALUE rb_color) {
  auto *position = get_vec2(rb_position);
  auto *size = get_vec2(rb_size);
  auto *color = get_color(rb_color);

  DrawRectangleV(*position, *size, *color);

  return Qnil;
}
// Draw a color-filled rectangle (RayRectangle version)
static auto rb_draw_rectangle_rec(VALUE self, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto *color = get_color(rb_color);

  DrawRectangleRec(*rect, *color);

  return self;
}
// RLAPI void DrawRectanglePro(RayRectangle rec, Vector2 origin, float rotation, Color color);                 // Draw a color-filled rectangle with pro parameters
static auto rb_draw_rectangle_pro(VALUE self, VALUE rb_origin, VALUE rb_rotation, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto *origin = get_vec2(rb_origin);
  auto rotation = NUM2DBL(rb_rotation);
  auto *color = get_color(rb_color);

  DrawRectanglePro(*rect, *origin, rotation, *color);

  return self;
}
// RLAPI void DrawRectangleGradientV(int posX, int posY, int width, int height, Color top, Color bottom); // Draw a vertical-gradient-filled rectangle
static auto rb_draw_rectangle_gradient_v(VALUE self, VALUE rb_top, VALUE rb_bottom) {
  auto *rect = get_rect(self);
  auto *top = get_color(rb_top);
  auto *bottom = get_color(rb_bottom);

  DrawRectangleGradientV(rect->x, rect->y, rect->width, rect->height, *top, *bottom);

  return self;
}
// RLAPI void DrawRectangleGradientH(int posX, int posY, int width, int height, Color left, Color right); // Draw a horizontal-gradient-filled rectangle
static auto rb_draw_rectangle_gradient_h(VALUE self, VALUE rb_left, VALUE rb_right) {
  auto *rect = get_rect(self);
  auto *left = get_color(rb_left);
  auto *right = get_color(rb_right);

  DrawRectangleGradientH(rect->x, rect->y, rect->width, rect->height, *left, *right);

  return self;
}
// RLAPI void DrawRectangleGradientEx(RayRectangle rec, Color topLeft, Color bottomLeft, Color topRight, Color bottomRight); // Draw a gradient-filled rectangle with custom vertex colors
static auto rb_draw_rectangle_gradient_ex(VALUE self, VALUE rb_top_left, VALUE rb_bottom_left, VALUE rb_top_right, VALUE rb_bottom_right) {
  auto *rect = get_rect(self);
  auto *top_left = get_color(rb_top_left);
  auto *bottom_left = get_color(rb_bottom_left);
  auto *top_right = get_color(rb_top_right);
  auto *bottom_right = get_color(rb_bottom_right);

  DrawRectangleGradientEx(*rect, *top_left, *bottom_left, *top_right, *bottom_right);

  return self;
}
// RLAPI void DrawRectangleLines(int posX, int posY, int width, int height, Color color);                   // Draw rectangle outline
static auto rb_draw_rectangle_lines(VALUE self, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto *color = get_color(rb_color);

  DrawRectangleLines(rect->x, rect->y, rect->width, rect->height, *color);

  return self;
}
// RLAPI void DrawRectangleLinesEx(RayRectangle rec, float lineThick, Color color);                            // Draw rectangle outline with extended parameters
static auto rb_draw_rectangle_lines_ex(VALUE self, VALUE rb_line_thick, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto lineThick = DBL2NUM(rb_line_thick);
  auto *color = get_color(rb_color);

  DrawRectangleLinesEx(*rect, lineThick, *color);

  return self;
}
// RLAPI void DrawRectangleRounded(RayRectangle rec, float roundness, int segments, Color color);              // Draw rectangle with rounded edges
static auto rb_draw_rectangle_rounded(VALUE self, VALUE rb_roundness, VALUE rb_segments, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto roundness = DBL2NUM(rb_roundness);
  auto segments = NUM2INT(rb_segments);
  auto *color = get_color(rb_color);

  DrawRectangleRounded(*rect, roundness, segments, *color);

  return self;
}
// RLAPI void DrawRectangleRoundedLines(RayRectangle rec, float roundness, int segments, Color color);         // Draw rectangle lines with rounded edges
static auto rb_draw_rectangle_rounded_lines(VALUE self, VALUE rb_roundness, VALUE rb_segments, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto roundness = DBL2NUM(rb_roundness);
  auto segments = NUM2INT(rb_segments);
  auto *color = get_color(rb_color);

  DrawRectangleRoundedLines(*rect, roundness, segments, *color);

  return self;
}
// RLAPI void DrawRectangleRoundedLinesEx(RayRectangle rec, float roundness, int segments, float lineThick, Color color); // Draw rectangle with rounded edges outline
static auto rb_draw_rectangle_rounded_lines_ex(VALUE self, VALUE rb_roundness, VALUE rb_segments, VALUE rb_line_thick, VALUE rb_color) {
  auto *rect = get_rect(self);
  auto roundness = DBL2NUM(rb_roundness);
  auto segments = NUM2INT(rb_segments);
  auto lineThick = DBL2NUM(rb_line_thick);
  auto *color = get_color(rb_color);

  DrawRectangleRoundedLinesEx(*rect, roundness, segments, lineThick, *color);

  return self;
}

// RLAPI bool CheckCollisionRecs(RayRectangle rec1, RayRectangle rec2);                                           // Check collision between two rectangles
static auto rb_check_collision_recs(VALUE self, VALUE rb_other) {
  auto *rect = get_rect(self);
  auto *other = get_rect(rb_other);

  auto result = CheckCollisionRecs(*rect, *other);

  return result ? Qtrue : Qfalse;
}
// RLAPI bool CheckCollisionPointRec(Vector2 point, RayRectangle rec);                                         // Check if point is inside rectangle
static auto rb_check_collision_point_rec(VALUE self, VALUE rb_point) {
  auto *rect = get_rect(self);
  auto *point = get_vec2(rb_point);

  auto result = CheckCollisionPointRec(*point, *rect);

  return result ? Qtrue : Qfalse;
}
// RLAPI RayRectangle GetCollisionRec(RayRectangle rec1, RayRectangle rec2);                                         // Get collision rectangle for two rectangles collision
static auto rb_get_collision_rec(VALUE self, VALUE rb_other) {
  auto *rect = get_rect(self);
  auto *other = get_rect(rb_other);

  *rect = GetCollisionRec(*rect, *other);

  return self;
}

extern "C" void Init_Rect() {
  rb_cRect = rb_define_class_under(rb_mRL, "Rect", rb_cObject);
  rb_define_alloc_func(rb_cRect, rb_object_alloc<RayRectangle>);

  rb_define_method(rb_cRect, "initialize", rb_rect_initialize, -1);
  rb_define_method(rb_cRect, "x", rb_rect_get_x, 0);
  rb_define_method(rb_cRect, "y", rb_rect_get_y, 0);
  rb_define_method(rb_cRect, "width", rb_rect_get_width, 0);
  rb_define_method(rb_cRect, "height", rb_rect_get_height, 0);

  rb_define_method(rb_cRect, "x=", rb_rect_set_x, 1);
  rb_define_method(rb_cRect, "y=", rb_rect_set_y, 1);
  rb_define_method(rb_cRect, "width=", rb_rect_set_width, 1);
  rb_define_method(rb_cRect, "height=", rb_rect_set_height, 1);

  rb_define_method(rb_cRect, "draw", rb_draw_rectangle_rec, 1);
  rb_define_method(rb_cRect, "draw_pro", rb_draw_rectangle_pro, 3);
  rb_define_method(rb_cRect, "draw_gradient_vertical", rb_draw_rectangle_gradient_v, 2);
  rb_define_method(rb_cRect, "draw_gradient_horizontal", rb_draw_rectangle_gradient_h, 2);
  rb_define_method(rb_cRect, "draw_gradient_ex", rb_draw_rectangle_gradient_ex, 4);
  rb_define_method(rb_cRect, "draw_lines", rb_draw_rectangle_lines, 1);
  rb_define_method(rb_cRect, "draw_lines_ex", rb_draw_rectangle_lines_ex, 2);
  rb_define_method(rb_cRect, "draw_rounded", rb_draw_rectangle_rounded, 3);
  rb_define_method(rb_cRect, "draw_rounded_lines", rb_draw_rectangle_rounded_lines, 3);
  rb_define_method(rb_cRect, "draw_rounded_lines_ex", rb_draw_rectangle_rounded_lines_ex, 4);
  rb_define_method(rb_cRect, "collides?", rb_check_collision_recs, 1);
  rb_define_method(rb_cRect, "point?", rb_check_collision_point_rec, 1);
  rb_define_method(rb_cRect, "collide_area", rb_get_collision_rec, 1);
}
