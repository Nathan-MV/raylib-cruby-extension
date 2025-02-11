#include "rubyraylib.hpp"

RUBY_FUNC_EXPORTED void Init_rubyraylib(void) {
  Init_Raylib();
  Init_Kernel();

  // Modules
  Init_Graphics();
  Init_Keyboard();
  Init_Mouse();
  Init_Gamepad();
  Init_Touch();
  Init_Gestures();
  Init_Draw();
  Init_Shapes();
  Init_Audio();

  // Classes
  Init_Color();
  Init_Rect();
  Init_Vec2();
  Init_Vec3();
  Init_Vec4();
  Init_Table();
  Init_Shader();
  Init_Sprite();
  Init_RenderTexture();
  Init_Bitmap();
  Init_Font();
  Init_Camera();

  // External
  Init_Gui();
  Init_Ease();
}

// static auto initializeRubyInterpreter() {
//   int argc = 0;
//   char *argv = nullptr;
//   char **pArgv = &argv;

//   ruby_sysinit(&argc, &pArgv);
//   RUBY_INIT_STACK;
//   ruby_init();
// }

static auto initializeRubyArguments() {
  const char *args[] = {"ruby", "-e", "--yjit"};  //, "--parser=prism"};
  auto argc = sizeof(args) / sizeof(args[0]);
  ruby_options(argc, const_cast<char **>(args));
}

static auto rubyScriptLoad(VALUE scriptPath) {
  rb_ary_push(rb_gv_get("$LOAD_PATH"), scriptPath);
  rb_load(scriptPath, 0);
  return Qnil;
}

static VALUE handleRubyException(VALUE, VALUE exc) {
  // Separator for clarity in the error message
  const std::string separator(100, '-');

  // Retrieve exception details with safety checks
  VALUE message = rb_funcall(exc, rb_intern("message"), 0);
  VALUE exception_name = rb_class_path(rb_obj_class(exc));
  VALUE backtrace = rb_funcall(exc, rb_intern("backtrace"), 0);

  // Verify that message, exception_name, and backtrace are non-nil
  if (NIL_P(message) || NIL_P(exception_name) || NIL_P(backtrace)) {
    std::cerr << "Error: Unable to retrieve exception details (one or more values are nil)."
              << std::endl;
    return Qnil;
  }

  // Attempt to convert Ruby values to C strings, handle failures gracefully
  const char *message_str = nullptr, *exception_name_str = nullptr;
  try {
    message_str = StringValueCStr(message);
    exception_name_str = StringValueCStr(exception_name);
  } catch (...) {
    std::cerr << "Error: Failed to convert exception message or class name to string." << std::endl;
    return Qnil;
  }

  VALUE first_line = rb_ary_entry(backtrace, 0);
  const char *file_str = NIL_P(first_line) ? "Unknown" : StringValueCStr(first_line);

  std::ostringstream result;
  result << separator << "\n"
         << "File: " << file_str << "\n"
         << "Class: " << exception_name_str << "\n"
         << "Message: " << message_str << "\n"
         << separator << "\n"
         << "Backtrace:\n";

  // Process and append each entry in the backtrace
  long backtrace_length = RARRAY_LEN(backtrace);
  for (long i = 1; i < backtrace_length; ++i) {
    VALUE bt_entry = rb_ary_entry(backtrace, i);
    if (NIL_P(bt_entry)) continue;  // Skip nil entries in the backtrace

    // Attempt to convert each backtrace entry to a C string
    const char *bt_entry_str = nullptr;
    try {
      bt_entry_str = StringValueCStr(bt_entry);
    } catch (...) {
      std::cerr << "Warning: Skipping invalid backtrace entry at index " << i << std::endl;
      continue;
    }
    result << "\tfrom " << bt_entry_str << "\n";
  }

  result << separator;

  // Output the constructed error message
  std::cerr << result.str() << std::endl;

  return Qnil;
}

static VALUE script_rescue(VALUE, VALUE exc) {
  VALUE backtrace = rb_ary_to_ary(rb_funcall(exc, rb_intern("backtrace"), 0));
  VALUE message = rb_str_to_str(rb_funcall(exc, rb_intern("message"), 0));
  std::cerr << StringValueCStr(message) << std::endl;
  for (long i = 0; i < RARRAY_LEN(backtrace); ++i) {
    VALUE lp = rb_str_to_str(rb_ary_entry(backtrace, i));
    std::cerr << StringValueCStr(lp) << std::endl;
  }
  return Qnil;
}

// auto main(int argc, char **argv) -> int {
//   initializeRubyInterpreter();
//   //initializeRubyArguments();
//   Init_rgray();

//   std::string scriptPath = determineScriptPath(argc, argv);
//   if (scriptPath.empty()) {
//     std::cerr << "Error: No valid script found." << std::endl;
//     ruby_cleanup(0);
//     return 1;
//   }

//   auto scriptPathValue = rb_str_new_cstr(scriptPath.c_str());
//   //auto result = rb_rescue(rubyScriptLoad, scriptPathValue, script_rescue, Qnil);

//   rb_rescue2(rubyScriptLoad, scriptPathValue, script_rescue, Qnil, rb_eException,
//              static_cast<VALUE>(0));

//   ruby_cleanup(0);
//   return 0;
// }

static auto determineScriptPath(int argc, char **argv) {
  std::string scriptPath;

  if (argc > 1) {
    scriptPath = argv[1];
    if (scriptPath.back() != '/') scriptPath += '/';
    scriptPath += "main.rb";
    if (!FileExists(scriptPath.c_str())) scriptPath.clear();
  }

  if (scriptPath.empty() && FileExists("./main.rb")) scriptPath = "./main.rb";

  return scriptPath;
}

static int initializeRubyInterpreter(const std::string &scriptPath) {
  RUBY_INIT_STACK;
  ruby_init();
  Init_rubyraylib();

  const char *args[] = {"ruby", scriptPath.c_str()};
  int argc = sizeof(args) / sizeof(args[0]);

  return ruby_run_node(ruby_options(argc, const_cast<char **>(args)));
}

int main(int argc, char **argv) {
#ifdef HAVE_LOCALE_H
  setlocale(LC_CTYPE, "");
#endif

  std::string scriptPath = determineScriptPath(argc, argv);
  if (scriptPath.empty()) {
    std::cerr << "Error: No valid script found." << std::endl;
    return 1;
  }

  ruby_sysinit(&argc, (char ***)&argv);
  return initializeRubyInterpreter(scriptPath);
}

