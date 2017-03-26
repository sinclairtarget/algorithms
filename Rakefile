require 'rake/clean'

C_SOURCE_DIRECTORY = 'c'.freeze
CPP_SOURCE_DIRECTORY = 'cpp'.freeze

C_EXECUTABLE_NAME = 'run_c'.freeze
CPP_EXECUTABLE_NAME = 'run_cpp'.freeze

C_SOURCE_FILES = FileList["#{C_SOURCE_DIRECTORY}/**/*.c"] 
CPP_SOURCE_FILES = FileList["#{CPP_SOURCE_DIRECTORY}/**/*.c", 
                            "#{CPP_SOURCE_DIRECTORY}/**/*.cpp"]

$compile_flags = '-c'

task :default => ['build:c']

namespace :build do
  desc 'Builds the test run executable using the c implementations.'
  task :c => [C_EXECUTABLE_NAME]

  namespace :debug do
    desc 'Builds the test run executable using the c implementations ' +
         'with debug info.'
    task :c => [:set_debug_compile_flags, C_EXECUTABLE_NAME]

    # TODO: Is there a better way to accomplish this?
    task :set_debug_compile_flags do
      $compile_flags = '-c -g'
    end
  end
end

file C_EXECUTABLE_NAME => C_SOURCE_FILES.ext('.o') do |t|
  sh "clang -o #{t.name} #{t.prerequisites.join(' ')}"
end
CLEAN.include(C_SOURCE_FILES.ext('.o'))

# Uses clang to determine the dependencies of a source file.
# Returns an array of file names.
def file_deps(task_name, file_ext)
  source_file_name = task_name.ext(file_ext)
  return [] unless File.exist?(source_file_name)

  out = `clang -E -MM #{source_file_name}`
  raise "Dependency generation failed!" unless $?.success?

  # Clang dependency file format example:
  # triangle.o: triangle.c triangle.h \
  #   math_utils.h
  out.split(':').last.split
     .reject { |e| e == '\\' || e == source_file_name }
end

rule '.o' => ['.c', *(-> (task_name) { file_deps(task_name, '.c') })] do |t|
  sh "clang #{$compile_flags} #{t.source} -o #{t.name}"
end

CLOBBER.include(C_EXECUTABLE_NAME)
