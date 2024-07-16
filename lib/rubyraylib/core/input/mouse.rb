# frozen_string_literal: true

module Input
  module Mouse
    MAPPING = {
      confirm: Mouse::BUTTON_LEFT,
      cancel: Mouse::BUTTON_RIGHT
    }

    # // Input-related functions: mouse
    # @!method x
    #   Get mouse position X
    #   @return [int]
    # @!method y
    #   Get mouse position Y
    #   @return [int]
    # @!method position
    #   Get mouse position XY
    #   @return [Vec2]
    # @!method delta
    #   Get mouse delta between frames
    #   @return [Vec2]
    # @!method position=
    #   Set mouse position XY
    #   @param x [Integer]
    #   @param y [Integer]
    #   @return [void]
    # @!method offset=
    #   Set mouse offset
    #   @param offsetX [Integer]
    #   @param offsetY [Integer]
    #   @return [void]
    # @!method scale=
    #   Set mouse scaling
    #   @param offsetX [Float]
    #   @param offsetY [Float]
    #   @return [void]
    # @!method wheel_move
    #   Get mouse wheel movement for X or Y, whichever is larger
    #   @return [Float]
    # @!method wheel_move_v
    #   Get mouse wheel movement for both X and Y
    #   @return [Vec2]
    # @!method cursor=
    #   Set mouse cursor
    #   @param cursor [Integer]
    #   @return [void]
  end
end
