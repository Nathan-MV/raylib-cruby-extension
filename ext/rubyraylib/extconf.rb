# frozen_string_literal: true

require "mkmf"

# Makes all symbols private by default to avoid unintended conflict
# with other gems. To explicitly export symbols you can use RUBY_FUNC_EXPORTED
# selectively, or entirely remove this flag.
append_cflags("-fvisibility=hidden")
append_cflags("-Ofast")
append_cflags("-flto")
append_cflags("-DNDEBUG")
append_cflags("-fpic")
append_cflags("-ftree-vectorize")

# $INCFLAGS << " -I'd:/Cloud/Projects/Raylib/Ruby/raylib-cruby/third_party/raylib/src'"
# $LDFLAGS << " -L'd:/Cloud/Projects/Raylib/Ruby/raylib-cruby/third_party/raylib/src'"
have_library('raylib')

create_makefile("rubyraylib/rubyraylib")
