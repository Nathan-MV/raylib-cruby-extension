# frozen_string_literal: true

class Raymark
  # The upper limit decreased after i updated Raylib from 5.0 to 5.5...
  MAX_ELEMENTS = 90_000
  MAX_BATCH_ELEMENTS = 8192
  MOVE_ELEMENTS = false

  def initialize
    @texture = Texture.new("lib/rubyraylib/raylib_32x32.png")
    @positions = generate_random_positions
    @direction = Vec2.new(-2, 2)
    @speed = 400
    @rect = Rect.new(0, 0, SCREEN_WIDTH, 20)
  end

  def generate_random_positions
    Array.new(MAX_ELEMENTS) do
      Vec2.new(random(0, SCREEN_WIDTH), random(0, SCREEN_HEIGHT))
    end
  end

  def update(_delta)
    return unless MOVE_ELEMENTS

    MAX_ELEMENTS.times { |i| @positions[i].random_movement(@direction, @speed) }
  end

  def draw
    MAX_ELEMENTS.times { |i| @texture.draw(@positions[i]) }
    @rect.draw(Color::BLACK)
    Text.draw(format("Textures: %i", MAX_ELEMENTS), 220, 0, 20, Color::GREEN)
    Text.draw(format("Batched Draw Calls: %i", 1 + MAX_ELEMENTS / MAX_BATCH_ELEMENTS), 410, 0, 20, Color::RED)
  end

  def unload
    @texture.unload
  end
end
