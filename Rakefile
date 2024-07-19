# frozen_string_literal: true

require "bundler/gem_tasks"
require "rubocop/rake_task"
require "rake/extensiontask"
require "fileutils"

RuboCop::RakeTask.new

task :clean_raylib do
  FileUtils.rm_rf Dir.glob('third_party/raylib/src/*.o')
end

# Task to compile Raylib
# PLATFORM=PLATFORM_DESKTOP_SDL
# PLATFORM=PLATFORM_DESKTOP_RGFW
# USE_WAYLAND_DISPLAY=TRUE
task :compile_raylib do
  if RbConfig::CONFIG['host_os'] =~ /mswin|mingw|cygwin/
    sh "mingw32-make PLATFORM=PLATFORM_DESKTOP -C third_party/raylib/src"
  else
    sh "make PLATFORM=PLATFORM_DESKTOP -C third_party/raylib/src"
  end
end

# Compile Raygui task and create static library
task :compile_raygui do
  sh "cp third_party/raygui/src/raygui.h third_party/raygui/src/raygui.c"
  sh "gcc -c third_party/raygui/src/raygui.c -o third_party/raygui/src/raygui.o -fpic -DRAYGUI_IMPLEMENTATION -Lthird_party/raylib/src -lraylib -Ithird_party/raylib/src"
  sh "ar rcs third_party/raygui/src/libraygui.a third_party/raygui/src/raygui.o"
end

# Compile Reasings task and create static library
task :compile_reasings do
  sh "cp third_party/reasings/src/reasings.h third_party/reasings/src/reasings.c"
  sh "gcc -c third_party/reasings/src/reasings.c -o third_party/reasings/src/reasings.o -Lthird_party/raylib/src -lraylib -Ithird_party/raylib/src"
  sh "ar rcs third_party/reasings/src/libreasings.a third_party/reasings/src/reasings.o"
end

GEMSPEC = Gem::Specification.load("rubyraylib.gemspec")

Rake::ExtensionTask.new("rubyraylib", GEMSPEC) do |ext|
  ext.lib_dir = "lib/rubyraylib"
end

task default: %i[clobber clean_raylib compile_raylib compile_raygui compile_reasings compile]
