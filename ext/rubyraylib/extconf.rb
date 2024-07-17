# frozen_string_literal: true

require "mkmf"

# Define directories for raylib, raygui, and reasings
raylib_dir = File.expand_path(File.dirname(__FILE__) + "/../../third_party/raylib/src")
raygui_dir = File.expand_path(File.dirname(__FILE__) + "/../../third_party/raygui/src")
reasings_dir = File.expand_path(File.dirname(__FILE__) + "/../../third_party/reasings/src")

# Add include and library directories
$INCFLAGS << " -I#{raylib_dir} -I#{raygui_dir} -I#{reasings_dir}"
$LDFLAGS << " -L#{raylib_dir} -L#{raygui_dir} -L#{reasings_dir}"

# Link against the static libraries
if /linux/i =~ RUBY_PLATFORM
  $LDFLAGS << " -lraylib -lraygui -lreasings -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr"
elsif /darwin/i =~ RUBY_PLATFORM
  $LDFLAGS << " -lraylib -lraygui -lreasings -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"
else
  $LDFLAGS << " -lraylib -lraygui -lreasings -lgdi32 -lwinmm"
end

# Debugging information
puts "Include flags: #{$INCFLAGS}"
puts "Library flags: #{$LDFLAGS}"

# Append compiler flags
append_cppflags("-fvisibility=hidden")
append_cppflags("-Ofast")
append_cppflags("-flto")
append_cppflags("-DNDEBUG")
append_cppflags("-fpic")
append_cppflags("-ftree-vectorize")
# append_cppflags("-Wall")
# append_cppflags("-Wextra")
# append_cppflags("-pedantic")

$CXXFLAGS << " -std=c++20"

# Create the Makefile
create_makefile("rubyraylib/rubyraylib")
