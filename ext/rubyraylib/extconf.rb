# frozen_string_literal: true

require "mkmf"

# Define raylib directory
raylib_dir = File.expand_path(File.dirname(__FILE__) + "/../../third_party/raylib/src")

# Add include and library directories
$INCFLAGS << " -I" + raylib_dir
$LDFLAGS << " -L" + raylib_dir

# Append compiler flags
append_cflags("-fvisibility=hidden")
append_cflags("-Ofast")
append_cflags("-flto")
append_cflags("-DNDEBUG")
append_cflags("-fpic")
append_cflags("-ftree-vectorize")

# Link against the static library specifically
$LDFLAGS << " -l:libraylib.a"

# Debugging information
puts "Include flags: #{$INCFLAGS}"
puts "Library flags: #{$LDFLAGS}"

# Configure the include and library paths for raylib
dir_config('raylib', raylib_dir)

# Create the Makefile
create_makefile("rubyraylib/rubyraylib")
