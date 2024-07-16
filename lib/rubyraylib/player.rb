# frozen_string_literal: true

class Player
  def initialize
    @sprite = SpriteSheet.new("lib/rubyraylib/Actor1.png", :character, Vec2.new(48, 48))
    @position = Vec2.new(0, 0)
    @bounds = Vec2.new(SCREEN_WIDTH - 48, SCREEN_HEIGHT - 48)
    @speed = 200
    @last_direction = :down
    @last_action = :still
    @timer = Timer.new(0.4)
  end

  def update(delta)
    update_position(delta)
    update_frame(delta)
    @sprite.direction = @last_direction
    @sprite.action = @last_action
  end

  def draw
    @sprite.draw(@position)
    Draw.text("position: #{@position}", SCREEN_WIDTH / 2, 0, 20, Color::GREEN)
  end

  def unload
    @sprite.unload
  end

  private

  def update_position(delta)
    @direction = Input.movement(:left, :right, :up, :down)
    @last_direction = Input.last_direction if Input.last_direction
    boost = Input.down?(:special) ? 2 : 1
    velocity = @direction * @speed * delta * boost

    @position += velocity
    @position.clamp(@bounds)
  end

  def update_frame(delta)
    if @direction.zero?
      @last_action = :still
      @timer.reset
    else
      @timer.update(delta)
      @last_action = @timer.elapsed < @timer.interval ? :walking1 : :walking2
      @timer.reset if @timer.elapsed?(2)
    end
  end
end
