# frozen_string_literal: true

module RL
  module Window
    # @!parse VSYNC = 0x00000040
    #   Window flag
    #   return [Integer]

    # @!parse FULLSCREEN = 0x00000002
    #   Window flag
    #   return [Integer]

    # @!parse RESIZABLE = 0x00000004
    #   Window flag
    #   return [Integer]

    # @!parse UNDECORATED = 0x00000008
    #   Window flag
    #   return [Integer]

    # @!parse HIDDEN = 0x00000080
    #   Window flag
    #   return [Integer]

    # @!parse MINIMIZED = 0x00000200
    #   Window flag
    #   return [Integer]

    # @!parse MAXIMIZED = 0x00000400
    #   Window flag
    #   return [Integer]

    # @!parse UNFOCUSED = 0x00000800
    #   Window flag
    #   return [Integer]

    # @!parse TOPMOST = 0x00001000
    #   Window flag
    #   return [Integer]

    # @!parse ALWAYS_RUN = 0x00000100
    #   Window flag
    #   return [Integer]

    # @!parse TRANSPARENT = 0x00000010
    #   Window flag
    #   return [Integer]

    # @!parse HIGHDPI = 0x00002000
    #   Window flag
    #   return [Integer]

    # @!parse MOUSE_PASSTHROUGH = 0x00004000
    #   Window flag
    #   return [Integer]

    # @!parse BORDERLESS_WINDOWED = 0x00008000
    #   Window flag
    #   return [Integer]

    # @!parse MSAA_4X = 0x00000020
    #   Window flag
    #   return [Integer]

    # @!parse INTERLACED = 0x00010000
    #   Window flag
    #   return [Integer]

    # @!method init
    #   Initialize window and OpenGL context
    #   @param width [Integer]
    #   @param height [Integer]
    #   @param title [String]
    #   @return [void]

    # @!method close
    #   Close window and unload OpenGL context
    #   @return [void]

    # @!method should_close?
    #   Check if application should close (KEY_ESCAPE pressed or windows close icon clicked)
    #   @return [void]

    # @!method ready?
    #   Check if window has been initialized successfully
    #   @return [void]

    # @!method fullscreen?
    #   Check if window is currently fullscreen
    #   @return [void]

    # @!method hidden?
    #   Check if window is currently hidden (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method minimized?
    #   Check if window is currently minimized (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method maximized?
    #   Check if window is currently maximized (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method focused?
    #   Check if window is currently focused (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method resized?
    #   Check if window has been resized last frame
    #   @return [void]

    # @!method state?
    #   Check if one specific window flag is enabled
    #   @param flags [Integer]
    #   @return [void]

    # @!method state=
    #   Set window configuration state using flags (only PLATFORM_DESKTOP)
    #   @param flags [Integer]
    #   @return [void]

    # @!method clear_state
    #   Clear window configuration state flags
    #   @param flags [Integer]
    #   @return [void]

    # @!method fullscreen
    #   Toggle window state: fullscreen/windowed (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method borderless_windowed
    #   Toggle window state: borderless windowed (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method maximize
    #   Set window state: maximized, if resizable (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method minimize
    #   Set window state: minimized, if resizable (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method restore
    #   Set window state: not minimized/maximized (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method icon=
    #   Set icon for window (single image, RGBA 32bit, only PLATFORM_DESKTOP)
    #   @param image [Image]
    #   @return [void]

    # @!method icons
    #   Set icon for window (multiple images, RGBA 32bit, only PLATFORM_DESKTOP)
    #   @param image [Image]
    #   @param count [Integer]
    #   @return [void]

    # @!method title=
    #   Set title for window (only PLATFORM_DESKTOP and PLATFORM_WEB)
    #   @param title [String]
    #   @return [void]

    # @!method position
    #   Set window position on screen (only PLATFORM_DESKTOP)
    #   @param x [Integer]
    #   @param y [Integer]
    #   @return [void]

    # @!method monitor=
    #   Set monitor for the current window
    #   @param monitor [Integer]
    #   @return [void]

    # @!method min_size
    #   Set window minimum dimensions (for FLAG_WINDOW_RESIZABLE)
    #   @param width [Integer]
    #   @param height [Integer]
    #   @return [void]

    # @!method max_size
    #   Set window maximum dimensions (for FLAG_WINDOW_RESIZABLE)
    #   @param width [Integer]
    #   @param height [Integer]
    #   @return [void]

    # @!method size
    #   Set window dimensions
    #   @param width [Integer]
    #   @param height [Integer]
    #   @return [void]

    # @!method opacity=
    #   Set window opacity [0.0f..1.0f] (only PLATFORM_DESKTOP)
    #   @param opacity [Float]
    #   @return [void]

    # @!method focused
    #   Set window focused (only PLATFORM_DESKTOP)
    #   @return [void]

    # @!method handle
    #   Get native window handle
    #   @return [void]

    # @!method screen_width
    #   Get current screen width
    #   @return [void]

    # @!method screen_height
    #   Get current screen height
    #   @return [void]

    # @!method render_width
    #   Get current render width (it considers HiDPI)
    #   @return [void]

    # @!method render_height
    #   Get current render height (it considers HiDPI)
    #   @return [void]

    # @!method monitor_count
    #   Get number of connected monitors
    #   @return [void]

    # @!method current_monitor
    #   Get current connected monitor
    #   @return [void]

    # @!method monitor_position
    #   Get specified monitor position
    #   @param monitor [Integer]
    #   @return [void]

    # @!method monitor_width
    #   Get specified monitor width (current video mode used by monitor)
    #   @param monitor [Integer]
    #   @return [void]

    # @!method monitor_height
    #   Get specified monitor height (current video mode used by monitor)
    #   @param monitor [Integer]
    #   @return [void]

    # @!method monitor_physical_width
    #   Get specified monitor physical width in millimetres
    #   @param monitor [Integer]
    #   @return [void]

    # @!method monitor_physical_height
    #   Get specified monitor physical height in millimetres
    #   @param monitor [Integer]
    #   @return [void]

    # @!method refresh_rate
    #   Get specified monitor refresh rate
    #   @param monitor [Integer]
    #   @return [void]

    # @!method window_position
    #   Get window position XY on monitor
    #   @return [void]

    # @!method scale_dpi
    #   Get window scale DPI factor
    #   @return [void]

    # @!method monitor_name
    #   Get the human-readable, UTF-8 encoded name of the specified monitor
    #   @param monitor [Integer]
    #   @return [void]

    # @!method clipboard_text=
    #   Set clipboard text content
    #   @param text [String]
    #   @return [void]

    # @!method clipboard_text
    #   Set clipboard text content
    #   @return [String]

    # @!method enable_event_waiting
    #   Enable waiting for events on EndDrawing(), no automatic event polling
    #   @return [void]

    # @!method disable_event_waiting
    #   Disable waiting for events on EndDrawing(), automatic events polling
    #   @return [void]

    # @!method exit_key=
    #   Set a custom key to exit program (default is ESC)
    #   @param key [Integer]
    #   @return [void]

    # Cursor-related functions

    # @!method show_cursor
    #   Shows cursor
    #   @return [void]

    # @!method hide_cursor
    #   Hides cursor
    #   @return [void]

    # @!method cursor_hidden?
    #   Check if cursor is not visible
    #   @return [void]

    # @!method enable_cursor
    #   Enables cursor (unlock cursor)
    #   @return [void]

    # @!method disable_cursor
    #   Disables cursor (lock cursor)
    #   @return [void]

    # @!method cursor_on_screen?
    #   Check if cursor is on the screen
    #   @return [void]

    # Timing-related functions

    # @!method target_fps=
    #   Set target FPS (maximum)
    #   @param fps [Integer]
    #   @return [void]

    # @!method frame_time
    #   Get time in seconds for last frame drawn (delta time)
    #   @return [Float]

    # @!method time
    #   Get elapsed time in seconds since InitWindow()
    #   @return [Float]

    # @!method fps
    #   Get current FPS
    #   @return [Float]

    # @!method show_fps
    #   Draw current FPS
    #   @param x [Integer]
    #   @param y [Integer]
    #   @return [void]
  end
end
