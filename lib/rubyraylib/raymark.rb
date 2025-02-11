# frozen_string_literal: true

class Raymark
  MAX_ELEMENTS = 90_000
  MAX_BATCH_ELEMENTS = 8192
  MOVE_ELEMENTS = false

  def initialize
    @sprite = Sprite.new('assets/raylib_32x32.png')
    @grid = create_texture_grid
    @total_grid_elements = @grid.size
    @speed = 400
    @rect = Rect.new(0, 0, Graphics.screen_width, 20)
    @font = Font.new('assets/KAISG.ttf')
    @black = Color.new(0, 0, 0)
    @white = Color.new(255, 255, 255)
  end

  def update(delta)
    unload if Input.released?(:up)
    return unless MOVE_ELEMENTS

    MAX_ELEMENTS.times { |i| @grid[i % @total_grid_elements].rand_move(@speed) }
  end

  def draw
    # draw functions already apply batching if it's drawing the same texture
    MAX_ELEMENTS.times { |i| @sprite.draw(@grid[i % @total_grid_elements]) }
    @rect.draw(@black)
    @font.draw("Textures: #{MAX_ELEMENTS}", 220, 0, 20, @white)
    @font.draw("Batched Draw Calls: #{1 + (MAX_ELEMENTS / MAX_BATCH_ELEMENTS)}", 410, 0, 20, @white)
  end

  def unload
    @sprite.unload
  end

  private

  def create_texture_grid
    cols = Graphics.screen_width / 32
    rows = Graphics.screen_height / 32
    Array.new(rows * cols) do |i|
      x = (i % cols) * 32
      y = (i / cols) * 32
      Vec2.new(x, y)
    end
  end
end
