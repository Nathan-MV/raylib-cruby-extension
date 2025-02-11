#include <font_bindings.h>
#include "ruby/internal/core/rstring.h"

//------------------------------------------------------------------------------------
// Font Loading and Text Drawing Functions (Module: text)
//------------------------------------------------------------------------------------

// Font loading/unloading functions
// RLAPI Font GetFontDefault(void);                                                            // Get the default Font
// RLAPI Font LoadFont(const char *fileName);                                                  // Load font from file into GPU memory (VRAM)
static auto rb_initialize_text(VALUE self, VALUE rb_filename) {
  const auto *filename = StringValueCStr(rb_filename);

  Font font = LoadFont(filename);

  return self;
}
// RLAPI Font LoadFontEx(const char *fileName, int fontSize, int *codepoints, int codepointCount); // Load font from file with extended parameters, use NULL for codepoints and 0 for codepointCount to load the default character set
// RLAPI Font LoadFontFromImage(Image image, Color key, int firstChar);                        // Load font from Image (XNA style)
// RLAPI Font LoadFontFromMemory(const char *fileType, const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount); // Load font from memory buffer, fileType refers to extension: i.e. '.ttf'
// RLAPI bool IsFontValid(Font font);                                                          // Check if a font is ready
// RLAPI GlyphInfo *LoadFontData(const unsigned char *fileData, int dataSize, int fontSize, int *codepoints, int codepointCount, int type); // Load font data for further use
// RLAPI Image GenImageFontAtlas(const GlyphInfo *glyphs, RayRectangle **glyphRecs, int glyphCount, int fontSize, int padding, int packMethod); // Generate image font atlas using chars info
// RLAPI void UnloadFontData(GlyphInfo *glyphs, int glyphCount);                               // Unload font chars info data (RAM)
// RLAPI void UnloadFont(Font font);                                                           // Unload font from GPU memory (VRAM)
// RLAPI bool ExportFontAsCode(Font font, const char *fileName);                               // Export font as code file, returns true on success

// Text drawing functions
// RLAPI void RayDrawText(const char *text, int posX, int posY, int fontSize, Color color);       // Draw text (using default font)
static auto rb_draw_text(VALUE self, VALUE rb_text, VALUE rb_pos_x, VALUE rb_pos_y,
                         VALUE rb_font_size, VALUE rb_color) {
  const auto *text = StringValueCStr(rb_text);
  auto posX = NUM2INT(rb_pos_x);
  auto posY = NUM2INT(rb_pos_y);
  auto fontSize = NUM2INT(rb_font_size);
  auto *color = get_color(rb_color);

  RayDrawText(text, posX, posY, fontSize, *color);

  return self;
}
// RLAPI void RayDrawTextEx(Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text using font and additional parameters
static auto rb_draw_text_ex(VALUE self, VALUE rb_text, VALUE rb_pos, VALUE rb_font_size,
                            VALUE rb_spacing, VALUE rb_color) {
  auto *font = get_font(self);
  const auto *text = StringValueCStr(rb_text);
  auto *position = get_vec2(rb_pos);
  auto fontSize = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);
  auto *tint = get_color(rb_color);

  RayDrawTextEx(*font, text, *position, fontSize, spacing, *tint);

  return self;
}
// RLAPI void DrawTextPro(Font font, const char *text, Vector2 position, Vector2 origin, float rotation, float fontSize, float spacing, Color tint); // Draw text using Font and pro parameters (rotation)
static auto rb_draw_text_pro(VALUE self, VALUE rb_text, VALUE rb_position, VALUE rb_origin,
                             VALUE rb_rotation, VALUE rb_font_size, VALUE rb_spacing,
                             VALUE rb_tint) {
  auto *font = get_font(self);
  const auto *text = StringValueCStr(rb_text);
  auto *position = get_vec2(rb_position);
  auto *origin = get_vec2(rb_origin);
  auto rotation = NUM2DBL(rb_rotation);
  auto fontSize = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);
  auto *tint = get_color(rb_tint);

  DrawTextPro(*font, text, *position, *origin, rotation, fontSize, spacing, *tint);

  return self;
}
// RLAPI void DrawTextCodepoint(Font font, int codepoint, Vector2 position, float fontSize, Color tint); // Draw one character (codepoint)
static auto rb_draw_text_codepoint(VALUE self, VALUE rb_codepoint, VALUE rb_position,
                                   VALUE rb_font_size, VALUE rb_tint) {
  auto *font = get_font(self);
  auto codepoint = NUM2INT(rb_codepoint);
  auto *position = get_vec2(rb_position);
  auto fontSize = NUM2DBL(rb_font_size);
  auto *tint = get_color(rb_tint);

  DrawTextCodepoint(*font, codepoint, *position, fontSize, *tint);

  return self;
}
// RLAPI void DrawTextCodepoints(Font font, const int *codepoints, int codepointCount, Vector2 position, float fontSize, float spacing, Color tint); // Draw multiple character (codepoint)
static auto rb_draw_text_codepoints(VALUE self, VALUE rb_codepoints, VALUE rb_codepoint_count,
                                    VALUE rb_position, VALUE rb_font_size, VALUE rb_spacing,
                                    VALUE rb_tint) {
  auto *font = get_font(self);
  auto codepoints = NUM2INT(rb_codepoints);
  auto codepointCount = NUM2INT(rb_codepoint_count);
  auto *position = get_vec2(rb_position);
  auto fontSize = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);
  auto *tint = get_color(rb_tint);

  DrawTextCodepoints(*font, &codepoints, codepointCount, *position, fontSize, spacing, *tint);

  return self;
}

// Text font info functions
// RLAPI void SetTextLineSpacing(int spacing);                                                 // Set vertical line spacing when drawing with line-breaks
// RLAPI int MeasureText(const char *text, int fontSize);                                      // Measure string width for default font
static auto rb_measure_text(VALUE self, VALUE rb_text, VALUE rb_font_size) {
  const auto *text = StringValueCStr(rb_text);
  auto fontSize = NUM2INT(rb_font_size);

  auto result = MeasureText(text, fontSize);

  return INT2NUM(result);
}
// RLAPI Vector2 MeasureTextEx(Font font, const char *text, float fontSize, float spacing);    // Measure string size for Font
static auto rb_measure_text_ex(VALUE self, VALUE rb_text, VALUE rb_font_size, VALUE rb_spacing) {
  auto *font = get_font(self);
  const auto *text = StringValueCStr(rb_text);
  auto fontSize = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);

  Vector2 result = MeasureTextEx(*font, text, fontSize, spacing);

  return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, &result);
}
// RLAPI int GetGlyphIndex(Font font, int codepoint);                                          // Get glyph index position in font for a codepoint (unicode character), fallback to '?' if not found
// RLAPI GlyphInfo GetGlyphInfo(Font font, int codepoint);                                     // Get glyph font info data for a codepoint (unicode character), fallback to '?' if not found
// RLAPI RayRectangle GetGlyphAtlasRec(Font font, int codepoint);                                 // Get glyph rectangle in font atlas for a codepoint (unicode character), fallback to '?' if not found

// Text codepoints management functions (unicode characters)
// RLAPI char *LoadUTF8(const int *codepoints, int length);                // Load UTF-8 text encoded from codepoints array
// RLAPI void UnloadUTF8(char *text);                                      // Unload UTF-8 text encoded from codepoints array
// RLAPI int *LoadCodepoints(const char *text, int *count);                // Load all codepoints from a UTF-8 text string, codepoints count returned by parameter
// RLAPI void UnloadCodepoints(int *codepoints);                           // Unload codepoints data from memory
// RLAPI int GetCodepointCount(const char *text);                          // Get total number of codepoints in a UTF-8 encoded string
// RLAPI int GetCodepoint(const char *text, int *codepointSize);           // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointNext(const char *text, int *codepointSize);       // Get next codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI int GetCodepointPrevious(const char *text, int *codepointSize);   // Get previous codepoint in a UTF-8 encoded string, 0x3f('?') is returned on failure
// RLAPI const char *CodepointToUTF8(int codepoint, int *utf8Size);        // Encode one codepoint into UTF-8 byte array (array length returned as parameter)

// Font type, defines generation method
// typedef enum {
//     FONT_DEFAULT = 0,               // Default font generation, anti-aliased
//     FONT_BITMAP,                    // Bitmap font generation, no anti-aliasing
//     FONT_SDF                        // SDF font generation, requires external shader
// } FontType;

extern "C" void Init_Font(void) {
  VALUE rb_cFont = rb_define_class_under(rb_mRL, "Font", rb_cObject);
  rb_define_alloc_func(rb_cFont, rb_font_alloc<Font>);

  rb_define_method(rb_cFont, "initialize", rb_initialize_text, 1);
  rb_define_method(rb_cFont, "draw", rb_draw_text, 5);
  rb_define_method(rb_cFont, "draw_ex", rb_draw_text_ex, 5);
  rb_define_method(rb_cFont, "draw_pro", rb_draw_text_pro, 7);
  rb_define_method(rb_cFont, "draw_codepoint", rb_draw_text_codepoint, 4);
  rb_define_method(rb_cFont, "draw_codepoints", rb_draw_text_codepoints, 6);

  rb_define_method(rb_cFont, "measure", rb_measure_text, 2);
  rb_define_method(rb_cFont, "measure_ex", rb_measure_text_ex, 3);
}
