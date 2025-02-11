#include <color_bindings.h>
#include "ruby/internal/core/rdata.h"

VALUE rb_cColor;

// Get Color structure from hexadecimal value
static auto rb_color_initialize(int argc, VALUE *argv, VALUE self) {
  auto *color = get_color(self);

  // Default to black (0, 0, 0, 255)
  if (argc == 0) {
    *color = (Color){0, 0, 0, 255};
  } else if (argc == 1) {
    // Handle hex string or number
    if (rb_obj_is_kind_of(argv[0], rb_cString) || rb_obj_is_kind_of(argv[0], rb_cNumeric)) {
      const char *hex_str = StringValueCStr(argv[0]);
      *color = ColorFromHex(hex_str);
    } else if (rb_obj_is_kind_of(argv[0], rb_cColor)) {
      // Handle specified Color object
      *color = *get_color(argv[0]);
    } else {
      rb_raise(rb_eTypeError, "Expected a hex string, number, or Color object.");
    }
  } else {
    // Handle specified r, g, b, (optional a)
    VALUE r, g, b, a;
    rb_scan_args(argc, argv, "31", &r, &g, &b, &a);

    color->r = NUM2INT(r);
    color->g = NUM2INT(g);
    color->b = NUM2INT(b);
    color->a = NIL_P(a) ? 255 : NUM2INT(a);  // Default alpha to 255
  }

  return self;
}

RB_COLOR_GETTER(rb_color_get_red, r)
RB_COLOR_GETTER(rb_color_get_green, g)
RB_COLOR_GETTER(rb_color_get_blue, b)
RB_COLOR_GETTER(rb_color_get_alpha, a)
RB_COLOR_SETTER(rb_color_set_red, r)
RB_COLOR_SETTER(rb_color_set_green, g)
RB_COLOR_SETTER(rb_color_set_blue, b)

// Color/pixel related functions
// RLAPI bool ColorIsEqual(Color col1, Color col2);                            // Check if two
// colors are equal
static auto rb_color_is_equal(VALUE self, VALUE other) {
  auto *color1 = get_color(self);
  auto *color2 = get_color(other);

  auto result = ColorIsEqual(*color1, *color2);

  return result ? Qtrue : Qfalse;
}
// RLAPI Color Fade(Color color, float alpha);                                 // Get color with
// alpha applied, alpha goes from 0.0f to 1.0f
static auto rb_color_fade(VALUE self, VALUE alpha) {
  auto *color = get_color(self);
  auto alpha_val = NUM2DBL(alpha);

  *color = Fade(*color, alpha_val);

  return self;
}
// RLAPI int ColorToInt(Color color);                                          // Get hexadecimal
// value for a Color (0xRRGGBBAA)
static auto rb_color_to_int(VALUE self) {
  auto *color = get_color(self);

  auto result = ColorToInt(*color);

  return INT2NUM(result);
}
// RLAPI Color ColorFromNormalized(Vector4 normalized);                        // Get Color from
// normalized values [0..1]
static auto rb_color_normalize(VALUE self) {
  auto *color = get_color(self);

  Vector4 result = ColorNormalize(*color);

  return Data_Wrap_Struct(rb_cVec4, NULL, rb_object_free<Vector4>, &result);
}
// RLAPI Vector3 ColorToHSV(Color color);                                      // Get HSV values for
// a Color, hue [0..360], saturation/value [0..1]
static auto rb_color_to_hsv(VALUE self) {
  auto *color = get_color(self);

  Vector3 result = ColorToHSV(*color);

  return Data_Wrap_Struct(rb_cVec3, NULL, rb_object_free<Vector3>, &result);
}
// RLAPI Color ColorTint(Color color, Color tint);                             // Get color
// multiplied with another color
static auto rb_color_tint(VALUE self, VALUE tint_val) {
  auto *color = get_color(self);
  auto *tint = get_color(tint_val);

  *color = ColorTint(*color, *tint);

  return self;
}
// RLAPI Color ColorBrightness(Color color, float factor);                     // Get color with
// brightness correction, brightness factor goes from -1.0f to 1.0f
static auto rb_color_brightness(VALUE self, VALUE factor_val) {
  auto *color = get_color(self);
  auto factor = NUM2DBL(factor_val);

  *color = ColorBrightness(*color, factor);

  return self;
}
// RLAPI Color ColorContrast(Color color, float contrast);                     // Get color with
// contrast correction, contrast values between -1.0f and 1.0f
static auto rb_color_contrast(VALUE self, VALUE contrast_val) {
  auto *color = get_color(self);
  auto contrast = NUM2DBL(contrast_val);

  *color = ColorContrast(*color, contrast);

  return self;
}
// Get color with alpha applied, alpha goes from 0.0f to 1.0f
static auto rb_color_set_alpha(VALUE self, VALUE alpha_val) {
  auto *color = get_color(self);
  auto alpha_float = NUM2INT(alpha_val) / 255.0f;

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
// RLAPI Color ColorAlphaBlend(Color dst, Color src, Color tint);              // Get src
// alpha-blended into dst color with tint
static auto rb_color_alpha_blend(VALUE self, VALUE src_val, VALUE tint_val) {
  auto *color = get_color(self);
  auto *src = get_color(src_val);
  auto *tint = get_color(tint_val);

  *color = ColorAlphaBlend(*color, *src, *tint);

  return self;
}
// RLAPI Color ColorLerp(Color color1, Color color2, float d);                 // Mix 2 Colors
// Together
static auto rb_color_lerp(VALUE self, VALUE rb_color2, VALUE rb_d) {
  auto *color1 = get_color(self);
  auto *color2 = get_color(rb_color2);
  auto d = NUM2DBL(rb_d);

  auto lerped_color = ColorLerp(*color1, *color2, d);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, &lerped_color);
}
// RLAPI Color GetPixelColor(void *srcPtr, int format);                        // Get Color from a
// source pixel pointer of certain format
static auto rb_get_pixel_color(VALUE self, VALUE rb_src_ptr, VALUE rb_format) {
  auto *src_ptr = (void *)(uintptr_t)NUM2ULONG(rb_src_ptr);
  auto format = NUM2INT(rb_format);

  auto color = GetPixelColor(src_ptr, format);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, &color);
}
// RLAPI void SetPixelColor(void *dstPtr, Color color, int format);            // Set color
// formatted into destination pixel pointer
static auto rb_set_pixel_color(VALUE self, VALUE rb_dst_ptr, VALUE rb_color, VALUE rb_format) {
  auto *dst_ptr = (void *)(uintptr_t)NUM2ULONG(rb_dst_ptr);
  auto *color = get_color(rb_color);
  auto format = NUM2INT(rb_format);

  SetPixelColor(dst_ptr, *color, format);

  return Qnil;
}
// RLAPI int GetPixelDataSize(int width, int height, int format);              // Get pixel data
// size in bytes for certain format
static auto rb_get_pixel_data_size(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_format) {
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto format = NUM2INT(rb_format);

  auto size = GetPixelDataSize(width, height, format);

  return INT2NUM(size);
}

extern "C" void Init_Color() {
  rb_cColor = rb_define_class_under(rb_mRL, "Color", rb_cObject);
  rb_define_alloc_func(rb_cColor, rb_object_alloc<Color>);

  // Define initialize and attribute accessors (getters and setters)
  rb_define_method(rb_cColor, "initialize", rb_color_initialize, -1);
  rb_define_method(rb_cColor, "r", rb_color_get_red, 0);
  rb_define_method(rb_cColor, "g", rb_color_get_green, 0);
  rb_define_method(rb_cColor, "b", rb_color_get_blue, 0);
  rb_define_method(rb_cColor, "a", rb_color_get_alpha, 0);
  rb_define_method(rb_cColor, "r=", rb_color_set_red, 1);
  rb_define_method(rb_cColor, "g=", rb_color_set_green, 1);
  rb_define_method(rb_cColor, "b=", rb_color_set_blue, 1);
  rb_define_method(rb_cColor, "a=", rb_color_set_alpha, 1);

  // Define alias methods
  rb_define_alias(rb_cColor, "red", "r");
  rb_define_alias(rb_cColor, "green", "g");
  rb_define_alias(rb_cColor, "blue", "b");
  rb_define_alias(rb_cColor, "alpha", "a");
  rb_define_alias(rb_cColor, "red=", "r=");
  rb_define_alias(rb_cColor, "green=", "g=");
  rb_define_alias(rb_cColor, "blue=", "b=");
  rb_define_alias(rb_cColor, "alpha=", "a=");

  // Define additional methods
  rb_define_method(rb_cColor, "eql?", rb_color_is_equal, 1);
  rb_define_method(rb_cColor, "fade", rb_color_fade, 1);
  rb_define_method(rb_cColor, "to_int", rb_color_to_int, 0);
  rb_define_method(rb_cColor, "normalize", rb_color_normalize, 0);
  rb_define_method(rb_cColor, "to_hsv", rb_color_to_hsv, 0);
  rb_define_method(rb_cColor, "tint", rb_color_tint, 1);
  rb_define_method(rb_cColor, "brightness", rb_color_brightness, 1);
  rb_define_method(rb_cColor, "contrast", rb_color_contrast, 1);
  rb_define_method(rb_cColor, "alpha_blend", rb_color_alpha_blend, 2);
  rb_define_method(rb_cColor, "lerp", rb_color_lerp, 2);
  rb_define_method(rb_cColor, "pixel_color", rb_get_pixel_color, 2);
  rb_define_method(rb_cColor, "set_pixel_color", rb_set_pixel_color, 3);
  rb_define_method(rb_cColor, "pixel_data_size", rb_get_pixel_data_size, 3);
}
