# frozen_string_literal: true

require 'benchmark'
require_relative "rubyraylib/version"
require_relative "rubyraylib/rubyraylib"

WHITE = Color.new(255, 255, 255)
SCREEN_WIDTH = 320 * 2
SCREEN_HEIGHT = 180 * 2

Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, 'Benchmark')

until Window.should_close?
  Draw.begin do
    Draw.clear(WHITE)
  end
end

Window.close