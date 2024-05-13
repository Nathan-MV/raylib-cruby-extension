# frozen_string_literal: true

require "bundler/gem_tasks"
require "rubocop/rake_task"

RuboCop::RakeTask.new

require "rake/extensiontask"

task build: :compile

GEMSPEC = Gem::Specification.load("rubyraylib.gemspec")

Rake::ExtensionTask.new("rubyraylib", GEMSPEC) do |ext|
  ext.lib_dir = "lib/rubyraylib"
end

task default: %i[clobber compile rubocop]
