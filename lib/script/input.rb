# typed: true

require_relative "keyboard"
require_relative "gamepad"
require_relative "mouse"
require_relative "touch"
require "sorbet-runtime"

module Input
  class << self
    extend T::Sig

    # Check if a key has been pressed once
    # @param key [Symbol] the key symbol to check
    # @return [Boolean] true if the key has been pressed once, false otherwise
    sig { params(key: Symbol).returns(T::Boolean) }
    def pressed?(key)
      check_key_status(key, :pressed?, :button_pressed?, :button_pressed?)
    end

    # Check if a key has been pressed again (Only PLATFORM_DESKTOP with Keyboards)
    # @param key [Symbol] the key symbol to check
    # @return [Boolean] true if the key has been pressed again, false otherwise
    sig { params(key: Symbol).returns(T::Boolean) }
    def repeat?(key)
      keys = Keyboard::MAPPING[key]
      keys.any? { |k| Keyboard.repeat?(k) }
    end

    # Check if a key is being pressed
    # @param key [Symbol] the key symbol to check
    # @return [Boolean] true if the key is being pressed, false otherwise
    sig { params(key: Symbol).returns(T::Boolean) }
    def down?(key)
      check_key_status(key, :down?, :button_down?, :button_down?)
    end

    # Check if a key has been released once
    # @param key [Symbol] the key symbol to check
    # @return [Boolean] true if the key has been released once, false otherwise
    sig { params(key: Symbol).returns(T::Boolean) }
    def released?(key)
      check_key_status(key, :released?, :button_released?, :button_released?)
    end

    # Check if a key is NOT being pressed
    # @param key [Symbol] the key symbol to check
    # @return [Boolean] true if the key is not being pressed, false otherwise
    sig { params(key: Symbol).returns(T::Boolean) }
    def up?(key)
      check_key_status(key, :up?, :button_up?, :button_up?)
    end

    # Calculates the movement vector based on input and gamepad axis.
    # @param negative_x [Symbol] the key symbol for negative X direction (e.g., :left)
    # @param positive_x [Symbol] the key symbol for positive X direction (e.g., :right)
    # @param negative_y [Symbol] the key symbol for negative Y direction (e.g., :down)
    # @param positive_y [Symbol] the key symbol for positive Y direction (e.g., :up)
    # @return [Vec2] the resulting movement vector
    sig { params(negative_x: Symbol, positive_x: Symbol, negative_y: Symbol, positive_y: Symbol).returns(Vec2) }
    def movement(negative_x, positive_x, negative_y, positive_y)
      input = Vec2.new(key_value(negative_x, positive_x), key_value(negative_y, positive_y))
      input += gamepad_axis(0, :left) if Gamepad.available?(0)
      input
    end

    private

    # Checks the status of a key across different input methods (keyboard, mouse, gamepad).
    # @param key [Symbol] the key symbol to check
    # @param key_method [Symbol] the method to call on the Keyboard module
    # @param mouse_method [Symbol] the method to call on the Mouse module
    # @param gamepad_method [Symbol] the method to call on the Gamepad module
    # @return [Boolean] true if the key is active in any of the input methods
    sig { params(key: Symbol, key_method: Symbol, mouse_method: Symbol, gamepad_method: Symbol).returns(T::Boolean) }
    def check_key_status(key, key_method, mouse_method, gamepad_method)
      key_bindings = Keyboard::MAPPING[key] || []
      gamepad_bindings = Gamepad::MAPPING[key]
      mouse_binding = Mouse::MAPPING[key]
      key_match = key_bindings.any? { |binding| Keyboard.send(key_method, binding) }
      mouse_match = mouse_binding && Mouse.send(mouse_method, mouse_binding)
      gamepad_match = Gamepad.available?(0) && Gamepad.send(gamepad_method, 0, gamepad_bindings)

      key_match || mouse_match || gamepad_match
    end

    # Computes the key value based on the status of the given keys.
    # @param negative_key [Symbol] the key symbol for the negative direction
    # @param positive_key [Symbol] the key symbol for the positive direction
    # @return [Float] the resulting key value, where -1.0 indicates the negative key is pressed,
    #   1.0 indicates the positive key is pressed, and 0.0 indicates neither key is pressed
    sig { params(negative_key: Symbol, positive_key: Symbol).returns(Float) }
    def key_value(negative_key, positive_key)
      (down?(negative_key) ? -1.0 : 0.0) + (down?(positive_key) ? 1.0 : 0.0)
    end

    # Retrieves the gamepad axis movement vector for the specified axis type.
    # @param [Integer] gamepad_index index of the gamepad (e.g., 0 for the first gamepad)
    # @param [Symbol] axis_type type of axis (:left, :right, or :triggers)
    # @return [Vec2] movement vector for the specified axis
    sig { params(gamepad_index: Integer, axis_type: Symbol).returns(Vec2) }
    def gamepad_axis(gamepad_index, axis_type)
      axis = Gamepad::AXIS_MAPPING[axis_type] || raise(ArgumentError, "Unsupported axis type: #{axis_type}")

      Vec2.new(Gamepad.axis_movement(gamepad_index, axis[0]), Gamepad.axis_movement(gamepad_index, axis[1]))
    end
  end
end
