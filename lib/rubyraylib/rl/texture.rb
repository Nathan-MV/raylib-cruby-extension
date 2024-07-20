# frozen_string_literal: true

module RL
  class Texture
    # @!attribute width [rw]
    #   @param width [Texture]
    #   @return [Integer]

    # @!attribute height [rw]
    #   @param height [Texture]
    #   @return [Integer]

    # @!attribute mipmaps [rw]
    #   @param mipmaps [Texture]
    #   @return [Integer]

    # @!attribute format [rw]
    #   @param format [Texture]
    #   @return [Integer]

    # @!method initialize
    #   Initializes a new Texture object.
    #   @param file_name [String] Load texture from file into GPU memory (VRAM)
    #   @return [Texture]

    # @!method unload
    #   Unload texture from GPU memory (VRAM)
    #   @return [void]

    # @!method scale=
    #   Scales the texture by an integer amount
    #   @return [Texture]
  end
end
