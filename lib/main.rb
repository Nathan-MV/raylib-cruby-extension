# frozen_string_literal: true
require_relative "rubyraylib/rubyraylib"

# MAX_ELEMENTS = RubyVM::YJIT.enabled? ? 110_000 : 75_000
MAX_ELEMENTS = 75_000
MOVE_ELEMENTS = false
MAX_BATCH_ELEMENTS = 8192
WHITE = Color.new(255, 255, 255)
BLACK = Color.new(0, 0, 0)
GREEN = Color.new(0, 228, 48)
RED = Color.new(190, 33, 55)
SCREEN_WIDTH = 320 * 2
SCREEN_HEIGHT = 180 * 2

class Benchmark
  def initialize(max, move)
    @max = max
    @move = move
    @texture = Texture.new('lib/raylib_32x32.png')
    @size = Vec2.new(32, 32)
    @positions = Array.new(@max) { Vec2.new(random(0 - @size.x, SCREEN_WIDTH), random(0, SCREEN_HEIGHT)) }
    @speeds = Array.new(@max) { Vec2.new(random(-5, 5), random(-5, 5)) } if move
  end

  def update
    return unless @move

    @max.times do |i|
      @positions[i].add(@speeds[i])
      @speeds[i].reverse if @positions[i].outside_bounds?(@size)
    end
  end

  def draw
    @max.times do |i|
      @texture.draw(@positions[i], WHITE)
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

# puts 'RUBY: YJIT Disabled' if !RubyVM::YJIT.enabled?
# puts 'RUBY: YJIT Enabled' if RubyVM::YJIT.enabled?
Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, 'Benchmark')
bench = Benchmark.new(MAX_ELEMENTS, MOVE_ELEMENTS)
Window.icon = 'lib/raylib_32x32.png'

until Window.should_close?
  bench.update
  Draw.begin do
    Draw.clear(WHITE)
    bench.draw
  end
end

bench.unload
Window.close
