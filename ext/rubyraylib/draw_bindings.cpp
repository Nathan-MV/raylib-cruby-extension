#include <draw_bindings.h>

// Drawing-related functions

// RLAPI void BeginMode3D(Camera3D camera);                          // Begin 3D mode with custom camera (3D)
// RLAPI void EndMode3D(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
// RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
// RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
static auto rb_begin_blend_mode(VALUE self, VALUE rb_mode) {
  auto mode = NUM2INT(rb_mode);

  rb_need_block();
  BeginBlendMode(mode);
  rb_yield(Qnil);
  EndBlendMode();

  return Qnil;
}
// RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
// RLAPI void EndScissorMode(void);                                  // End scissor mode
static auto rb_begin_scissor_mode(VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_width,
                                  VALUE rb_height) {
  auto x = NUM2INT(rb_x);
  auto y = NUM2INT(rb_y);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);

  rb_need_block();
  BeginScissorMode(x, y, width, height);
  rb_yield(Qnil);
  EndScissorMode();

  return Qnil;
}

// Color blending modes (pre-defined)
// typedef enum {
//     BLEND_ALPHA = 0,                // Blend textures considering alpha (default)
//     BLEND_ADDITIVE,                 // Blend textures adding colors
//     BLEND_MULTIPLIED,               // Blend textures multiplying colors
//     BLEND_ADD_COLORS,               // Blend textures adding colors (alternative)
//     BLEND_SUBTRACT_COLORS,          // Blend textures subtracting colors (alternative)
//     BLEND_ALPHA_PREMULTIPLY,        // Blend premultiplied textures considering alpha
//     BLEND_CUSTOM,                   // Blend textures using custom src/dst factors (use rlSetBlendFactors())
//     BLEND_CUSTOM_SEPARATE           // Blend textures using custom rgb/alpha separate src/dst factors (use rlSetBlendFactorsSeparate())
// } BlendMode;

// Initializes the Draw module and defines its functions
extern "C" void Init_Draw(void) {
  VALUE rb_mDraw = rb_define_module_under(rb_mRL, "Draw");

  rb_define_module_function(rb_mDraw, "begin_blend_mode", rb_begin_blend_mode, 1);
  rb_define_module_function(rb_mDraw, "begin_scissor_mode",
                            rb_begin_scissor_mode, 4);
}
