# frozen_string_literal: true

require "bundler/gem_tasks"
require "rubocop/rake_task"

RuboCop::RakeTask.new

require "rake/extensiontask"

# Task to compile Raylib
task :compile_raylib do
  platform = "PLATFORM_DESKTOP"
  sh "make PLATFORM=#{platform} -C third_party/raylib/src"
end

# Ensure the build task depends on compile_raylib
task build: :compile_raylib

GEMSPEC = Gem::Specification.load("rubyraylib.gemspec")

Rake::ExtensionTask.new("rubyraylib", GEMSPEC) do |ext|
  ext.lib_dir = "lib/rubyraylib"
end

task default: %i[clobber compile_raylib compile]
