# frozen_string_literal: true

require_relative "rubyraylib/version"
require_relative "rubyraylib/settings"
require_relative "rubyraylib/rubyraylib"
require_relative "rubyraylib/rl/input"
require_relative "rubyraylib/rl/input/gamepad"
require_relative "rubyraylib/rl/input/gestures"
require_relative "rubyraylib/rl/input/keyboard"
require_relative "rubyraylib/rl/input/mouse"
require_relative "rubyraylib/rl/input/touch"
require_relative "rubyraylib/raymark"

include RL

class Game
  def initialize(klass)
    Graphics.init(SCREEN_WIDTH, SCREEN_HEIGHT, klass.to_s)
    Graphics.target_fps = Graphics.refresh_rate(Graphics.current_monitor)
    @klass = klass.new
  end

  def run
    until Graphics.should_close?
      @klass.update(Graphics.frame_time)
      Graphics.begin do
        Graphics.clear(Color.new(255, 255, 255))
        @klass.draw
        Graphics.draw_fps(0, 0)
      end
    end
    @klass.unload
    Graphics.close
  end
end

Game.new(Raymark).run
