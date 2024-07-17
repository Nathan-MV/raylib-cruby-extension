# frozen_string_literal: true

require_relative "rubyraylib/version"
require_relative "rubyraylib/rubyraylib"
require_relative "rubyraylib/settings"

require_relative "rubyraylib/raymark"

require_relative "rubyraylib/main"

Game.new(Raymark).run
