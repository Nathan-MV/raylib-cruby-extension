#include "rubyraylib.hpp"

RUBY_FUNC_EXPORTED void Init_rubyraylib(void) {
  initializeKernel();

  // Modules
  initializeWindow();
  initializeInput();
  initializeKeyboard();
  initializeMouse();
  initializeGamepad();
  initializeTouch();
  initializeGestures();
  initializeDraw();
  initializeShapes();

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
  std::vector<const char *> args{"RUBY", "-e ", "--yjit", "--parser=prism"};
  void *rubyNode = ruby_options(args.size(), const_cast<char **>(args.data()));
  int executionState = 0;
  bool success = ruby_executable_node(rubyNode, &executionState);
  if (success) {
    ruby_exec_node(rubyNode);
  } else {
    std::cerr << "RUBY: Failed to execute ruby arguments" << std::endl;
    ruby_cleanup(executionState);
  }
}

static VALUE script_run(VALUE) {
  rb_ary_push(rb_gv_get("$LOAD_PATH"), rb_str_new_literal("./script"));
  rb_load(rb_str_new_literal("./main.rb"), 0);
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

int main() {
  // Initialize components
  initializeRubyInterpreter();
  initializeRubyArguments();
  Init_rubyraylib();

  try {
    rb_rescue2(script_run, Qnil, script_rescue, Qnil, rb_eException,
               static_cast<VALUE>(0));
  } catch (std::exception &e) {
    std::string msg = "Error:\n";
    std::cerr << msg + e.what() << std::endl;
  }
  ruby_finalize();

  // Return success or failure based on script evaluation
  return Qnil;
}
