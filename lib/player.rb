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
    puts "start" if Input.pressed?(:start)
    puts "select" if Input.pressed?(:select)
    puts "home" if Input.pressed?(:home)

    puts "confirm" if Input.pressed?(:confirm)
    puts "cancel" if Input.pressed?(:cancel)
    puts "menu" if Input.pressed?(:menu)
    puts "special" if Input.pressed?(:special)

    puts "left_trigger" if Input.pressed?(:left_trigger)
    puts "right_trigger" if Input.pressed?(:right_trigger)
    puts "left_bumper" if Input.pressed?(:left_bumper)
    puts "right_bumper" if Input.pressed?(:right_bumper)

    puts "left_stick" if Input.pressed?(:left_stick)
    puts "right_stick" if Input.pressed?(:right_stick)

    puts "up" if Input.pressed?(:up)
    puts "down" if Input.pressed?(:down)
    puts "left" if Input.pressed?(:left)
    puts "right" if Input.pressed?(:right)
  end

  def draw
    @texture.draw(@position, WHITE)
    Draw.text("position: #{@position}", 220, 10, 20, GREEN)
  end

  def unload
    @texture.unload
  end

  private

  def update_position(delta)
    direction = Input.movement(:left, :right, :up, :down)
    velocity = direction * @speed
    displacement = velocity.scale(delta)
    @position += displacement
  end
end

Game.new.run
