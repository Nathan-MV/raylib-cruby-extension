# frozen_string_literal: true

require_relative "rubyraylib/rubyraylib"
require_relative "script/input"

MOVE_ELEMENTS = true
# Multiplying by delta is CPU intensive, not really recommended for Benchmarks
FPS_INDEPENDENT = false
# The upper limit decreased after i updated Raylib from 5.0 to 5.5...
MAX_ELEMENTS = if MOVE_ELEMENTS
                 if FPS_INDEPENDENT
                   RubyVM::YJIT.enabled? ? 35_000 : 20_000
                 else
                   (RubyVM::YJIT.enabled? ? 90_000 : 50_000)
                 end
               else
                 RubyVM::YJIT.enabled? ? 90_000 : 75_000
               end
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
    @positions = Array.new(max) { Vec2.new(random(0 - @texture.width, SCREEN_WIDTH), random(0, SCREEN_HEIGHT)) }
    return unless move

    @speed = 400
    @speeds = Array.new(@max) { Vec2.new(random(-250, 250) / 60, random(-250, 250) / 60) } unless FPS_INDEPENDENT
    @bounds = Vec2.new(SCREEN_WIDTH - @texture.width, SCREEN_HEIGHT - @texture.height)
  end

  def update(delta)
    return unless @move

    @max.times do |i|
      if FPS_INDEPENDENT
        direction = Vec2.new(random(-1.0, 1.0), random(-1.0, 1.0))
        velocity = direction * @speed * delta
        @positions[i] = (@positions[i] + velocity).clamp(@bounds)
      else
        @positions[i] = (@positions[i] + @speeds[i]).clamp(@bounds)
      end
    end
  end

  def draw
    @max.times { |i| @texture.draw(@positions[i]) }
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
