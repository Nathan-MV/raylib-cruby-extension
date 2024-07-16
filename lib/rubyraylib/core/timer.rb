# frozen_string_literal: true

class Timer
  attr_accessor :interval
  attr_reader :elapsed

  def initialize(interval)
    @interval = interval
    @elapsed = 0
    @running = true
  end

  def update(delta)
    @elapsed += delta if @running
  end

  def reset
    @elapsed = 0
  end

  def pause
    @running = false
  end

  def paused?
    !@running
  end

  def resume
    @running = true
  end

  def elapsed?(time = 1)
    @elapsed >= @interval * time
  end

  def interval_passed?
    if @elapsed >= @interval
      reset
      true
    else
      false
    end
  end

  def toggle
    @running = !@running
  end

  def running?
    @running
  end
end
