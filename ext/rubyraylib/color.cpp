#include "color.hpp"

VALUE rb_cColor;

RB_COLOR_GETTER(rb_color_get_red, r)
RB_COLOR_GETTER(rb_color_get_green, g)
RB_COLOR_GETTER(rb_color_get_blue, b)
RB_COLOR_GETTER(rb_color_get_alpha, a)
RB_COLOR_SETTER(rb_color_set_red, r)
RB_COLOR_SETTER(rb_color_set_green, g)
RB_COLOR_SETTER(rb_color_set_blue, b)

// Color/pixel related functions
// RLAPI bool ColorIsEqual(Color col1, Color col2);                            // Check if two colors are equal
// RLAPI Color Fade(Color color, float alpha);                                 // Get color with alpha applied, alpha goes from 0.0f to 1.0f
static VALUE rb_color_fade(VALUE self, VALUE alpha_val) {
  Color *color = get_color(self);
  float alpha = NUM2DBL(alpha_val);

  *color = Fade(*color, alpha);

  return self;
}
// RLAPI int ColorToInt(Color color);                                          // Get hexadecimal value for a Color (0xRRGGBBAA)
static VALUE rb_color_to_int(VALUE self) {
  Color *color = get_color(self);

  int result = ColorToInt(*color);

  return INT2NUM(result);
}
// RLAPI Color ColorFromNormalized(Vector4 normalized);                        // Get Color from normalized values [0..1]
static VALUE rb_color_normalize(VALUE self) {
  Color *color = get_color(self);

  Vector4 result = ColorNormalize(*color);

  return Data_Wrap_Struct(rb_cVec4, NULL, NULL, &result);
}
// RLAPI Color ColorFromHSV(float hue, float saturation, float value);         // Get a Color from HSV values, hue [0..360], saturation/value [0..1]
static VALUE rb_color_to_hsv(VALUE self) {
  Color *color = get_color(self);

  Vector3 result = ColorToHSV(*color);

  return Data_Wrap_Struct(rb_cVec3, NULL, NULL, &result);
}
// RLAPI Color ColorTint(Color color, Color tint);                             // Get color multiplied with another color
static VALUE rb_color_tint(VALUE self, VALUE tint_val) {
  Color *color = get_color(self);
  Color *tint = get_color(tint_val);

  *color = ColorTint(*color, *tint);

  return self;
}
// RLAPI Color ColorBrightness(Color color, float factor);                     // Get color with brightness correction, brightness factor goes from -1.0f to 1.0f
static VALUE rb_color_brightness(VALUE self, VALUE factor_val) {
  Color *color = get_color(self);
  float factor = NUM2DBL(factor_val);

  *color = ColorBrightness(*color, factor);

  return self;
}
// RLAPI Color ColorContrast(Color color, float contrast);                     // Get color with contrast correction, contrast values between -1.0f and 1.0f
static VALUE rb_color_contrast(VALUE self, VALUE contrast_val) {
  Color *color = get_color(self);
  float contrast = NUM2DBL(contrast_val);

  *color = ColorContrast(*color, contrast);

  return self;
}
// Get color with alpha applied, alpha goes from 0.0f to 1.0f
static VALUE rb_color_set_alpha(VALUE self, VALUE alpha_val) {
  Color *color = get_color(self);
  float alpha_float = NUM2INT(alpha_val) / 255.0f;

  alpha_float = std::round(alpha_float * 10.0f) / 10.0f;

  // Convert alpha_float to string with one decimal place
  std::stringstream ss;
  ss << std::fixed << std::setprecision(1) << alpha_float;
  std::string alpha_str = ss.str();

  // Convert alpha_str back to float
  alpha_float = std::stof(alpha_str);

  *color = ColorAlpha(*color, alpha_float);

  return self;
}
// RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Get src alpha-blended into dst color with tint
static VALUE rb_color_alpha_blend(VALUE self, VALUE src_val, VALUE tint_val) {
  Color *color = get_color(self);
  Color *src = get_color(src_val);
  Color *tint = get_color(tint_val);

  *color = ColorAlphaBlend(*color, *src, *tint);

  return self;
}
// Get Color structure from hexadecimal value
static VALUE rb_color_initialize(int argc, VALUE *argv, VALUE self) {
  Color *color = get_color(self);

  if (argc == 1) {
    // Single argument (hex value)
    unsigned int hex = NUM2UINT(argv[0]);
    *color = GetColor(hex);
  } else {
    // Four arguments (r, g, b, a)
    VALUE r, g, b, a;
    rb_scan_args(argc, argv, "31", &r, &g, &b, &a);

    // Set default value of a to 255 if not provided
    a = NIL_P(a) ? INT2NUM(255) : a;

    color->r = NUM2INT(r);
    color->g = NUM2INT(g);
    color->b = NUM2INT(b);
    color->a = NUM2INT(a);
  }

  return self;
}
// RLAPI Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a source pixel pointer of certain format
// RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color formatted into destination pixel pointer
// RLAPI int GetPixelDataSize(int width, int height, int format);              // Get pixel data size in bytes for certain format

extern "C" void initializeColor() {
  rb_cColor = rb_define_class("Color", rb_cObject);
  rb_define_alloc_func(rb_cColor, rb_object_alloc<Color>);

  rb_define_method(rb_cColor, "initialize", rb_color_initialize, -1);
  rb_define_method(rb_cColor, "red", rb_color_get_red, 0);
  rb_define_method(rb_cColor, "green", rb_color_get_green, 0);
  rb_define_method(rb_cColor, "blue", rb_color_get_blue, 0);
  rb_define_method(rb_cColor, "alpha", rb_color_get_alpha, 0);
  rb_define_method(rb_cColor, "red=", rb_color_set_red, 1);
  rb_define_method(rb_cColor, "green=", rb_color_set_green, 1);
  rb_define_method(rb_cColor, "blue=", rb_color_set_blue, 1);
  rb_define_method(rb_cColor, "alpha=", rb_color_set_alpha, 1);

  rb_define_method(rb_cColor, "fade", rb_color_fade, 1);
  rb_define_method(rb_cColor, "to_int", rb_color_to_int, 0);
  rb_define_method(rb_cColor, "normalize", rb_color_normalize, 0);
  rb_define_method(rb_cColor, "to_hsv", rb_color_to_hsv, 0);
  rb_define_method(rb_cColor, "tint", rb_color_tint, 1);
  rb_define_method(rb_cColor, "brightness", rb_color_brightness, 1);
  rb_define_method(rb_cColor, "contrast", rb_color_contrast, 1);
  rb_define_method(rb_cColor, "alpha_blend", rb_color_alpha_blend, 2);

  static Color lightgray = LIGHTGRAY;
  static Color gray = GRAY;
  static Color darkgray = DARKGRAY;
  static Color yellow = YELLOW;
  static Color gold = GOLD;
  static Color orange = ORANGE;
  static Color pink = PINK;
  static Color red = RED;
  static Color maroon = MAROON;
  static Color green = GREEN;
  static Color lime = LIME;
  static Color darkgreen = DARKGREEN;
  static Color skyblue = SKYBLUE;
  static Color blue = BLUE;
  static Color darkblue = DARKBLUE;
  static Color purple = PURPLE;
  static Color violet = VIOLET;
  static Color darkpurple = DARKPURPLE;
  static Color beige = BEIGE;
  static Color brown = BROWN;
  static Color darkbrown = DARKBROWN;
  static Color white = WHITE;
  static Color black = BLACK;
  static Color blank = BLANK;
  static Color magenta = MAGENTA;
  static Color raywhite = RAYWHITE;

  rb_define_const(rb_cColor, "LIGHTGRAY", Data_Wrap_Struct(rb_cColor, NULL, NULL, &lightgray));
  rb_define_const(rb_cColor, "GRAY", Data_Wrap_Struct(rb_cColor, NULL, NULL, &gray));
  rb_define_const(rb_cColor, "DARKGRAY", Data_Wrap_Struct(rb_cColor, NULL, NULL, &darkgray));
  rb_define_const(rb_cColor, "YELLOW", Data_Wrap_Struct(rb_cColor, NULL, NULL, &yellow));
  rb_define_const(rb_cColor, "GOLD", Data_Wrap_Struct(rb_cColor, NULL, NULL, &gold));
  rb_define_const(rb_cColor, "ORANGE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &orange));
  rb_define_const(rb_cColor, "PINK", Data_Wrap_Struct(rb_cColor, NULL, NULL, &pink));
  rb_define_const(rb_cColor, "RED", Data_Wrap_Struct(rb_cColor, NULL, NULL, &red));
  rb_define_const(rb_cColor, "MAROON", Data_Wrap_Struct(rb_cColor, NULL, NULL, &maroon));
  rb_define_const(rb_cColor, "GREEN", Data_Wrap_Struct(rb_cColor, NULL, NULL, &green));
  rb_define_const(rb_cColor, "LIME", Data_Wrap_Struct(rb_cColor, NULL, NULL, &lime));
  rb_define_const(rb_cColor, "DARKGREEN", Data_Wrap_Struct(rb_cColor, NULL, NULL, &darkgreen));
  rb_define_const(rb_cColor, "SKYBLUE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &skyblue));
  rb_define_const(rb_cColor, "BLUE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &blue));
  rb_define_const(rb_cColor, "DARKBLUE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &darkblue));
  rb_define_const(rb_cColor, "PURPLE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &purple));
  rb_define_const(rb_cColor, "VIOLET", Data_Wrap_Struct(rb_cColor, NULL, NULL, &violet));
  rb_define_const(rb_cColor, "DARKPURPLE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &darkpurple));
  rb_define_const(rb_cColor, "BEIGE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &beige));
  rb_define_const(rb_cColor, "BROWN", Data_Wrap_Struct(rb_cColor, NULL, NULL, &brown));
  rb_define_const(rb_cColor, "DARKBROWN", Data_Wrap_Struct(rb_cColor, NULL, NULL, &darkbrown));
  rb_define_const(rb_cColor, "WHITE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &white));
  rb_define_const(rb_cColor, "BLACK", Data_Wrap_Struct(rb_cColor, NULL, NULL, &black));
  rb_define_const(rb_cColor, "BLANK", Data_Wrap_Struct(rb_cColor, NULL, NULL, &blank));
  rb_define_const(rb_cColor, "MAGENTA", Data_Wrap_Struct(rb_cColor, NULL, NULL, &magenta));
  rb_define_const(rb_cColor, "RAYWHITE", Data_Wrap_Struct(rb_cColor, NULL, NULL, &raywhite));
}
