module Touch
  # // Input-related functions: touch
  # @!method touch_x
  #   Get touch position X for touch point 0 (relative to screen size)
  #   @return [int]
  # @!method touch_y
  #   Get touch position Y for touch point 0 (relative to screen size)
  #   @return [int]
  # @!method touch_position
  #   Get touch position XY for a touch point index (relative to screen size)
  #   @param index [Integer]
  #   @return [Vec2]
  # @!method touch_point_id
  #   Get touch point identifier for given index
  #   @param index [Integer]
  #   @return [int]
  # @!method touch_point_count
  #   Get number of touch points
  #   @return [int]
end
