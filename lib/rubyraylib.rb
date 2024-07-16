# frozen_string_literal: true

require_relative "rubyraylib/version"
require_relative "rubyraylib/rubyraylib"
require_relative "rubyraylib/settings"

require_relative "rubyraylib/core/spritesheet"
require_relative "rubyraylib/core/timer"
require_relative "rubyraylib/core/input"

require_relative "rubyraylib/player"
require_relative "rubyraylib/raymark"

require_relative "rubyraylib/main"

Game.new(Player).run
