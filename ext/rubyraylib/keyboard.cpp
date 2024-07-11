#include "keyboard.hpp"

//------------------------------------------------------------------------------------
// Input Handling Functions (Module: core)
//------------------------------------------------------------------------------------

// Input-related functions: keyboard
// RLAPI bool IsKeyPressed(int key);                             // Check if a key has been pressed once
RB_METHOD_BOOL_ARG_INT(rb_key_pressed, IsKeyPressed)
// RLAPI bool IsKeyPressedRepeat(int key);                       // Check if a key has been pressed again (Only PLATFORM_DESKTOP)
RB_METHOD_BOOL_ARG_INT(rb_key_pressed_repeat, IsKeyPressedRepeat)
// RLAPI bool IsKeyDown(int key);                                // Check if a key is being pressed
RB_METHOD_BOOL_ARG_INT(rb_key_down, IsKeyDown)
// RLAPI bool IsKeyReleased(int key);                            // Check if a key has been released once
RB_METHOD_BOOL_ARG_INT(rb_key_released, IsKeyReleased)
// RLAPI bool IsKeyUp(int key);                                  // Check if a key is NOT being pressed
RB_METHOD_BOOL_ARG_INT(rb_key_up, IsKeyUp)
// RLAPI int GetKeyPressed(void);                                // Get key pressed (keycode), call it multiple times for keys queued, returns 0 when the queue is empty
RB_METHOD_INT(rb_get_key_pressed, GetKeyPressed)
// RLAPI int GetCharPressed(void);                               // Get char pressed (unicode), call it multiple times for chars queued, returns 0 when the queue is empty
RB_METHOD_INT(rb_get_char_pressed, GetCharPressed)
// RLAPI void SetExitKey(int key);                               // Set a custom key to exit program (default is ESC)
RB_METHOD_ARG_INT(rb_set_exit_key, SetExitKey)

extern "C" void initializeKeyboard() {
  VALUE rb_mKeyboard = rb_define_module("Keyboard");

  rb_define_module_function(rb_mKeyboard, "pressed?", rb_key_pressed, 1);
	rb_define_module_function(rb_mKeyboard, "repeat?", rb_key_pressed_repeat, 1);
	rb_define_module_function(rb_mKeyboard, "down?", rb_key_down, 1);
	rb_define_module_function(rb_mKeyboard, "released?", rb_key_released, 1);
	rb_define_module_function(rb_mKeyboard, "up?", rb_key_up, 1);
	rb_define_module_function(rb_mKeyboard, "pressed", rb_get_key_pressed, 0);
	rb_define_module_function(rb_mKeyboard, "char_pressed", rb_get_char_pressed, 0);
	rb_define_module_function(rb_mKeyboard, "exit_key=", rb_set_exit_key, 1);

  // Alphanumeric keys
  rb_define_const(rb_mKeyboard, "NULL", INT2NUM(0));
  rb_define_const(rb_mKeyboard, "APOSTROPHE", INT2NUM(39));
  rb_define_const(rb_mKeyboard, "COMMA", INT2NUM(44));
  rb_define_const(rb_mKeyboard, "MINUS", INT2NUM(45));
  rb_define_const(rb_mKeyboard, "PERIOD", INT2NUM(46));
  rb_define_const(rb_mKeyboard, "SLASH", INT2NUM(47));
  rb_define_const(rb_mKeyboard, "ZERO", INT2NUM(48));
  rb_define_const(rb_mKeyboard, "ONE", INT2NUM(49));
  rb_define_const(rb_mKeyboard, "TWO", INT2NUM(50));
  rb_define_const(rb_mKeyboard, "THREE", INT2NUM(51));
  rb_define_const(rb_mKeyboard, "FOUR", INT2NUM(52));
  rb_define_const(rb_mKeyboard, "FIVE", INT2NUM(53));
  rb_define_const(rb_mKeyboard, "SIX", INT2NUM(54));
  rb_define_const(rb_mKeyboard, "SEVEN", INT2NUM(55));
  rb_define_const(rb_mKeyboard, "EIGHT", INT2NUM(56));
  rb_define_const(rb_mKeyboard, "NINE", INT2NUM(57));
  rb_define_const(rb_mKeyboard, "SEMICOLON", INT2NUM(59));
  rb_define_const(rb_mKeyboard, "EQUAL", INT2NUM(61));
  rb_define_const(rb_mKeyboard, "A", INT2NUM(65));
  rb_define_const(rb_mKeyboard, "B", INT2NUM(66));
  rb_define_const(rb_mKeyboard, "C", INT2NUM(67));
  rb_define_const(rb_mKeyboard, "D", INT2NUM(68));
  rb_define_const(rb_mKeyboard, "E", INT2NUM(69));
  rb_define_const(rb_mKeyboard, "F", INT2NUM(70));
  rb_define_const(rb_mKeyboard, "G", INT2NUM(71));
  rb_define_const(rb_mKeyboard, "H", INT2NUM(72));
  rb_define_const(rb_mKeyboard, "I", INT2NUM(73));
  rb_define_const(rb_mKeyboard, "J", INT2NUM(74));
  rb_define_const(rb_mKeyboard, "K", INT2NUM(75));
  rb_define_const(rb_mKeyboard, "L", INT2NUM(76));
  rb_define_const(rb_mKeyboard, "M", INT2NUM(77));
  rb_define_const(rb_mKeyboard, "N", INT2NUM(78));
  rb_define_const(rb_mKeyboard, "O", INT2NUM(79));
  rb_define_const(rb_mKeyboard, "P", INT2NUM(80));
  rb_define_const(rb_mKeyboard, "Q", INT2NUM(81));
  rb_define_const(rb_mKeyboard, "R", INT2NUM(82));
  rb_define_const(rb_mKeyboard, "S", INT2NUM(83));
  rb_define_const(rb_mKeyboard, "T", INT2NUM(84));
  rb_define_const(rb_mKeyboard, "U", INT2NUM(85));
  rb_define_const(rb_mKeyboard, "V", INT2NUM(86));
  rb_define_const(rb_mKeyboard, "W", INT2NUM(87));
  rb_define_const(rb_mKeyboard, "X", INT2NUM(88));
  rb_define_const(rb_mKeyboard, "Y", INT2NUM(89));
  rb_define_const(rb_mKeyboard, "Z", INT2NUM(90));
  rb_define_const(rb_mKeyboard, "LEFT_BRACKET", INT2NUM(91));
  rb_define_const(rb_mKeyboard, "BACKSLASH", INT2NUM(92));
  rb_define_const(rb_mKeyboard, "RIGHT_BRACKET", INT2NUM(93));
  rb_define_const(rb_mKeyboard, "GRAVE", INT2NUM(96));

  // Function keys
  rb_define_const(rb_mKeyboard, "SPACE", INT2NUM(32));
  rb_define_const(rb_mKeyboard, "ESCAPE", INT2NUM(256));
  rb_define_const(rb_mKeyboard, "ENTER", INT2NUM(257));
  rb_define_const(rb_mKeyboard, "TAB", INT2NUM(258));
  rb_define_const(rb_mKeyboard, "BACKSPACE", INT2NUM(259));
  rb_define_const(rb_mKeyboard, "INSERT", INT2NUM(260));
  rb_define_const(rb_mKeyboard, "DELETE", INT2NUM(261));
  rb_define_const(rb_mKeyboard, "RIGHT", INT2NUM(262));
  rb_define_const(rb_mKeyboard, "LEFT", INT2NUM(263));
  rb_define_const(rb_mKeyboard, "DOWN", INT2NUM(264));
  rb_define_const(rb_mKeyboard, "UP", INT2NUM(265));
  rb_define_const(rb_mKeyboard, "PAGE_UP", INT2NUM(266));
  rb_define_const(rb_mKeyboard, "PAGE_DOWN", INT2NUM(267));
  rb_define_const(rb_mKeyboard, "HOME", INT2NUM(268));
  rb_define_const(rb_mKeyboard, "END", INT2NUM(269));
  rb_define_const(rb_mKeyboard, "CAPS_LOCK", INT2NUM(280));
  rb_define_const(rb_mKeyboard, "SCROLL_LOCK", INT2NUM(281));
  rb_define_const(rb_mKeyboard, "NUM_LOCK", INT2NUM(282));
  rb_define_const(rb_mKeyboard, "PRINT_SCREEN", INT2NUM(283));
  rb_define_const(rb_mKeyboard, "PAUSE", INT2NUM(284));
  rb_define_const(rb_mKeyboard, "F1", INT2NUM(290));
  rb_define_const(rb_mKeyboard, "F2", INT2NUM(291));
  rb_define_const(rb_mKeyboard, "F3", INT2NUM(292));
  rb_define_const(rb_mKeyboard, "F4", INT2NUM(293));
  rb_define_const(rb_mKeyboard, "F5", INT2NUM(294));
  rb_define_const(rb_mKeyboard, "F6", INT2NUM(295));
  rb_define_const(rb_mKeyboard, "F7", INT2NUM(296));
  rb_define_const(rb_mKeyboard, "F8", INT2NUM(297));
  rb_define_const(rb_mKeyboard, "F9", INT2NUM(298));
  rb_define_const(rb_mKeyboard, "F10", INT2NUM(299));
  rb_define_const(rb_mKeyboard, "F11", INT2NUM(300));
  rb_define_const(rb_mKeyboard, "F12", INT2NUM(301));
  rb_define_const(rb_mKeyboard, "LEFT_SHIFT", INT2NUM(340));
  rb_define_const(rb_mKeyboard, "LEFT_CONTROL", INT2NUM(341));
  rb_define_const(rb_mKeyboard, "LEFT_ALT", INT2NUM(342));
  rb_define_const(rb_mKeyboard, "LEFT_SUPER", INT2NUM(343));
  rb_define_const(rb_mKeyboard, "RIGHT_SHIFT", INT2NUM(344));
  rb_define_const(rb_mKeyboard, "RIGHT_CONTROL", INT2NUM(345));
  rb_define_const(rb_mKeyboard, "RIGHT_ALT", INT2NUM(346));
  rb_define_const(rb_mKeyboard, "RIGHT_SUPER", INT2NUM(347));
  rb_define_const(rb_mKeyboard, "KB_MENU", INT2NUM(348));

  // Keypad keys
  rb_define_const(rb_mKeyboard, "KP_0", INT2NUM(320));
  rb_define_const(rb_mKeyboard, "KP_1", INT2NUM(321));
  rb_define_const(rb_mKeyboard, "KP_2", INT2NUM(322));
  rb_define_const(rb_mKeyboard, "KP_3", INT2NUM(323));
  rb_define_const(rb_mKeyboard, "KP_4", INT2NUM(324));
  rb_define_const(rb_mKeyboard, "KP_5", INT2NUM(325));
  rb_define_const(rb_mKeyboard, "KP_6", INT2NUM(326));
  rb_define_const(rb_mKeyboard, "KP_7", INT2NUM(327));
  rb_define_const(rb_mKeyboard, "KP_8", INT2NUM(328));
  rb_define_const(rb_mKeyboard, "KP_9", INT2NUM(329));
  rb_define_const(rb_mKeyboard, "KP_DECIMAL", INT2NUM(330));
  rb_define_const(rb_mKeyboard, "KP_DIVIDE", INT2NUM(331));
  rb_define_const(rb_mKeyboard, "KP_MULTIPLY", INT2NUM(332));
  rb_define_const(rb_mKeyboard, "KP_SUBTRACT", INT2NUM(333));
  rb_define_const(rb_mKeyboard, "KP_ADD", INT2NUM(334));
  rb_define_const(rb_mKeyboard, "KP_ENTER", INT2NUM(335));
  rb_define_const(rb_mKeyboard, "KP_EQUAL", INT2NUM(336));

  // Android key buttons
  rb_define_const(rb_mKeyboard, "BACK", INT2NUM(4));
  rb_define_const(rb_mKeyboard, "MENU", INT2NUM(5));
  rb_define_const(rb_mKeyboard, "VOLUME_UP", INT2NUM(24));
  rb_define_const(rb_mKeyboard, "VOLUME_DOWN", INT2NUM(25));
}
