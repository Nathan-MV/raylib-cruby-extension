#include "draw.hpp"

// Setup canvas (framebuffer) to start drawing
static VALUE rb_begin_drawing(VALUE self) {
  rb_need_block();
  BeginDrawing();
  rb_yield(Qnil);
  EndDrawing();

  return Qnil;
}

// Set background color (framebuffer clear color)
static VALUE rb_clear_background(VALUE self, VALUE color) {
  Color *col = get_color(color);

  ClearBackground(*col);

  return Qnil;
}

// Draw current FPS
static VALUE rb_draw_fps(VALUE self, VALUE posX, VALUE posY) {
  int x = NUM2INT(posX);
  int y = NUM2INT(posY);

  DrawFPS(x, y);

  return Qnil;
}

// Draw a color-filled rectangle
static VALUE rb_draw_rectangle(VALUE posX, VALUE posY, VALUE width, VALUE height, VALUE color) {
  int x = NUM2INT(posX);
  int y = NUM2INT(posY);
  int w = NUM2INT(width);
  int h = NUM2INT(height);
  Color *col = get_color(color);

  DrawRectangle(x, y, w, h, *col);

  return Qnil;
}

// Draw a color-filled rectangle (Vector version)
static VALUE rb_draw_rectangle_v(VALUE position, VALUE size_val, VALUE color) {
  Vector2 *pos = get_vec2(position);
  Vector2 *size = get_vec2(size_val);
  Color *col = get_color(color);

  DrawRectangleV(*pos, *size, *col);

  return Qnil;
}

static VALUE rb_draw_rect(int argc, VALUE *argv, VALUE self) {
  switch (argc) {
  case 3:
    // void DrawRectangleV(Vector2 position, Vector2 size, Color color);
    rb_scan_args(argc, argv, "3", &argv[0], &argv[1], &argv[2]);
    rb_draw_rectangle_v(argv[0], argv[1], argv[2]);
    break;
  case 5:
    rb_scan_args(argc, argv, "5", &argv[0], &argv[1], &argv[2], &argv[3], &argv[4]);
    rb_draw_rectangle(argv[0], argv[1], argv[2], argv[3], argv[4]);
    break;
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments. Expected 3 or 5.");
    break;
  }

  return Qnil;
}

// Draw text using font and additional parameters
static VALUE rb_draw_text(VALUE self, VALUE text, VALUE posX, VALUE posY, VALUE fontSize, VALUE color) {
  const char *txt = StringValueCStr(text);
  int x = NUM2INT(posX);
  int y = NUM2INT(posY);
  int size = NUM2INT(fontSize);
  Color *col = get_color(color);

  DrawText(txt, x, y, size, *col);

  return Qnil;
}

// Initializes the Draw module and defines its functions
extern "C" void initializeDraw(void) {
  VALUE rb_cDraw = rb_define_module("Draw");

  rb_define_module_function(rb_cDraw, "begin", rb_begin_drawing, 0);
  rb_define_module_function(rb_cDraw, "clear", rb_clear_background, 1);
  rb_define_module_function(rb_cDraw, "fps", rb_draw_fps, 2);
  rb_define_module_function(rb_cDraw, "rect", rb_draw_rect, -1);
  rb_define_module_function(rb_cDraw, "text", rb_draw_text, 5);
}
