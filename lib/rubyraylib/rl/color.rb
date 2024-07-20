# frozen_string_literal: true

module RL
  class Color
    # @!attribute red [rw]
    #   @param red [Color]
    #   @return [Float]

    # @!attribute green [rw]
    #   @param green [Color]
    #   @return [Float]

    # @!attribute blue [rw]
    #   @param blue [Color]
    #   @return [Float]

    # @!attribute alpha [rw]
    #   @param alpha [Color]
    #   @return [Float]

    # @!method initialize
    #   Initializes a new Color object.
    #   You can initialize the color using either a hex value or individual RGBA components.
    #   @overload initialize(hex)
    #   @param hex [Integer] The hex value representing the color.
    #   @overload initialize(r, g, b, a = 255)
    #   @param r [Float] The red component (0-255).
    #   @param g [Float] The green component (0-255).
    #   @param b [Float] The blue component (0-255).
    #   @param a [Float] The alpha component (0-255), defaults to 255 if not provided.
    #   @return [Color]

    # @!method fade
    #   Get color with alpha applied, alpha goes from 0.0f to 1.0f
    #   @param alpha [Float]
    #   @return [Color]

    # @!method to_int
    #   Get hexadecimal value for a Color (0xRRGGBBAA)
    #   @return [Integer]

    # @!method normalize
    #   Get Color from normalized values [0..1]
    #   @return [Color]

    # @!method to_hsv
    #   Get HSV values for a Color, hue [0..360], saturation/value [0..1]
    #   @return [Vector3]

    # @!method tint
    #   Get color multiplied with another color
    #   @param tint [Color]
    #   @return [Color]

    # @!method brightness
    #   Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
    #   @param factor [Float]
    #   @return [Color]

    # @!method contrast
    #   Get color with contrast correction, contrast values between -1.0f and 1.0f
    #   @param contrast [Float]
    #   @return [Color]

    # @!method alpha_blend
    #   Get src alpha-blended into dst color with tint
    #   @param src [Color]
    #   @param tint [Color]
    #   @return [Color]
  end
end
