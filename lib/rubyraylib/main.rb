# frozen_string_literal: true

class Game
  def initialize(klass)
    Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, klass.to_s)
    Window.target_fps = Window.refresh_rate(Window.current_monitor)
    @klass = klass.new
  end

  def run
    until Window.should_close?
      @klass.update(Window.frame_time)
      Draw.begin do
        Draw.clear(Color::WHITE)
        @klass.draw
        Window.show_fps(0, 0)
      end
    end
    @klass.unload
    Window.close
  end
end
