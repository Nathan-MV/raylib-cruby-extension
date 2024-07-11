# frozen_string_literal: true

require_relative "rubyraylib/rubyraylib"
require_relative "script/input"

SCREEN_WIDTH = 320 * 2
SCREEN_HEIGHT = 180 * 2
WHITE = Color.new(255, 255, 255)
GREEN = Color.new(0, 228, 48)

class Game
  def initialize
    Window.init(SCREEN_WIDTH, SCREEN_HEIGHT, "Player")
    Window.target_fps = 60
    @player = Player.new
  end

  def run
    until Window.should_close?
      @player.update(Window.frame_time)
      Draw.begin do
        Draw.clear(WHITE)
        @player.draw
      end
    end
    @player.unload
    Window.close
  end
end

class Player
  def initialize
    @texture = Texture.new("lib/raylib_32x32.png")
    @position = Vec2.new(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2)
    @speed = 400
  end

  def update(delta)
    update_position(delta)
    Input.debug_mappings
  end

  def draw
    @texture.draw(@position)
    Draw.text("position: #{@position}", 220, 10, 20, GREEN)
  end

  def unload
    @texture.unload
  end

  private

  def update_position(delta)
    direction = Input.movement(:left, :right, :up, :down)
    @position += direction * @speed * delta
  end
end

Game.new.run
