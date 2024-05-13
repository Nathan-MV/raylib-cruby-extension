# frozen_string_literal: true
require_relative "rubyraylib/rubyraylib"

MAX_BATCH_ELEMENTS = 8192
WHITE = Color.new(255, 255, 255)
BLACK = Color.new(0, 0, 0)
GREEN = Color.new(0, 228, 48, 255)
RED = Color.new(190, 33, 55, 255)
SCREEN_WIDTH = 320 * 2
SCREEN_HEIGHT = 180 * 2

class Benchmark
  COLORS = [WHITE, BLACK, GREEN, RED].freeze

  def initialize(max, move)
    @max = max
    @move = move
    @size = Vec2.new(32, 32)
    @positions = Array.new(@max) { Vec2.new(random(0 - @size.x, SCREEN_WIDTH), random(0, SCREEN_HEIGHT)) }
    @speeds = Array.new(@max) { Vec2.new(random(-5, 5), random(-5, 5)) } if move
    @colors = Array.new(@max) { COLORS.sample }
  end

  def update
    return unless @move

    @max.times do |i|
      @positions[i].add!(@speeds[i])
      @speeds[i].reverse! if @positions[i].outside_bounds?(@size)
    end
  end

  def draw
    @max.times do |i|
      Draw.rect(@positions[i], @size, @colors[i])
    end

    Draw.rect(0, 0, SCREEN_WIDTH, 40, BLACK)
    Draw.text(format("rects: %i", @max), 220, 10, 20, GREEN)
    Draw.text(format("batched draw calls: %i", 1 + @max / MAX_BATCH_ELEMENTS), 410, 10, 20, RED)

    Draw.fps(10, 10)
  end
end

puts 'RUBY: YJIT Disabled' if !RubyVM::YJIT.enabled?
puts 'RUBY: YJIT Enabled' if RubyVM::YJIT.enabled?
Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, 'Benchmark')
bench = Benchmark.new(110_000, false)

until Window.should_close?
  bench.update
  Draw.begin do
    Draw.clear(WHITE)
    bench.draw
  end
end

Window.close
