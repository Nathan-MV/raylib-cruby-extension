#include "gui.hpp"

static VALUE rb_gui_label(VALUE self, VALUE bounds, VALUE text) {
  Rectangle *rect = get_rect(bounds);
  const char *text_val = StringValueCStr(text);

  int result = GuiLabel(*rect, text_val);

  return result ? Qtrue : Qfalse;
}

static VALUE rb_gui_label_button(VALUE self, VALUE bounds, VALUE text) {
  Rectangle *rect = get_rect(bounds);
  const char *text_val = StringValueCStr(text);

  int result = GuiLabelButton(*rect, text_val);

  return result ? Qtrue : Qfalse;
}

// Initializes the GUI module and defines its functions
void initializeGui() {
  VALUE rb_cGui = rb_define_module("GUI");

  rb_define_module_function(rb_cGui, "label", rb_gui_label, 2);
  rb_define_module_function(rb_cGui, "label_button", rb_gui_label_button, 2);
}
