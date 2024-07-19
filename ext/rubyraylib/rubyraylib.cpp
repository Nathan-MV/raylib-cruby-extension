#include "rubyraylib.hpp"

RUBY_FUNC_EXPORTED void Init_rubyraylib(void) {
  initializeRaylib();
  initializeKernel();

  // Modules
  initializeWindow();
  initializeKeyboard();
  initializeMouse();
  initializeGamepad();
  initializeTouch();
  initializeGestures();
  initializeDraw();
  initializeShapes();
  initializeText();

  // Classes
  initializeColor();
  initializeRect();
  initializeVec2();
  initializeVec3();
  initializeVec4();
  initializeTexture();
  initializeImage();

  // External
  initializeGui();
  initializeEase();

  // Custom
  initializeTextureAtlas();
}

static void initializeRubyInterpreter() {
  int argc = 0;
  char **argv = nullptr;

  ruby_sysinit(&argc, &argv);
  RUBY_INIT_STACK;
  ruby_init();
  rb_enc_set_default_internal(rb_enc_from_encoding(rb_utf8_encoding()));
  rb_enc_set_default_external(rb_enc_from_encoding(rb_utf8_encoding()));
}

static void initializeRubyArguments() {
  const char *args[] = {"ruby", "-e", "--yjit", "--parser=prism"};
  int argc = sizeof(args) / sizeof(args[0]);
  ruby_options(argc, const_cast<char **>(args));
}

static std::string determineScriptPath(int argc, char **argv) {
  std::string scriptPath;

  if (argc > 1) {
    scriptPath = argv[1];
    if (scriptPath.back() != '/')
      scriptPath += '/';
    scriptPath += "main.rb";
    if (!FileExists(scriptPath.c_str()))
      scriptPath.clear();
  }

  if (scriptPath.empty() && FileExists("./main.rb"))
    scriptPath = "./main.rb";

  return scriptPath;
}

static VALUE rubyScriptLoad(VALUE scriptPath) {
  rb_load(scriptPath, 0);
  return Qnil;
}

// Function to handle Ruby exceptions
static VALUE handleRubyException(VALUE, VALUE exc) {
  // Initialize a string stream to build the error message
  std::ostringstream result;
  const std::string separator(100, '-');

  // Retrieve the Ruby exception details
  VALUE message = rb_funcall(exc, rb_intern("message"), 0);
  VALUE exception_name = rb_class_path(rb_obj_class(exc));
  VALUE backtrace = rb_funcall(exc, rb_intern("backtrace"), 0);

  // Extract file path and line number from the first backtrace entry
  VALUE first_line = rb_ary_entry(backtrace, 0);
  VALUE parts = rb_str_split(first_line, ":");
  VALUE file_path = rb_ary_entry(parts, 0);
  VALUE line = rb_ary_entry(parts, 1);
  const char *file_path_str = StringValueCStr(file_path);
  int line_number = atoi(StringValueCStr(line));

  // Build the error message
  result << separator << "\n"
         << "File: " << file_path_str << " in line " << line_number + 1 << "\n"
         << "Class: " << RSTRING_PTR(exception_name) << "\n"
         << "Message: " << RSTRING_PTR(message) << "\n"
         << separator << "\n"
         << "Backtrace:\n";

  // Append the backtrace
  long backtrace_length = RARRAY_LEN(backtrace);
  for (long i = 1; i < backtrace_length; ++i) {
    result << "\tfrom " << RSTRING_PTR(rb_ary_entry(backtrace, i)) << "\n";
  }

  result << separator;

  // Output the error message to standard error
  std::cerr << result.str() << std::endl;

  // Clear the Ruby error information
  std::ostringstream().swap(result);
  rb_set_errinfo(Qnil);

  return Qnil;
}

int main(int argc, char **argv) {
  initializeRubyInterpreter();
  initializeRubyArguments();
  Init_rubyraylib();

  std::string scriptPath = determineScriptPath(argc, argv);
  if (scriptPath.empty()) {
    std::cerr << "Error: No valid script found." << std::endl;
    ruby_cleanup(0);
    return 1;
  }

  VALUE scriptPathValue = rb_str_new_cstr(scriptPath.c_str());
  VALUE result =
      rb_rescue(rubyScriptLoad, scriptPathValue, handleRubyException, Qnil);

  ruby_cleanup(0);
  return 0;
}
