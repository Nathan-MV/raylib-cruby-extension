# frozen_string_literal: true

require "bundler/gem_tasks"
require "rubocop/rake_task"

RuboCop::RakeTask.new

require "rake/extensiontask"

task :clean_raylib do
  sh "make clean -C third_party/raylib/src"
end

# Task to compile Raylib
task :compile_raylib do
  sh "make -C third_party/raylib/src"
end

GEMSPEC = Gem::Specification.load("rubyraylib.gemspec")

Rake::ExtensionTask.new("rubyraylib", GEMSPEC) do |ext|
  ext.lib_dir = "lib/rubyraylib"
end

task default: %i[clobber clean_raylib compile_raylib compile]
