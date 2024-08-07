#include "draw.hpp"

// Drawing-related functions

// RLAPI void ClearBackground(Color color);                          // Set background color (framebuffer clear color)
static VALUE rb_clear_background(VALUE self, VALUE color) {
  Color *col = get_color(color);

  ClearBackground(*col);

  return Qnil;
}
// RLAPI void BeginDrawing(void);                                    // Setup canvas (framebuffer) to start drawing
// RLAPI void EndDrawing(void);                                      // End canvas drawing and swap buffers (double buffering)
static VALUE rb_begin_drawing(VALUE self) {
  rb_need_block();
  BeginDrawing();
  rb_yield(Qnil);
  EndDrawing();

  return Qnil;
}
// RLAPI void BeginMode2D(Camera2D camera);                          // Begin 2D mode with custom camera (2D)
// RLAPI void EndMode2D(void);                                       // Ends 2D mode with custom camera
// RLAPI void BeginMode3D(Camera3D camera);                          // Begin 3D mode with custom camera (3D)
// RLAPI void EndMode3D(void);                                       // Ends 3D mode and returns to default 2D orthographic mode
// RLAPI void BeginTextureMode(RenderTexture2D target);              // Begin drawing to render texture
// RLAPI void EndTextureMode(void);                                  // Ends drawing to render texture
// RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
// RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
// RLAPI void BeginBlendMode(int mode);                              // Begin blending mode (alpha, additive, multiplied, subtract, custom)
// RLAPI void EndBlendMode(void);                                    // End blending mode (reset to default: alpha blending)
// RLAPI void BeginScissorMode(int x, int y, int width, int height); // Begin scissor mode (define screen area for following drawing)
// RLAPI void EndScissorMode(void);                                  // End scissor mode

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
extern "C" void initializeDraw(void) {
  VALUE rb_cDraw = rb_define_module_under(rb_mRL, "Draw");

  rb_define_module_function(rb_cDraw, "begin", rb_begin_drawing, 0);
  rb_define_module_function(rb_cDraw, "clear", rb_clear_background, 1);
}
