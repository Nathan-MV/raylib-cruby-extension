#include <gui_bindings.h>

// Global gui state control functions
// RAYGUIAPI void GuiEnable(void);                                 // Enable gui controls (global state)
RB_METHOD(rb_gui_enable, GuiEnable)
// RAYGUIAPI void GuiDisable(void);                                // Disable gui controls (global state)
RB_METHOD(rb_gui_disable, GuiDisable)
// RAYGUIAPI void GuiLock(void);                                   // Lock gui controls (global state)
RB_METHOD(rb_gui_lock, GuiLock)
// RAYGUIAPI void GuiUnlock(void);                                 // Unlock gui controls (global state)
RB_METHOD(rb_gui_unlock, GuiUnlock)
// RAYGUIAPI bool GuiIsLocked(void);                               // Check if gui is locked (global state)
RB_METHOD_BOOL(rb_gui_is_locked, GuiIsLocked)
// RAYGUIAPI void GuiSetAlpha(float alpha);                        // Set gui controls alpha (global state), alpha goes from 0.0f to 1.0f
RB_METHOD_ARG_FLOAT(rb_gui_set_alpha, GuiSetAlpha, Qnil)
// RAYGUIAPI void GuiSetState(int state);                          // Set gui state (global state)
RB_METHOD_ARG_INT(rb_gui_set_state, GuiSetState, Qnil)
// RAYGUIAPI int GuiGetState(void);                                // Get gui state (global state)
RB_METHOD_INT(rb_gui_get_state, GuiGetState)

// Font set/get functions
// RAYGUIAPI void GuiSetFont(Font font);                           // Set gui custom font (global state)
// RAYGUIAPI Font GuiGetFont(void);                                // Get gui custom font (global state)

// Style set/get functions
// RAYGUIAPI void GuiSetStyle(int control, int property, int value); // Set one style property
RB_METHOD_ARG_INT_INT_INT(rb_gui_set_style, GuiSetStyle, self)
// RAYGUIAPI int GuiGetStyle(int control, int property);           // Get one style property
RB_METHOD_INT_ARG_INT_INT(rb_gui_get_style, GuiGetStyle)

// Styles loading functions
// RAYGUIAPI void GuiLoadStyle(const char *fileName);              // Load style file over global style variable (.rgs)
RB_METHOD_ARG_STR(rb_gui_load_style, GuiLoadStyle, self)
// RAYGUIAPI void GuiLoadStyleDefault(void);                       // Load style default over global style
RB_METHOD(rb_gui_load_style_default, GuiLoadStyleDefault)

// Tooltips management functions
// RAYGUIAPI void GuiEnableTooltip(void);                          // Enable gui tooltips (global state)
RB_METHOD(rb_gui_enable_tooltip, GuiEnableTooltip)
// RAYGUIAPI void GuiDisableTooltip(void);                         // Disable gui tooltips (global state)
RB_METHOD(rb_gui_disable_tooltip, GuiDisableTooltip)
// RAYGUIAPI void GuiSetTooltip(const char *tooltip);              // Set tooltip string
RB_METHOD_ARG_STR(rb_gui_set_tooltip, GuiSetTooltip, Qnil)

// // Icons functionality
// RAYGUIAPI const char *GuiIconText(int iconId, const char *text); // Get text with icon id prepended (if supported)
// #if !defined(RAYGUI_NO_ICONS)
// RAYGUIAPI void GuiSetIconScale(int scale);                      // Set default icon drawing size
// RAYGUIAPI unsigned int *GuiGetIcons(void);                      // Get raygui icons data pointer
// RAYGUIAPI char **GuiLoadIcons(const char *fileName, bool loadIconsName); // Load raygui icons file (.rgi) into internal icons data
// RAYGUIAPI void GuiDrawIcon(int iconId, int posX, int posY, int pixelSize, Color color); // Draw icon using pixel size at specified position
// #endif

// Controls
//----------------------------------------------------------------------------------------------------------
// Container/separator controls, useful for controls organization
// RAYGUIAPI int GuiWindowBox(RayRectangle bounds, const char *title);                                       // Window Box control, shows a window that can be closed
static auto rb_gui_window_box(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *title = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiWindowBox(*bounds, title);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiGroupBox(RayRectangle bounds, const char *text);                                         // Group Box control with text name
static auto rb_gui_group_box(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiGroupBox(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiLine(RayRectangle bounds, const char *text);                                             // Line separator control, could contain text
static auto rb_gui_line(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiLine(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiPanel(RayRectangle bounds, const char *text);                                            // Panel control, useful to group controls
static auto rb_gui_panel(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiPanel(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiTabBar(RayRectangle bounds, const char **text, int count, int *active);                  // Tab Bar control, returns TAB to be closed or -1
static auto rb_gui_tab_bar(VALUE self, VALUE rb_bounds, VALUE rb_text, VALUE rb_count, VALUE rb_active) {
  Check_Type(rb_text, T_ARRAY);
  auto text_len = RARRAY_LEN(rb_text);

  // Allocate on heap to handle large arrays safely
  const auto **text = (const char **)calloc(text_len, sizeof(char *));
  if (text == NULL) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for text_val");
  }

  for (auto i = 0; i < text_len; i++) {
    VALUE str = rb_ary_entry(rb_text, i);
    text[i] = StringValueCStr(str);
  }

  auto *bounds = get_rect(rb_bounds);
  auto active = NUM2INT(rb_active);

  auto result = GuiTabBar(*bounds, text, RARRAY_LEN(rb_text), &active);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiScrollPanel(RayRectangle bounds, const char *text, RayRectangle content, Vector2 *scroll, RayRectangle *view); // Scroll Panel control
static auto rb_gui_scroll_panel(VALUE self, VALUE rb_bounds, VALUE rb_text, VALUE rb_content, VALUE rb_scroll, VALUE rb_view) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto *content = get_rect(rb_content);
  auto *scroll = get_vec2(rb_scroll);
  auto *view = get_rect(rb_view);

  auto result = GuiScrollPanel(*bounds, text, *content, scroll, view);

  return result ? Qtrue : Qfalse;
}

// Basic controls set
// RAYGUIAPI int GuiLabel(RayRectangle bounds, const char *text);                                            // Label control
static auto rb_gui_label(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiLabel(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiButton(RayRectangle bounds, const char *text);                                           // Button control, returns true when clicked
static auto rb_gui_button(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiButton(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiLabelButton(RayRectangle bounds, const char *text);                                      // Label button control, returns true when clicked
static auto rb_gui_label_button(VALUE self, VALUE rb_text, VALUE rb_bounds) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiLabelButton(*bounds, text);

  return result ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiToggle(RayRectangle bounds, const char *text, bool *active);                             // Toggle Button control
static auto rb_gui_toogle(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_active) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto active = RTEST(rb_active);

  GuiToggle(*bounds, text, &active);

  return active ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiToggleGroup(RayRectangle bounds, const char *text, int *active);                         // Toggle Group control
static auto rb_gui_toogle_group(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_active) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto active = NUM2INT(rb_active);

  GuiToggleGroup(*bounds, text, &active);

  return INT2NUM(active);
}
// RAYGUIAPI int GuiToggleSlider(RayRectangle bounds, const char *text, int *active);                        // Toggle Slider control
static auto rb_gui_toogle_slider(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_active) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto active = NUM2INT(rb_active);

  GuiToggleSlider(*bounds, text, &active);

  return active ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiCheckBox(RayRectangle bounds, const char *text, bool *checked);                          // Check Box control, returns true when active
static auto rb_gui_check_box(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_checked) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto check = RTEST(rb_checked);

  GuiCheckBox(*bounds, text, &check);

  return check ? Qtrue : Qfalse;
}
// RAYGUIAPI int GuiComboBox(RayRectangle bounds, const char *text, int *active);                            // Combo Box control
static auto rb_gui_combo_box(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_active) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto active = NUM2INT(rb_active);

  auto result = GuiComboBox(*bounds, text, &active);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, INT2NUM(active));
}

// RAYGUIAPI int GuiDropdownBox(RayRectangle bounds, const char *text, int *active, bool editMode);          // Dropdown Box control
static auto rb_gui_dropdown_box(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_active,
                                VALUE rb_edit_mode) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto active = NUM2INT(rb_active);
  auto edit_mode = RTEST(rb_edit_mode);

  auto result = GuiDropdownBox(*bounds, text, &active, edit_mode);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, INT2NUM(active));
}

// RAYGUIAPI int GuiSpinner(RayRectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode); // Spinner control
static auto rb_gui_spinner(VALUE self, VALUE rb_bounds, VALUE rb_value,
                            VALUE rb_min_value, VALUE rb_max_value,
                            VALUE rb_edit_mode) {
  auto *bounds = get_rect(rb_bounds);
  auto value = NUM2INT(rb_value);
  auto min_value = NUM2INT(rb_min_value);
  auto max_value = NUM2INT(rb_max_value);
  auto edit_mode = RTEST(rb_edit_mode);

  auto result = GuiSpinner(*bounds, "", &value, min_value, max_value, edit_mode);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, INT2NUM(value));
}
// RAYGUIAPI int GuiValueBox(RayRectangle bounds, const char *text, int *value, int minValue, int maxValue, bool editMode); // Value Box control, updates input text with numbers
static auto rb_gui_value_box(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_value,
                             VALUE rb_min_value, VALUE rb_max_value, VALUE rb_edit_mode) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto value = NUM2INT(rb_value);
  auto minValue = NUM2INT(rb_min_value);
  auto maxValue = NUM2INT(rb_max_value);
  auto editMode = RTEST(rb_edit_mode);

  auto result = GuiValueBox(*bounds, text, &value, minValue, maxValue, editMode);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, INT2NUM(value));
}
// RAYGUIAPI int GuiValueBoxFloat(RayRectangle bounds, const char *text, char *textValue, float *value, bool editMode); // Value box control for float values
static auto rb_gui_value_box_float(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_text_value,
                                   VALUE rb_value, VALUE rb_edit_mode) {
  const auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto textValue = StringValueCStr(rb_text_value);
  float value = NUM2DBL(rb_value);
  auto editMode = RTEST(rb_edit_mode);

  auto result = GuiValueBoxFloat(*bounds, text, textValue, &value, editMode);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, DBL2NUM(value));
}
// RAYGUIAPI int GuiTextBox(RayRectangle bounds, char *text, int textSize, bool editMode);                   // Text Box control, updates input text
static auto rb_gui_text_box(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_text_size,
                            VALUE rb_edit_mode) {
  auto *text = StringValueCStr(rb_text);
  auto *bounds = get_rect(rb_bounds);
  auto textSize = NUM2INT(rb_text_size);
  auto editMode = RTEST(rb_edit_mode);

  auto result = GuiTextBox(*bounds, text, textSize, editMode);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse,
                              rb_str_new_cstr(text));
}

// RAYGUIAPI int GuiSlider(RayRectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Slider control
static auto rb_gui_slider(VALUE self, VALUE rb_bounds, VALUE rb_text_left, VALUE rb_text_right, VALUE rb_value, VALUE rb_min_value, VALUE rb_max_value) {
  // auto *bounds = get_rect(rb_bounds);
  // const char *textLeft = StringValueCStr(rb_text_left);
  // const char *textRight = StringValueCStr(rb_text_right);
  // auto value = NUM2DBL(rb_value);
  // auto minValue = NUM2DBL(rb_min_value);
  // auto maxValue = NUM2DBL(rb_max_value);

  // auto result = GuiSlider(*bounds, textLeft, textRight, &value, minValue, maxValue);

  // return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, DBL2NUM(value));
}
// RAYGUIAPI int GuiSliderBar(RayRectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Slider Bar control
static auto rb_gui_slider_bar(VALUE self, VALUE rb_bounds, VALUE rb_text_left, VALUE rb_text_right, VALUE rb_value, VALUE rb_min_value, VALUE rb_max_value) {
  // auto *bounds = get_rect(rb_bounds);
  // const char *textLeft = StringValueCStr(rb_text_left);
  // const char *textRight = StringValueCStr(rb_text_right);
  // auto value = NUM2DBL(rb_value);
  // auto minValue = NUM2DBL(rb_min_value);
  // auto maxValue = NUM2DBL(rb_max_value);

  // auto result = GuiSlider(*bounds, textLeft, textRight, &value, minValue, maxValue);

  // return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, DBL2NUM(value));
}
// RAYGUIAPI int GuiProgressBar(RayRectangle bounds, const char *textLeft, const char *textRight, float *value, float minValue, float maxValue); // Progress Bar control
static auto rb_gui_progress_bar(VALUE self, VALUE rb_bounds, VALUE rb_text_left, VALUE rb_text_right, VALUE rb_value, VALUE rb_min_value, VALUE rb_max_value) {
  // auto *bounds = get_rect(rb_bounds);
  // const char *textLeft = StringValueCStr(rb_text_left);
  // const char *textRight = StringValueCStr(rb_text_right);
  // auto value = NUM2DBL(rb_value);
  // auto minValue = NUM2DBL(rb_min_value);
  // auto maxValue = NUM2DBL(rb_max_value);

  // auto result = GuiProgressBar(*bounds, textLeft, textRight, &value, minValue, maxValue);

  // return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, DBL2NUM(value));
}
// RAYGUIAPI int GuiStatusBar(RayRectangle bounds, const char *text);                                        // Status Bar control, shows info text
static auto rb_gui_status_bar(VALUE self, VALUE rb_bounds, VALUE rb_text) {
  auto *bounds = get_rect(rb_bounds);
  const char *text = StringValueCStr(rb_text);

  GuiStatusBar(*bounds, text);

  return Qnil;
}
// RAYGUIAPI int GuiDummyRec(RayRectangle bounds, const char *text);                                         // Dummy control for placeholders
static auto rb_gui_dummy_rec(VALUE self, VALUE rb_bounds, VALUE rb_text) {
  auto *bounds = get_rect(rb_bounds);
  const char *text = StringValueCStr(rb_text);

  GuiDummyRec(*bounds, text);

  return Qnil;
}
// RAYGUIAPI int GuiGrid(RayRectangle bounds, const char *text, float spacing, int subdivs, Vector2 *mouseCell); // Grid control
static auto rb_gui_grid(VALUE self, VALUE rb_bounds, VALUE rb_text, VALUE rb_spacing, VALUE rb_subdivs, VALUE rb_mouse_ceell) {
  auto *bounds = get_rect(rb_bounds);
  const char *text = StringValueCStr(rb_text);
  auto spacing = NUM2DBL(rb_spacing);
  auto subdivs = NUM2INT(rb_subdivs);
  auto *mouseCell = get_vec2(rb_mouse_ceell);

  auto result = GuiGrid(*bounds, text, spacing, subdivs, mouseCell);

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse,
                              INT2NUM(mouseCell->x), INT2NUM(mouseCell->y));
}

// Advance controls set
// RAYGUIAPI int GuiListView(RayRectangle bounds, const char *text, int *scrollIndex, int *active);          // List View control
// Useless, hard limit of 128 items
// RAYGUIAPI int GuiListViewEx(RayRectangle bounds, const char **text, int count, int *scrollIndex, int *active, int *focus); // List View with extended parameters
static auto rb_gui_list_view_ex(VALUE self, VALUE rb_text, VALUE rb_bounds, VALUE rb_scroll_index,
                                VALUE rb_active) {
  Check_Type(rb_text, T_ARRAY);
  auto text_len = RARRAY_LEN(rb_text);

  // Allocate on heap to handle large arrays safely
  const auto **text = (const char **)calloc(text_len, sizeof(char *));
  if (text == NULL) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for text_val");
  }

  for (auto i = 0; i < text_len; i++) {
    VALUE str = rb_ary_entry(rb_text, i);
    text[i] = StringValueCStr(str);
  }

  auto *bounds = get_rect(rb_bounds);

  auto scrollIndex = NUM2INT(rb_scroll_index);
  auto active = NUM2INT(rb_active);

  GuiListViewEx(*bounds, text, text_len, &scrollIndex, &active, NULL);

  free(text);

  return rb_ary_new_from_args(2, INT2NUM(scrollIndex), INT2NUM(active));
}
// RAYGUIAPI int GuiMessageBox(RayRectangle bounds, const char *title, const char *message, const char *buttons); // Message Box control, displays a message
static  auto rb_gui_message_box(VALUE self, VALUE rb_bounds, VALUE rb_title, VALUE rb_message, VALUE rb_buttons) {
  const auto *title_str = StringValueCStr(rb_title);
  const auto *message_str = StringValueCStr(rb_message);
  const auto *buttons_str = StringValueCStr(rb_buttons);
  auto *bounds = get_rect(rb_bounds);

  auto result = GuiMessageBox(*bounds, title_str, message_str, buttons_str);

  return INT2NUM(result);
}
// RAYGUIAPI int GuiTextInputBox(RayRectangle bounds, const char *title, const char *message, const char *buttons, char *text, int textMaxSize, bool *secretViewActive); // Text Input Box control, ask for text, supports secret
static auto rb_gui_text_input_box(VALUE self, VALUE rb_bounds, VALUE rb_title, VALUE rb_message,
                                  VALUE rb_buttons, VALUE rb_text, VALUE rb_text_max_size,
                                  VALUE rb_secret_view_active) {
  const auto *title_str = StringValueCStr(rb_title);
  const auto *message_str = StringValueCStr(rb_message);
  const auto *buttons_str = StringValueCStr(rb_buttons);
  auto *bounds = get_rect(rb_bounds);
  auto textMaxSize = NUM2INT(rb_text_max_size);

  // Create a buffer for text that can be modified
  char *text_buf = ALLOC_N(char, textMaxSize + 1);
  strncpy(text_buf, StringValueCStr(rb_text), textMaxSize);
  text_buf[textMaxSize] = '\0';  // Ensure null-termination

  bool secretViewActive = RTEST(rb_secret_view_active);

  auto result = GuiTextInputBox(*bounds, title_str, message_str, buttons_str, text_buf, textMaxSize,
                                &secretViewActive);

  // Create the return array: result (true/false) and the potentially modified text
  VALUE ret_text = rb_str_new_cstr(text_buf);
  xfree(text_buf);  // Free the buffer after use

  return rb_ary_new_from_args(2, result ? Qtrue : Qfalse, ret_text);
}
// RAYGUIAPI int GuiColorPicker(RayRectangle bounds, const char *text, Color *color);                        // Color Picker control (multiple color controls)
static auto rb_gui_color_picker(VALUE self, VALUE rb_bounds, VALUE rb_text, VALUE rb_color) {
  // auto *bounds = get_rect(rb_bounds);
  // const auto *text_str = StringValueCStr(rb_text);
  // auto *color = get_color(rb_color);

  // auto result = GuiColorPicker(*bounds, text_str, color);

  // return rb_ary_new_from_args(2, result ? Qtrue : Qfalse,
  //                             rb_color_new(color->r, color->g, color->b, color->a));
}
// RAYGUIAPI int GuiColorPanel(RayRectangle bounds, const char *text, Color *color);                         // Color Panel control
// RAYGUIAPI int GuiColorBarAlpha(RayRectangle bounds, const char *text, float *alpha);                      // Color Bar Alpha control
// RAYGUIAPI int GuiColorBarHue(RayRectangle bounds, const char *text, float *value);                        // Color Bar Hue control
// RAYGUIAPI int GuiColorPickerHSV(RayRectangle bounds, const char *text, Vector3 *colorHsv);                // Color Picker control that avoids conversion to RGB on each call (multiple color controls)
// RAYGUIAPI int GuiColorPanelHSV(RayRectangle bounds, const char *text, Vector3 *colorHsv);                 // Color Panel control that updates Hue-Saturation-Value color value, used by GuiColorPickerHSV()

// Initializes the GUI module and defines its functions
extern "C" void Init_Gui() {
  VALUE rb_mGui = rb_define_module_under(rb_mRL, "Gui");

  // Global gui state control functions
  rb_define_module_function(rb_mGui, "enable", rb_gui_enable, 0);
  rb_define_module_function(rb_mGui, "disable", rb_gui_disable, 0);
  rb_define_module_function(rb_mGui, "lock", rb_gui_lock, 0);
  rb_define_module_function(rb_mGui, "unlock", rb_gui_unlock, 0);
  rb_define_module_function(rb_mGui, "locked?", rb_gui_is_locked, 0);
  rb_define_module_function(rb_mGui, "alpha=", rb_gui_set_alpha, 1);
  rb_define_module_function(rb_mGui, "state=", rb_gui_set_state, 1);
  rb_define_module_function(rb_mGui, "state", rb_gui_get_state, 0);

  // Style set/get functions
  rb_define_module_function(rb_mGui, "set_style", rb_gui_set_style, 3);
  rb_define_module_function(rb_mGui, "style", rb_gui_get_style, 2);

  // Styles loading functions
  rb_define_module_function(rb_mGui, "load_style", rb_gui_load_style, 1);
  rb_define_module_function(rb_mGui, "load_default_style", rb_gui_load_style_default, 0);

  // Tooltips management functions
  rb_define_module_function(rb_mGui, "enable_tooltip", rb_gui_enable_tooltip, 0);
  rb_define_module_function(rb_mGui, "disable_tooltip", rb_gui_disable_tooltip, 0);
  rb_define_module_function(rb_mGui, "tooltip=", rb_gui_set_tooltip, 1);

  rb_define_module_function(rb_mGui, "window_box", rb_gui_window_box, 2);
  rb_define_module_function(rb_mGui, "group_box", rb_gui_group_box, 2);
  rb_define_module_function(rb_mGui, "line", rb_gui_line, 2);
  rb_define_module_function(rb_mGui, "panel", rb_gui_panel, 2);
  rb_define_module_function(rb_mGui, "tab_bar", rb_gui_tab_bar, 4);
  rb_define_module_function(rb_mGui, "scroll_panel", rb_gui_scroll_panel, 5);

  rb_define_module_function(rb_mGui, "label", rb_gui_label, 2);
  rb_define_module_function(rb_mGui, "button", rb_gui_button, 2);
  rb_define_module_function(rb_mGui, "label_button", rb_gui_label_button, 2);
  rb_define_module_function(rb_mGui, "toogle", rb_gui_toogle, 3);
  rb_define_module_function(rb_mGui, "toogle_group", rb_gui_toogle_group, 3);
  rb_define_module_function(rb_mGui, "toogle_slider", rb_gui_toogle_slider, 3);
  rb_define_module_function(rb_mGui, "check_box", rb_gui_check_box, 3);
  rb_define_module_function(rb_mGui, "combo_box", rb_gui_combo_box, 3);
  rb_define_module_function(rb_mGui, "dropdown_box", rb_gui_dropdown_box, 4);
  rb_define_module_function(rb_mGui, "spinner", rb_gui_spinner, 5);
  rb_define_module_function(rb_mGui, "value_box", rb_gui_value_box, 6);
  rb_define_module_function(rb_mGui, "value_box_float", rb_gui_value_box_float, 5);
  rb_define_module_function(rb_mGui, "text_box", rb_gui_text_box, 4);
  //rb_define_module_function(rb_mGui, "slider", rb_gui_slider, 6);
  //rb_define_module_function(rb_mGui, "slider_bar", rb_gui_slider_bar, 5);
  //rb_define_module_function(rb_mGui, "progress_bar", rb_gui_progress_bar, 6);
  rb_define_module_function(rb_mGui, "status_bar", rb_gui_status_bar, 2);
  rb_define_module_function(rb_mGui, "dummy_rec", rb_gui_dummy_rec, 2);
  rb_define_module_function(rb_mGui, "grid", rb_gui_grid, 5);

  rb_define_module_function(rb_mGui, "list_view", rb_gui_list_view_ex, 4);
  rb_define_module_function(rb_mGui, "message_box", rb_gui_message_box, 4);
  rb_define_module_function(rb_mGui, "text_input_box", rb_gui_text_input_box, 7);
  //rb_define_module_function(rb_mGui, "color_picker", rb_gui_color_picker, 3);

  // Gui control state
  rb_define_const(rb_mGui, "STATE_NORMAL", INT2NUM(STATE_NORMAL));
  rb_define_const(rb_mGui, "STATE_FOCUSED", INT2NUM(STATE_FOCUSED));
  rb_define_const(rb_mGui, "STATE_PRESSED", INT2NUM(STATE_PRESSED));
  rb_define_const(rb_mGui, "STATE_DISABLED", INT2NUM(STATE_DISABLED));

  // Gui control text alignment
  rb_define_const(rb_mGui, "TEXT_ALIGN_LEFT", INT2NUM(TEXT_ALIGN_LEFT));
  rb_define_const(rb_mGui, "TEXT_ALIGN_CENTER", INT2NUM(TEXT_ALIGN_CENTER));
  rb_define_const(rb_mGui, "TEXT_ALIGN_RIGHT", INT2NUM(TEXT_ALIGN_RIGHT));

  // Gui control text alignment vertical
  rb_define_const(rb_mGui, "TEXT_ALIGN_TOP", INT2NUM(TEXT_ALIGN_TOP));
  rb_define_const(rb_mGui, "TEXT_ALIGN_MIDDLE", INT2NUM(TEXT_ALIGN_MIDDLE));
  rb_define_const(rb_mGui, "TEXT_ALIGN_BOTTOM", INT2NUM(TEXT_ALIGN_BOTTOM));

  // Gui control text wrap mode
  rb_define_const(rb_mGui, "TEXT_WRAP_NONE", INT2NUM(TEXT_WRAP_NONE));
  rb_define_const(rb_mGui, "TEXT_WRAP_CHAR", INT2NUM(TEXT_WRAP_CHAR));
  rb_define_const(rb_mGui, "TEXT_WRAP_WORD", INT2NUM(TEXT_WRAP_WORD));

  // Gui controls
  rb_define_const(rb_mGui, "DEFAULT", INT2NUM(DEFAULT));
  rb_define_const(rb_mGui, "LABEL", INT2NUM(LABEL));
  rb_define_const(rb_mGui, "BUTTON", INT2NUM(BUTTON));
  rb_define_const(rb_mGui, "TOGGLE", INT2NUM(TOGGLE));
  rb_define_const(rb_mGui, "SLIDER", INT2NUM(SLIDER));
  rb_define_const(rb_mGui, "PROGRESSBAR", INT2NUM(PROGRESSBAR));
  rb_define_const(rb_mGui, "CHECKBOX", INT2NUM(CHECKBOX));
  rb_define_const(rb_mGui, "COMBOBOX", INT2NUM(COMBOBOX));
  rb_define_const(rb_mGui, "DROPDOWNBOX", INT2NUM(DROPDOWNBOX));
  rb_define_const(rb_mGui, "TEXTBOX", INT2NUM(TEXTBOX));
  rb_define_const(rb_mGui, "VALUEBOX", INT2NUM(VALUEBOX));
  rb_define_const(rb_mGui, "SPINNER", INT2NUM(SPINNER));
  rb_define_const(rb_mGui, "LISTVIEW", INT2NUM(LISTVIEW));
  rb_define_const(rb_mGui, "COLORPICKER", INT2NUM(COLORPICKER));
  rb_define_const(rb_mGui, "SCROLLBAR", INT2NUM(SCROLLBAR));
  rb_define_const(rb_mGui, "STATUSBAR", INT2NUM(STATUSBAR));

  // Gui base properties for every control
  rb_define_const(rb_mGui, "BORDER_COLOR_NORMAL", INT2NUM(BORDER_COLOR_NORMAL));
  rb_define_const(rb_mGui, "BASE_COLOR_NORMAL", INT2NUM(BASE_COLOR_NORMAL));
  rb_define_const(rb_mGui, "TEXT_COLOR_NORMAL", INT2NUM(TEXT_COLOR_NORMAL));
  rb_define_const(rb_mGui, "BORDER_COLOR_FOCUSED",
                  INT2NUM(BORDER_COLOR_FOCUSED));
  rb_define_const(rb_mGui, "BASE_COLOR_FOCUSED", INT2NUM(BASE_COLOR_FOCUSED));
  rb_define_const(rb_mGui, "TEXT_COLOR_FOCUSED", INT2NUM(TEXT_COLOR_FOCUSED));
  rb_define_const(rb_mGui, "BORDER_COLOR_PRESSED",
                  INT2NUM(BORDER_COLOR_PRESSED));
  rb_define_const(rb_mGui, "BASE_COLOR_PRESSED", INT2NUM(BASE_COLOR_PRESSED));
  rb_define_const(rb_mGui, "TEXT_COLOR_PRESSED", INT2NUM(TEXT_COLOR_PRESSED));
  rb_define_const(rb_mGui, "BORDER_COLOR_DISABLED",
                  INT2NUM(BORDER_COLOR_DISABLED));
  rb_define_const(rb_mGui, "BASE_COLOR_DISABLED", INT2NUM(BASE_COLOR_DISABLED));
  rb_define_const(rb_mGui, "TEXT_COLOR_DISABLED", INT2NUM(TEXT_COLOR_DISABLED));
  rb_define_const(rb_mGui, "BORDER_WIDTH", INT2NUM(BORDER_WIDTH));
  rb_define_const(rb_mGui, "TEXT_PADDING", INT2NUM(TEXT_PADDING));
  rb_define_const(rb_mGui, "TEXT_ALIGNMENT", INT2NUM(TEXT_ALIGNMENT));

  rb_define_const(rb_mGui, "TEXT_SIZE", INT2NUM(TEXT_SIZE));
  rb_define_const(rb_mGui, "TEXT_SPACING", INT2NUM(TEXT_SPACING));
  rb_define_const(rb_mGui, "LINE_COLOR", INT2NUM(LINE_COLOR));
  rb_define_const(rb_mGui, "BACKGROUND_COLOR", INT2NUM(BACKGROUND_COLOR));
  rb_define_const(rb_mGui, "TEXT_LINE_SPACING", INT2NUM(TEXT_LINE_SPACING));
  rb_define_const(rb_mGui, "TEXT_ALIGNMENT_VERTICAL",
                  INT2NUM(TEXT_ALIGNMENT_VERTICAL));
  rb_define_const(rb_mGui, "TEXT_WRAP_MODE", INT2NUM(TEXT_WRAP_MODE));

  // Toggle/ToggleGroup
  rb_define_const(rb_mGui, "GROUP_PADDING", INT2NUM(GROUP_PADDING));

  // Slider/SliderBar
  rb_define_const(rb_mGui, "SLIDER_WIDTH", INT2NUM(SLIDER_WIDTH));
  rb_define_const(rb_mGui, "SLIDER_PADDING", INT2NUM(SLIDER_PADDING));

  // ProgressBar
  rb_define_const(rb_mGui, "PROGRESS_PADDING", INT2NUM(PROGRESS_PADDING));

  // ScrollBar
  rb_define_const(rb_mGui, "ARROWS_SIZE", INT2NUM(ARROWS_SIZE));
  rb_define_const(rb_mGui, "ARROWS_VISIBLE", INT2NUM(ARROWS_VISIBLE));
  rb_define_const(rb_mGui, "SCROLL_SLIDER_PADDING",
                  INT2NUM(SCROLL_SLIDER_PADDING));
  rb_define_const(rb_mGui, "SCROLL_SLIDER_SIZE", INT2NUM(SCROLL_SLIDER_SIZE));
  rb_define_const(rb_mGui, "SCROLL_PADDING", INT2NUM(SCROLL_PADDING));
  rb_define_const(rb_mGui, "SCROLL_SPEED", INT2NUM(SCROLL_SPEED));

  // CheckBox
  rb_define_const(rb_mGui, "CHECK_PADDING", INT2NUM(CHECK_PADDING));

  // ComboBox
  rb_define_const(rb_mGui, "COMBO_BUTTON_WIDTH", INT2NUM(COMBO_BUTTON_WIDTH));
  rb_define_const(rb_mGui, "COMBO_BUTTON_SPACING",
                  INT2NUM(COMBO_BUTTON_SPACING));

  // DropdownBox
  rb_define_const(rb_mGui, "ARROW_PADDING", INT2NUM(ARROW_PADDING));
  rb_define_const(rb_mGui, "DROPDOWN_ITEMS_SPACING",
                  INT2NUM(DROPDOWN_ITEMS_SPACING));

  // TextBox/TextBoxMulti/ValueBox/Spinner
  rb_define_const(rb_mGui, "TEXT_READONLY", INT2NUM(TEXT_READONLY));

  // Spinner
  rb_define_const(rb_mGui, "SPIN_BUTTON_WIDTH", INT2NUM(SPIN_BUTTON_WIDTH));
  rb_define_const(rb_mGui, "SPIN_BUTTON_SPACING", INT2NUM(SPIN_BUTTON_SPACING));

  // ListView
  rb_define_const(rb_mGui, "LIST_ITEMS_HEIGHT", INT2NUM(LIST_ITEMS_HEIGHT));
  rb_define_const(rb_mGui, "LIST_ITEMS_SPACING", INT2NUM(LIST_ITEMS_SPACING));
  rb_define_const(rb_mGui, "SCROLLBAR_WIDTH", INT2NUM(SCROLLBAR_WIDTH));
  rb_define_const(rb_mGui, "SCROLLBAR_SIDE", INT2NUM(SCROLLBAR_SIDE));

  // ColorPicker
  rb_define_const(rb_mGui, "COLOR_SELECTOR_SIZE", INT2NUM(COLOR_SELECTOR_SIZE));
  rb_define_const(rb_mGui, "HUEBAR_WIDTH", INT2NUM(HUEBAR_WIDTH));
  rb_define_const(rb_mGui, "HUEBAR_PADDING", INT2NUM(HUEBAR_PADDING));
  rb_define_const(rb_mGui, "HUEBAR_SELECTOR_HEIGHT",
                  INT2NUM(HUEBAR_SELECTOR_HEIGHT));
  rb_define_const(rb_mGui, "HUEBAR_SELECTOR_OVERFLOW",
                  INT2NUM(HUEBAR_SELECTOR_OVERFLOW));
}
