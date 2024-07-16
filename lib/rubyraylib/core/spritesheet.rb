class SpriteSheet
  attr_reader :texture, :schema, :size, :frame, :direction_index, :action_index

  SCHEMAS = {
    character: {
      directions: %i[down left right up],
      actions: %i[walking1 still walking2],
      interval: 0.5
    }
  }

  def initialize(texture, schema)
    @texture = Texture.new(texture)
    @schema = SCHEMAS[schema.to_sym]
    @num_rows = @schema[:directions].size
    @num_columns = @schema[:actions].size
    @size = Vec2.new(@texture.width / @num_columns, @texture.height / @num_rows)
    @frame = Timer.new(@schema[:interval])
    @direction_index = @action_index = @current_frame = 0
    update_frame_rectangle
  end

  def update(delta)
    return unless @frame.running?

    @frame.update(delta)
    return unless @frame.ready?

    @action_index = (@action_index + 1) % @num_columns
    update_frame
  end

  def draw(position)
    @texture.draw_rec(@frame_rect, position, Color::WHITE)
  end

  def unload
    @texture.unload
  end

  def direction=(direction)
    set_index(:direction, direction)
  end

  def action=(action)
    set_index(:action, action)
  end

  private

  def set_index(type, value)
    index = @schema[:"#{type}s"].index(value)
    raise ArgumentError, "Invalid #{type}: #{value}" unless index

    instance_variable_set("@#{type}_index", index)
    update_frame
  end

  def update_frame
    @current_frame = @direction_index * @num_columns + @action_index
    update_frame_rectangle
  end

  def update_frame_rectangle
    frame_x = (@current_frame % @num_columns) * @size.x
    frame_y = (@current_frame / @num_columns) * @size.y
    @frame_rect = Rect.new(frame_x, frame_y, @size.x, @size.y)
  end
end
