# frozen_string_literal: true

require "mkmf"

# Define directories for raylib, raygui, and reasings
raylib_dir = File.expand_path("#{File.dirname(__FILE__)}/../../third_party/raylib/src")
raygui_dir = File.expand_path("#{File.dirname(__FILE__)}/../../third_party/raygui/src")
reasings_dir = File.expand_path("#{File.dirname(__FILE__)}/../../third_party/reasings/src")

# Add include and library directories
$INCFLAGS << " -I#{raylib_dir} -I#{raygui_dir} -I#{reasings_dir}"
$LDFLAGS << " -L#{raylib_dir} -L#{raygui_dir} -L#{reasings_dir}"

# Specify the static libraries to link against
raylib_lib = File.expand_path("#{raylib_dir}/libraylib.a")
raygui_lib = File.expand_path("#{raygui_dir}/libraygui.a")
reasings_lib = File.expand_path("#{reasings_dir}/libreasings.a")

$LDFLAGS << " #{raylib_lib} #{raygui_lib} #{reasings_lib}"

$LDFLAGS << if /linux/i =~ RUBY_PLATFORM
              " -lGL -lm -lpthread -ldl -lrt -lX11 -lXrandr"
            elsif /darwin/i =~ RUBY_PLATFORM
              " -framework CoreVideo -framework IOKit -framework Cocoa -framework GLUT -framework OpenGL"
            else
              " -lgdi32 -lwinmm"
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
