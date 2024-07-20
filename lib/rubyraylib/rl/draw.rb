# frozen_string_literal: true

module RL
  module Draw
    # @!method clear
    #   Set background color (framebuffer clear color)
    #   @param color [Color]
    #   @return [void]

    # @!method begin
    #   Setup canvas (framebuffer) to start drawing
    #   This method must be used with a block. The drawing commands should be placed inside the block.
    #   The block ensures that drawing is correctly finalized with EndDrawing.
    #   @yield The drawing commands to be executed.
    #   @return [void]
  end
end
