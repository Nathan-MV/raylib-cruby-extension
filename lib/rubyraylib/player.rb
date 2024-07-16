# frozen_string_literal: true

class Player
  def initialize
    @sprite = SpriteSheet.new("lib/rubyraylib/Actor1.png", :character)
    @position = Vec2.new(0, 0)
    @bounds = Vec2.new(SCREEN_WIDTH - @sprite.size.x, SCREEN_HEIGHT - @sprite.size.y)
    @speed = 200
  end

  def update(delta)
    update_position(delta)
    @sprite.update(delta) unless @direction.zero?
    @sprite.direction = Input.last_direction if Input.last_direction
    @sprite.action = :still if @direction.zero?
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
    boost = Input.down?(:special) ? 2 : 1
    @position += @direction * @speed * delta * boost
    @position.clamp(@bounds)
  end
end
