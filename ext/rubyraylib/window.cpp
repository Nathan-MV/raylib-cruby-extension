#include "window.hpp"

// RLAPI void InitWindow(int width, int height, const char *title);  // Initialize window and OpenGL context
static VALUE rb_init_window(VALUE self, VALUE width, VALUE height, VALUE title) {
  InitWindow(NUM2INT(width), NUM2INT(height), StringValueCStr(title));

  return Qnil;
}
// RLAPI void CloseWindow(void);                                     // Close window and unload OpenGL context
RB_METHOD(rb_close_window, CloseWindow)
// RLAPI bool WindowShouldClose(void);                               // Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
RB_METHOD_BOOL(rb_window_should_close, WindowShouldClose)
// RLAPI bool IsWindowReady(void);                                   // Check if window has been initialized successfully
RB_METHOD_BOOL(rb_window_ready, IsWindowReady)
// RLAPI bool IsWindowFullscreen(void);                              // Check if window is currently fullscreen
RB_METHOD_BOOL(rb_window_fullscreen, IsWindowFullscreen)
// RLAPI bool IsWindowHidden(void);                                  // Check if window is currently hidden (only PLATFORM_DESKTOP)
RB_METHOD_BOOL(rb_window_hidden, IsWindowHidden)
// RLAPI bool IsWindowMinimized(void);                               // Check if window is currently minimized (only PLATFORM_DESKTOP)
RB_METHOD_BOOL(rb_window_minimized, IsWindowMinimized)
// RLAPI bool IsWindowMaximized(void);                               // Check if window is currently maximized (only PLATFORM_DESKTOP)
RB_METHOD_BOOL(rb_window_maximized, IsWindowMaximized)
// RLAPI bool IsWindowFocused(void);                                 // Check if window is currently focused (only PLATFORM_DESKTOP)
RB_METHOD_BOOL(rb_window_focused, IsWindowFocused)
// RLAPI bool IsWindowResized(void);                                 // Check if window has been resized last frame
RB_METHOD_BOOL(rb_window_resized, IsWindowResized)
// RLAPI bool IsWindowState(unsigned int flag);                      // Check if one specific window flag is enabled
RB_METHOD_BOOL_ARG_UINT(rb_is_window_state, IsWindowState)
// RLAPI void SetWindowState(unsigned int flags);                    // Set window configuration state using flags (only PLATFORM_DESKTOP)
RB_METHOD_ARG_UINT(rb_set_window_state, SetWindowState)
// RLAPI void ClearWindowState(unsigned int flags);                  // Clear window configuration state flags
RB_METHOD_ARG_UINT(rb_clear_window_state, ClearWindowState)
// RLAPI void ToggleFullscreen(void);                                // Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
RB_METHOD(rb_toggle_fullscreen, ToggleFullscreen)
// RLAPI void ToggleBorderlessWindowed(void);                        // Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
RB_METHOD(rb_toggle_borderless_windowed, ToggleBorderlessWindowed)
// RLAPI void MaximizeWindow(void);                                  // Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
RB_METHOD(rb_maximize_window, MaximizeWindow)
// RLAPI void MinimizeWindow(void);                                  // Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
RB_METHOD(rb_minimize_window, MinimizeWindow)
// RLAPI void RestoreWindow(void);                                   // Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
RB_METHOD(rb_restore_window, RestoreWindow)
// RLAPI void SetWindowIcon(Image image);                            // Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
RB_METHOD_ARG_IMAGE(rb_set_window_icon, SetWindowIcon)
// RLAPI void SetWindowIcons(Image *images, int count);              // Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
static VALUE rb_set_window_icons(VALUE self, VALUE image, VALUE count) {
  Image *img = get_image(image);
	int count_val = NUM2INT(count);

  SetWindowIcons(img, count_val);

  return Qnil;
}
// RLAPI void SetWindowTitle(const char *title);                     // Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
RB_METHOD_ARG_STR(rb_set_window_title, SetWindowTitle)
// RLAPI void SetWindowPosition(int x, int y);                       // Set window position on screen (only PLATFORM_DESKTOP)
RB_METHOD_ARG_INT_2(rb_set_window_position, SetWindowPosition)
// RLAPI void SetWindowMonitor(int monitor);                         // Set monitor for the current window
RB_METHOD_ARG_INT(rb_set_window_monitor, SetWindowMonitor)
// RLAPI void SetWindowMinSize(int width, int height);               // Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
RB_METHOD_ARG_INT_2(rb_set_window_min_size, SetWindowMinSize)
// RLAPI void SetWindowMaxSize(int width, int height);               // Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
RB_METHOD_ARG_INT_2(rb_set_window_max_size, SetWindowMaxSize)
// RLAPI void SetWindowSize(int width, int height);                  // Set window dimensions
RB_METHOD_ARG_INT_2(rb_set_window_size, SetWindowSize)
// RLAPI void SetWindowOpacity(float opacity);                       // Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
RB_METHOD_ARG_FLOAT(rb_set_window_opacity, SetWindowOpacity)
// RLAPI void SetWindowFocused(void);                                // Set window focused (only PLATFORM_DESKTOP)
RB_METHOD(rb_set_window_focused, SetWindowFocused)
// RLAPI void *GetWindowHandle(void);                                // Get native window handle
RB_METHOD(rb_get_window_handle, GetWindowHandle)
// RLAPI int GetScreenWidth(void);                                   // Get current screen width
RB_METHOD_INT(rb_get_screen_width, GetScreenWidth)
// RLAPI int GetScreenHeight(void);                                  // Get current screen height
RB_METHOD_INT(rb_get_screen_height, GetScreenHeight)
// RLAPI int GetRenderWidth(void);                                   // Get current render width (it considers HiDPI)
RB_METHOD_INT(rb_get_render_width, GetRenderWidth)
// RLAPI int GetRenderHeight(void);                                  // Get current render height (it considers HiDPI)
RB_METHOD_INT(rb_get_render_height, GetRenderHeight)
// RLAPI int GetMonitorCount(void);                                  // Get number of connected monitors
RB_METHOD_INT(rb_get_monitor_count, GetMonitorCount)
// RLAPI int GetCurrentMonitor(void);                                // Get current connected monitor
RB_METHOD_INT(rb_get_current_monitor, GetCurrentMonitor)
// RLAPI Vector2 GetMonitorPosition(int monitor);                    // Get specified monitor position
RB_METHOD_VEC2_ARG_INT(rb_get_monitor_position, GetMonitorPosition)
// RLAPI int GetMonitorWidth(int monitor);                           // Get specified monitor width (current video mode used by monitor)
RB_METHOD_INT_ARG(rb_get_monitor_width, GetMonitorWidth)
// RLAPI int GetMonitorHeight(int monitor);                          // Get specified monitor height (current video mode used by monitor)
RB_METHOD_INT_ARG(rb_get_monitor_height, GetMonitorHeight)
// RLAPI int GetMonitorPhysicalWidth(int monitor);                   // Get specified monitor physical width in millimetres
RB_METHOD_INT_ARG(rb_get_monitor_physical_width, GetMonitorPhysicalWidth)
// RLAPI int GetMonitorPhysicalHeight(int monitor);                  // Get specified monitor physical height in millimetres
RB_METHOD_INT_ARG(rb_get_monitor_physical_height, GetMonitorPhysicalHeight)
// RLAPI int GetMonitorRefreshRate(int monitor);                     // Get specified monitor refresh rate
RB_METHOD_INT_ARG(rb_get_monitor_refresh_rate, GetMonitorRefreshRate)
// RLAPI Vector2 GetWindowPosition(void);                            // Get window position XY on monitor
RB_METHOD_VEC2(rb_get_window_position, GetWindowPosition)
// RLAPI Vector2 GetWindowScaleDPI(void);                            // Get window scale DPI factor
RB_METHOD_VEC2(rb_get_scale_dpi, GetWindowScaleDPI)
// RLAPI const char *GetMonitorName(int monitor);                    // Get the human-readable, UTF-8 encoded name of the specified monitor
RB_METHOD_STR_ARG_INT(rb_get_monitor_name, GetMonitorName)
// RLAPI void SetClipboardText(const char *text);                    // Set clipboard text content
RB_METHOD_ARG_STR(rb_set_clipboard_text, SetClipboardText)
// RLAPI const char *GetClipboardText(void);                         // Get clipboard text content
RB_METHOD_STR(rb_get_clipboard_text, GetClipboardText)
// RLAPI void EnableEventWaiting(void);                              // Enable waiting for events on EndDrawing(), no automatic event polling
RB_METHOD(rb_enable_event_waiting, EnableEventWaiting)
// RLAPI void DisableEventWaiting(void);                             // Disable waiting for events on EndDrawing(), automatic events polling
RB_METHOD(rb_disable_event_waiting, DisableEventWaiting)

// Cursor-related functions
// RLAPI void ShowCursor(void);                                      // Shows cursor
RB_METHOD(rb_show_cursor, ShowCursor)
// RLAPI void HideCursor(void);                                      // Hides cursor
RB_METHOD(rb_hide_cursor, HideCursor)
// RLAPI bool IsCursorHidden(void);                                  // Check if cursor is not visible
RB_METHOD_BOOL(rb_cursor_hidden, IsCursorHidden)
// RLAPI void EnableCursor(void);                                    // Enables cursor (unlock cursor)
RB_METHOD(rb_enable_cursor, EnableCursor)
// RLAPI void DisableCursor(void);                                   // Disables cursor (lock cursor)
RB_METHOD(rb_disable_cursor, DisableCursor)
// RLAPI bool IsCursorOnScreen(void);                                // Check if cursor is on the screen
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

// RLAPI void DrawFPS(int posX, int posY);                                                     // Draw current FPS
RB_METHOD_ARG_INT_2(rb_draw_fps, DrawFPS)

// Custom frame control functions
// NOTE: Those functions are intended for advanced users that want full control
// over the frame processing By default EndDrawing() does this job: draws
// everything + SwapScreenBuffer() + manage frame timing + PollInputEvents() To
// avoid that behaviour and control frame processes manually, enable in
// config.h: SUPPORT_CUSTOM_FRAME_CONTROL
// RLAPI void SwapScreenBuffer(void); // Swap back buffer with front buffer (screen drawing)
// RLAPI void PollInputEvents(void); // Register all input events
// RLAPI void WaitTime(double seconds); // Wait for some time (halt program execution)

// Misc. functions
// RLAPI void TakeScreenshot(const char *fileName); // Takes a screenshot of current screen
//                                       // (filename extension defines format)
// RLAPI void SetConfigFlags(unsigned int flags); // Setup init configuration flags (view FLAGS)
// RLAPI void OpenURL(const char *url); // Open URL with default system browser (if available)

extern "C" void initializeWindow() {
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
  rb_define_module_function(rb_mWindow, "clear_state", rb_clear_window_state,
                            1);
  rb_define_module_function(rb_mWindow, "fullscreen", rb_toggle_fullscreen, 0);
  rb_define_module_function(rb_mWindow, "borderless_windowed",
                            rb_toggle_borderless_windowed, 0);
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
  rb_define_module_function(rb_mWindow, "screen_height", rb_get_screen_height,
                            0);
  rb_define_module_function(rb_mWindow, "render_width", rb_get_render_width, 0);
  rb_define_module_function(rb_mWindow, "render_height", rb_get_render_height,
                            0);
  rb_define_module_function(rb_mWindow, "monitor_count", rb_get_monitor_count,
                            0);
  rb_define_module_function(rb_mWindow, "current_monitor",
                            rb_get_current_monitor, 0);
  rb_define_module_function(rb_mWindow, "monitor_position",
                            rb_get_monitor_position, 1);
  rb_define_module_function(rb_mWindow, "monitor_width", rb_get_monitor_width,
                            1);
  rb_define_module_function(rb_mWindow, "monitor_height", rb_get_monitor_height,
                            1);
  rb_define_module_function(rb_mWindow, "monitor_physical_width",
                            rb_get_monitor_physical_width, 1);
  rb_define_module_function(rb_mWindow, "monitor_physical_height",
                            rb_get_monitor_physical_height, 1);
  rb_define_module_function(rb_mWindow, "refresh_rate",
                            rb_get_monitor_refresh_rate, 1);
  rb_define_module_function(rb_mWindow, "window_position",
                            rb_get_window_position, 0);
  rb_define_module_function(rb_mWindow, "scale_dpi", rb_get_scale_dpi, 0);
  rb_define_module_function(rb_mWindow, "monitor_name", rb_get_monitor_name, 1);
  rb_define_module_function(rb_mWindow,
                            "clipboard_text=", rb_set_clipboard_text, 1);
  rb_define_module_function(rb_mWindow, "clipboard_text", rb_get_clipboard_text,
                            0);
  rb_define_module_function(rb_mWindow, "enable_event_waiting",
                            rb_enable_event_waiting, 0);
  rb_define_module_function(rb_mWindow, "disable_event_waiting",
                            rb_disable_event_waiting, 0);

  rb_define_module_function(rb_mWindow, "show_cursor", rb_show_cursor, 0);
  rb_define_module_function(rb_mWindow, "hide_cursor", rb_hide_cursor, 0);
  rb_define_module_function(rb_mWindow, "cursor_hidden?", rb_cursor_hidden, 0);
  rb_define_module_function(rb_mWindow, "enable_cursor", rb_enable_cursor, 0);
  rb_define_module_function(rb_mWindow, "disable_cursor", rb_disable_cursor, 0);
  rb_define_module_function(rb_mWindow, "cursor_on_screen?",
                            rb_cursor_on_screen, 0);

  rb_define_module_function(rb_mWindow, "target_fps=", rb_set_target_fps, 1);
  rb_define_module_function(rb_mWindow, "frame_time", rb_get_frame_time, 0);
  rb_define_module_function(rb_mWindow, "time", rb_get_time, 0);
  rb_define_module_function(rb_mWindow, "fps", rb_get_fps, 0);

  rb_define_module_function(rb_mWindow, "show_fps", rb_draw_fps, 2);

  // Set to try enabling V-Sync on GPU
  rb_define_const(rb_mWindow, "VSYNC", INT2NUM(0x00000040));
  // Set to run program in fullscreen
  rb_define_const(rb_mWindow, "FULLSCREEN", INT2NUM(0x00000002));
  // Set to allow resizable window
  rb_define_const(rb_mWindow, "RESIZABLE", INT2NUM(0x00000004));
  // Set to disable window decoration (frame and buttons)
  rb_define_const(rb_mWindow, "UNDECORATED", INT2NUM(0x00000008));
  // Set to hide window
  rb_define_const(rb_mWindow, "HIDDEN", INT2NUM(0x00000080));
  // Set to minimize window (iconify)
  rb_define_const(rb_mWindow, "MINIMIZED", INT2NUM(0x00000200));
  // Set to maximize window (expanded to monitor)
  rb_define_const(rb_mWindow, "MAXIMIZED", INT2NUM(0x00000400));
  // Set to window non focused
  rb_define_const(rb_mWindow, "UNFOCUSED", INT2NUM(0x00000800));
  // Set to window always on top
  rb_define_const(rb_mWindow, "TOPMOST", INT2NUM(0x00001000));
  // Set to allow windows running while minimized
  rb_define_const(rb_mWindow, "ALWAYS_RUN", INT2NUM(0x00000100));
  // Set to allow transparent framebuffer
  rb_define_const(rb_mWindow, "TRANSPARENT", INT2NUM(0x00000010));
  // Set to support HighDPI
  rb_define_const(rb_mWindow, "HIGHDPI", INT2NUM(0x00002000));
  // Set to support mouse passthrough, only supported when FLAG_WINDOW_UNDECORATED
  rb_define_const(rb_mWindow, "MOUSE_PASSTHROUGH", INT2NUM(0x00004000));
  // Set to run program in borderless windowed mode
  rb_define_const(rb_mWindow, "BORDERLESS_WINDOWED", INT2NUM(0x00008000));
  // Set to try enabling MSAA 4X
  rb_define_const(rb_mWindow, "MSAA_4X", INT2NUM(0x00000020));
  // Set to try enabling interlaced video format (for V3D)
  rb_define_const(rb_mWindow, "INTERLACED", INT2NUM(0x00010000));
}
