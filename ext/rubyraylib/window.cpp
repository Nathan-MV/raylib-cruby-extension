#include "window.hpp"

static VALUE rb_init_window(VALUE self, VALUE width, VALUE height, VALUE title) {
  InitWindow(NUM2INT(width), NUM2INT(height), StringValueCStr(title));

  return Qnil;
}

RB_METHOD(rb_close_window, CloseWindow)
RB_METHOD_BOOL(rb_window_should_close, WindowShouldClose)
RB_METHOD_BOOL(rb_window_ready, IsWindowReady)
RB_METHOD_BOOL(rb_window_fullscreen, IsWindowFullscreen)
RB_METHOD_BOOL(rb_window_hidden, IsWindowHidden)
RB_METHOD_BOOL(rb_window_minimized, IsWindowMinimized)
RB_METHOD_BOOL(rb_window_maximized, IsWindowMaximized)
RB_METHOD_BOOL(rb_window_focused, IsWindowFocused)
RB_METHOD_BOOL(rb_window_resized, IsWindowResized)
RB_METHOD_BOOL_ARG_UINT(rb_is_window_state, IsWindowState)
RB_METHOD_ARG_UINT(rb_set_window_state, SetWindowState)
RB_METHOD_ARG_UINT(rb_clear_window_state, ClearWindowState)
RB_METHOD(rb_toggle_fullscreen, ToggleFullscreen)
RB_METHOD(rb_toggle_borderless_windowed, ToggleBorderlessWindowed)
RB_METHOD(rb_maximize_window, MaximizeWindow)
RB_METHOD(rb_minimize_window, MinimizeWindow)
RB_METHOD(rb_restore_window, RestoreWindow)
RB_METHOD_ARG_IMAGE(rb_set_window_icon, SetWindowIcon)

static VALUE rb_set_window_icons(VALUE self, VALUE image, VALUE count) {
  Image *img = get_image(image);
	int count_val = NUM2INT(count);

  SetWindowIcons(img, count_val);

  return Qnil;
}

RB_METHOD_ARG_STR(rb_set_window_title, SetWindowTitle)
RB_METHOD_ARG_INT_2(rb_set_window_position, SetWindowPosition)
RB_METHOD_ARG_INT(rb_set_window_monitor, SetWindowMonitor)
RB_METHOD_ARG_INT_2(rb_set_window_min_size, SetWindowMinSize)
RB_METHOD_ARG_INT_2(rb_set_window_max_size, SetWindowMaxSize)
RB_METHOD_ARG_INT_2(rb_set_window_size, SetWindowSize)
RB_METHOD_ARG_FLOAT(rb_set_window_opacity, SetWindowOpacity)
RB_METHOD(rb_set_window_focused, SetWindowFocused)
RB_METHOD(rb_get_window_handle, GetWindowHandle)
RB_METHOD_INT(rb_get_screen_width, GetScreenWidth)
RB_METHOD_INT(rb_get_screen_height, GetScreenHeight)
RB_METHOD_INT(rb_get_render_width, GetRenderWidth)
RB_METHOD_INT(rb_get_render_height, GetRenderHeight)
RB_METHOD_INT(rb_get_monitor_count, GetMonitorCount)
RB_METHOD_INT(rb_get_current_monitor, GetCurrentMonitor)
RB_METHOD_VEC2_ARG_INT(rb_get_monitor_position, GetMonitorPosition)
RB_METHOD_INT_ARG(rb_get_monitor_width, GetMonitorWidth)
RB_METHOD_INT_ARG(rb_get_monitor_height, GetMonitorHeight)
RB_METHOD_INT_ARG(rb_get_monitor_physical_width, GetMonitorPhysicalWidth)
RB_METHOD_INT_ARG(rb_get_monitor_physical_height, GetMonitorPhysicalHeight)
RB_METHOD_INT_ARG(rb_get_monitor_refresh_rate, GetMonitorRefreshRate)
RB_METHOD_VEC2(rb_get_window_position, GetWindowPosition)
RB_METHOD_VEC2(rb_get_scale_dpi, GetWindowScaleDPI)
RB_METHOD_STR_ARG_INT(rb_get_monitor_name, GetMonitorName)
RB_METHOD_ARG_STR(rb_set_clipboard_text, SetClipboardText)
RB_METHOD_STR(rb_get_clipboard_text, GetClipboardText)
RB_METHOD(rb_enable_event_waiting, EnableEventWaiting)
RB_METHOD(rb_disable_event_waiting, DisableEventWaiting)

RB_METHOD(rb_show_cursor, ShowCursor)
RB_METHOD(rb_hide_cursor, HideCursor)
RB_METHOD_BOOL(rb_cursor_hidden, IsCursorHidden)
RB_METHOD(rb_enable_cursor, EnableCursor)
RB_METHOD(rb_disable_cursor, DisableCursor)
RB_METHOD_BOOL(rb_cursor_on_screen, IsCursorOnScreen)

// Timing-related functions
// RLAPI void SetTargetFPS(int fps);                                 // Set target FPS (maximum)
RB_METHOD_ARG_INT(rb_set_target_fps, SetTargetFPS)
// RLAPI float GetFrameTime(void);                                   // Get time in seconds for last frame drawn (delta time)
RB_METHOD_FLOAT(rb_get_frame_time, GetFrameTime)
// RLAPI double GetTime(void);                                       // Get elapsed time in seconds since InitWindow()
RB_METHOD_FLOAT(rb_get_time, GetTime)
// RLAPI int GetFPS(void);                                           // Get current FPS
RB_METHOD_INT(rb_get_fps, GetFPS)

void initializeWindow() {
  VALUE rb_mWindow = rb_define_module("Window");

  rb_define_module_function(rb_mWindow, "init", rb_init_window, 3);
  rb_define_module_function(rb_mWindow, "close", rb_close_window, 0);
  rb_define_module_function(rb_mWindow, "should_close?", rb_window_should_close, 0);
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
	rb_define_module_function(rb_mWindow, "icons", rb_set_window_icons, 2);
	rb_define_module_function(rb_mWindow, "title=", rb_set_window_title, 1);
	rb_define_module_function(rb_mWindow, "position", rb_set_window_position, 2);
	rb_define_module_function(rb_mWindow, "monitor=", rb_set_window_monitor, 1);
	rb_define_module_function(rb_mWindow, "min_size", rb_set_window_min_size, 2);
	rb_define_module_function(rb_mWindow, "max_size", rb_set_window_max_size, 2);
	rb_define_module_function(rb_mWindow, "size", rb_set_window_size, 2);
	rb_define_module_function(rb_mWindow, "opacity", rb_set_window_opacity, 1);
	rb_define_module_function(rb_mWindow, "focused", rb_set_window_focused, 0);
	rb_define_module_function(rb_mWindow, "handle", rb_get_window_handle, 0);
  rb_define_module_function(rb_mWindow, "screen_width", rb_get_screen_width, 0);
  rb_define_module_function(rb_mWindow, "screen_height", rb_get_screen_height, 0);
	rb_define_module_function(rb_mWindow, "render_width", rb_get_render_width, 0);
	rb_define_module_function(rb_mWindow, "render_height", rb_get_render_height, 0);
	rb_define_module_function(rb_mWindow, "monitor_count", rb_get_monitor_count, 0);
	rb_define_module_function(rb_mWindow, "current_monitor", rb_get_current_monitor, 0);
	rb_define_module_function(rb_mWindow, "monitor_position", rb_get_monitor_position, 1);
	rb_define_module_function(rb_mWindow, "monitor_width", rb_get_monitor_width, 1);
	rb_define_module_function(rb_mWindow, "monitor_height", rb_get_monitor_height, 1);
	rb_define_module_function(rb_mWindow, "monitor_physical_width", rb_get_monitor_physical_width, 1);
	rb_define_module_function(rb_mWindow, "monitor_physical_height", rb_get_monitor_physical_height, 1);
	rb_define_module_function(rb_mWindow, "refresh_rate", rb_get_monitor_refresh_rate, 1);
	rb_define_module_function(rb_mWindow, "window_position", rb_get_window_position, 0);
	rb_define_module_function(rb_mWindow, "scale_dpi", rb_get_scale_dpi, 0);
	rb_define_module_function(rb_mWindow, "monitor_name", rb_get_monitor_name, 1);
	rb_define_module_function(rb_mWindow, "clipboard_text=", rb_set_clipboard_text, 1);
	rb_define_module_function(rb_mWindow, "clipboard_text", rb_get_clipboard_text, 0);
	rb_define_module_function(rb_mWindow, "enable_event_waiting", rb_enable_event_waiting, 0);
	rb_define_module_function(rb_mWindow, "disable_event_waiting", rb_disable_event_waiting, 0);

	rb_define_module_function(rb_mWindow, "show_cursor", rb_show_cursor, 0);
	rb_define_module_function(rb_mWindow, "hide_cursor", rb_hide_cursor, 0);
	rb_define_module_function(rb_mWindow, "cursor_hidden?", rb_cursor_hidden, 0);
	rb_define_module_function(rb_mWindow, "enable_cursor", rb_enable_cursor, 0);
	rb_define_module_function(rb_mWindow, "disable_cursor", rb_disable_cursor, 0);
	rb_define_module_function(rb_mWindow, "cursor_on_screen?", rb_cursor_on_screen, 0);

  rb_define_module_function(rb_mWindow, "target_fps=", rb_set_target_fps, 1);
  rb_define_module_function(rb_mWindow, "frame_time", rb_get_frame_time, 0);
  rb_define_module_function(rb_mWindow, "time", rb_get_time, 0);
  rb_define_module_function(rb_mWindow, "fps", rb_get_fps, 0);
}
