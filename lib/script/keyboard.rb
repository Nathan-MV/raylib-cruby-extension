module Keyboard
  # Mapping of symbolic key names to their corresponding key codes for keyboard inputs.
  # @note The key codes for keyboard inputs (e.g., `J`, `INSERT`) are constants defined by Raylib.
  # @example Replace the mapping for the start button
  #   Keyboard::MAPPING[:start] = [Keyboard::J, Keyboard::INSERT]
  MAPPING = {
    # Start and select buttons
    start: [J, INSERT],
    select: [H, PAUSE],
    home: [SEMICOLON, HOME],

    # Action buttons
    confirm: [C, SPACE, ENTER],
    cancel: [X, BACKSPACE, ESCAPE],
    menu: [V, MENU, KP_3],
    special: [B, KP_1, RIGHT_SHIFT],

    # Triggers and bumpers
    left_trigger: [F, ONE, KP_7],
    right_trigger: [G, THREE, KP_9],
    left_bumper: [R],
    right_bumper: [T],

    # Joystick buttons
    left_stick: [FOUR, Y],
    right_stick: [FIVE, U],

    # Directional buttons
    up: [UP, W, KP_8],
    down: [DOWN, S, KP_2],
    left: [LEFT, A, KP_4],
    right: [RIGHT, D, KP_6]
  }

  # // Input-related functions: keyboard
  # @!method pressed
  #   Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
  #   @return [Integer]
  # @!method char_pressed
  #   Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
  #   @return [Integer]
  # @!method exit_key=
  #   Set a custom key to exit program (default is ESC)
  #   @param key [Integer]
  #   @return [void]
end
