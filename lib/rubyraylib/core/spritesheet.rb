class SpriteSheet
  attr_reader :texture

  SCHEMAS = {
    character: {
      directions: %i[down left right up],
      actions: %i[walking1 still walking2]
    }
  }

  def initialize(texture, schema, size)
    @texture = Texture.new(texture)
    @schema = SCHEMAS[schema.to_sym]
    @sprite_size = size
    @num_columns = @schema[:actions].size
    @num_rows = @schema[:directions].size
    @direction_index = 0
    @action_index = 0
    @current_frame = 0
    update_frame_rectangle
  end

  def update(delta); end

  def draw(position)
    @texture.draw_rec(@frame_rect, position, Color::WHITE)
  end

  def unload
    @texture.unload
  end

  def direction=(direction)
    index = @schema[:directions].index(direction)
    raise "Invalid direction: #{direction}" unless index

    @direction_index = index
    update_frame
  end

  def action=(action)
    index = @schema[:actions].index(action)
    raise "Invalid action: #{action}" unless index

    @action_index = index
    update_frame
  end

  private

  def update_frame
    @current_frame = @direction_index * @num_columns + @action_index
    update_frame_rectangle
  end

  def update_frame_rectangle
    frame_x = (@current_frame % @num_columns) * @sprite_size.x
    frame_y = (@current_frame / @num_columns) * @sprite_size.y
    @frame_rect = Rect.new(frame_x, frame_y, @sprite_size.x, @sprite_size.y)
  end
end
