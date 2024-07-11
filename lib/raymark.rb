# frozen_string_literal: true

require_relative "rubyraylib/rubyraylib"
require_relative "script/input"

MAX_ELEMENTS = RubyVM::YJIT.enabled? ? 110_000 : 75_000
MOVE_ELEMENTS = false
SCREEN_WIDTH = 320 * 2
SCREEN_HEIGHT = 180 * 2
WHITE = Color.new(255, 255, 255)
BLACK = Color.new(0, 0, 0)
GREEN = Color.new(0, 228, 48)
RED = Color.new(255, 0, 0)

class Game
  def initialize
    Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, "Raymark")
    Window.target_fps = 60
    @raymark = Raymark.new(MAX_ELEMENTS, MOVE_ELEMENTS)
  end

  def run
    until Window.should_close?
      @raymark.update(Window.frame_time)
      Draw.begin do
        Draw.clear(WHITE)
        @raymark.draw
      end
    end
    @raymark.unload
    Window.close
  end
end

class Raymark
  MAX_BATCH_ELEMENTS = 8192

  def initialize(max, move)
    @max = max
    @move = move
    @texture = Texture.new("lib/raylib_32x32.png")
    @positions = Array.new(@max) { Vec2.new(random(0 - @texture.width, SCREEN_WIDTH), random(0, SCREEN_HEIGHT)) }
    # @src = Rect.new(0, 0, @texture.width.to_f, @texture.height.to_f)
    # @dest = Rect.new(0, 0, @texture.width.to_f, @texture.height.to_f)
    # @origin = Vec2.new(0, 0)
    @speeds = Array.new(@max) { Vec2.new(random(-250, 250) / 60, random(-250, 250) / 60) } if move
  end

  def update(delta)
    return unless @move

    @max.times do |i|
      @positions[i] + @speeds[i]
    end
  end

  def draw
    @max.times do |i|
      @texture.draw(@positions[i])
    end
    Draw.rect(0, 0, SCREEN_WIDTH, 40, BLACK)
    Draw.text(format("rects: %i", @max), 220, 10, 20, GREEN)
    Draw.text(format("batched draw calls: %i", 1 + @max / MAX_BATCH_ELEMENTS), 410, 10, 20, RED)

    Draw.fps(10, 10)
  end

  def unload
    @texture.unload
  end
end

Game.new.run
