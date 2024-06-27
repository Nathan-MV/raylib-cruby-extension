#include "window.h"

static VALUE rb_init_window(VALUE self, VALUE width, VALUE height,
                            VALUE title) {
  InitWindow(NUM2INT(width), NUM2INT(height), StringValueCStr(title));

  return Qnil;
}

static VALUE rb_close_window(VALUE self) {
  CloseWindow();

  return Qnil;
}

static VALUE rb_window_should_close(VALUE self) {
  return WindowShouldClose() ? Qtrue : Qfalse;
}

static VALUE rb_window_ready(VALUE self) {
  return IsWindowReady() ? Qtrue : Qfalse;
}

static VALUE rb_window_fullscreen(VALUE self) {
  return IsWindowFullscreen() ? Qtrue : Qfalse;
}

static VALUE rb_window_hidden(VALUE self) {
  return IsWindowHidden() ? Qtrue : Qfalse;
}

static VALUE rb_window_minimized(VALUE self) {
  return IsWindowMinimized() ? Qtrue : Qfalse;
}

static VALUE rb_window_maximized(VALUE self) {
  return IsWindowMaximized() ? Qtrue : Qfalse;
}

static VALUE rb_window_focused(VALUE self) {
  return IsWindowFocused() ? Qtrue : Qfalse;
}

static VALUE rb_window_resized(VALUE self) {
  return IsWindowResized() ? Qtrue : Qfalse;
}

static VALUE rb_is_window_state(VALUE self, VALUE flag) {
  unsigned int state_flag = NUM2UINT(flag);
  bool result = IsWindowState(state_flag);

  return result ? Qtrue : Qfalse;
}

static VALUE rb_set_window_state(VALUE self, VALUE flags) {
  unsigned int state_flags = NUM2UINT(flags);
  SetWindowState(state_flags);

  return Qnil;
}

static VALUE rb_clear_window_state(VALUE self, VALUE flags) {
  unsigned int state_flags = NUM2UINT(flags);
  ClearWindowState(state_flags);

  return Qnil;
}

static VALUE rb_toggle_fullscreen(VALUE self) {
  ToggleFullscreen();

  return Qnil;
}

static VALUE rb_toggle_borderless_windowed(VALUE self) {
  ToggleBorderlessWindowed();

  return Qnil;
}

static VALUE rb_maximize_window(VALUE self) {
  MaximizeWindow();

  return Qnil;
}

static VALUE rb_minimize_window(VALUE self) {
  MinimizeWindow();

  return Qnil;
}

static VALUE rb_restore_window(VALUE self) {
  RestoreWindow();

  return Qnil;
}

static VALUE rb_set_window_icon(VALUE self, VALUE image) {
  const char *file_name_str = StringValueCStr(image);
  Image *img = ALLOC(Image);
  *img = LoadImage(file_name_str);

  Data_Wrap_Struct(rb_cObject, NULL, free, img);
  SetWindowIcon(*img);

  return Qnil;
}

static VALUE rb_get_screen_width(VALUE self) {
  int screenWidth = GetScreenWidth();
  return INT2NUM(screenWidth);
}

static VALUE rb_get_screen_height(VALUE self) {
  int screenHeight = GetScreenHeight();
  return INT2NUM(screenHeight);
}

void initializeWindow() {
  VALUE rb_mWindow = rb_define_module("Window");

  rb_define_module_function(rb_mWindow, "init", rb_init_window, 3);
  rb_define_module_function(rb_mWindow, "close", rb_close_window, 0);
  rb_define_module_function(rb_mWindow, "should_close?", rb_window_should_close,
                            0);
  rb_define_module_function(rb_mWindow, "ready?", rb_window_ready, 0);
  rb_define_module_function(rb_mWindow, "fullscreen?", rb_window_fullscreen, 0);
  rb_define_module_function(rb_mWindow, "hidden?", rb_window_hidden, 0);
  rb_define_module_function(rb_mWindow, "minimized?", rb_window_minimized, 0);
  rb_define_module_function(rb_mWindow, "maximized?", rb_window_maximized, 0);
  rb_define_module_function(rb_mWindow, "focused?", rb_window_focused, 0);
  rb_define_module_function(rb_mWindow, "resized?", rb_window_resized, 0);
  rb_define_module_function(rb_mWindow, "state?", rb_is_window_state, 1);
  rb_define_module_function(rb_mWindow, "state=", rb_set_window_state, 1);
  rb_define_module_function(rb_mWindow, "clear_state", rb_clear_window_state, 1);
  rb_define_module_function(rb_mWindow, "fullscreen", rb_toggle_fullscreen, 0);
  rb_define_module_function(rb_mWindow, "borderless_windowed", rb_toggle_borderless_windowed, 0);
  rb_define_module_function(rb_mWindow, "maximize", rb_maximize_window, 0);
  rb_define_module_function(rb_mWindow, "minimize", rb_minimize_window, 0);
  rb_define_module_function(rb_mWindow, "restore", rb_restore_window, 0);
  rb_define_module_function(rb_mWindow, "icon=", rb_set_window_icon, 1);

  rb_define_module_function(rb_mWindow, "screen_width", rb_get_screen_width, 0);
  rb_define_module_function(rb_mWindow, "screen_height", rb_get_screen_height,
                            0);
}