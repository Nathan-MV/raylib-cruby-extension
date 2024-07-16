# frozen_string_literal: true

class Game
  def initialize(klass)
    Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, klass.to_s)
    Window.target_fps = 60
    @klass = klass.new
    @displaying_fps = false
  end

  def run
    until Window.should_close?
      @klass.update(Window.frame_time)
      @displaying_fps = !@displaying_fps if Input.pressed?(:f2)
      Draw.begin do
        Draw.clear(Color::WHITE)
        @klass.draw
        Window.show_fps(0, 0) if @displaying_fps
      end
    end
    @klass.unload
    Window.close
  end
end
