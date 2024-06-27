#include "color.h"

VALUE rb_cColor;

static void rb_color_free(void *ptr)
{
  Color *color = (Color *)ptr;

  if (color != NULL)
  {
    free(color);
  }
}

static VALUE rb_color_alloc(VALUE klass)
{
  Color *color = ALLOC(Color);

  if (color != NULL)
  {
    return Data_Wrap_Struct(klass, NULL, rb_color_free, color);
  }
  else
  {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Color.");
  }
}

static VALUE rb_color_initialize(int argc, VALUE *argv, VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  if (argc == 1)
  {
    // Single argument (hex value)
    unsigned int hex = NUM2UINT(argv[0]);
    *color = GetColor(hex);
  }
  else
  {
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

static VALUE rb_color_get_red(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  return INT2NUM(color->r);
}

static VALUE rb_color_get_green(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  return INT2NUM(color->g);
}

static VALUE rb_color_get_blue(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  return INT2NUM(color->b);
}

static VALUE rb_color_get_alpha(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  return INT2NUM(color->a);
}

static VALUE rb_color_set_red(VALUE self, VALUE value)
{
  Color *color = (Color *)DATA_PTR(self);

  color->r = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_green(VALUE self, VALUE value)
{
  Color *color = (Color *)DATA_PTR(self);

  color->g = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_blue(VALUE self, VALUE value)
{
  Color *color = (Color *)DATA_PTR(self);

  color->b = NUM2INT(value);

  return self;
}

static VALUE rb_color_set_alpha(VALUE self, VALUE alpha)
{
  Color *color = (Color *)DATA_PTR(self);
  // int alpha_value = NUM2INT(alpha);
  float alpha_value = NUM2DBL(alpha);

  // Convert alpha from 0-255 to 0.0-1.0
  // float alpha_float = roundf((float)alpha_value / 255.0f * 10.0f) / 10.0f;
  // rb_warn("Setting alpha to %f", alpha_float);

  *color = ColorAlpha(*color, alpha_value);

  return self;
}

static VALUE rb_color_fade(VALUE self, VALUE alpha)
{
  Color *color = (Color *)DATA_PTR(self);
  float alpha_value = NUM2DBL(alpha);

  *color = Fade(*color, alpha_value);

  return self;
}

static VALUE rb_color_to_int(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  int result = ColorToInt(*color);

  return INT2NUM(result);
}

static VALUE rb_color_normalize(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  Vector4 result = ColorNormalize(*color);
  VALUE rb_result = Data_Wrap_Struct(rb_cVec4, NULL, NULL, &result);

  return rb_result;
}

static VALUE rb_color_to_hsv(VALUE self)
{
  Color *color = (Color *)DATA_PTR(self);

  Vector3 result = ColorToHSV(*color);
  VALUE rb_result = Data_Wrap_Struct(rb_cVec3, NULL, NULL, &result);

  return rb_result;
}

static VALUE rb_color_tint(VALUE self, VALUE tint)
{
  Color *color = (Color *)DATA_PTR(self);
  Color *tint_value = (Color *)DATA_PTR(tint);

  *color = ColorTint(*color, *tint_value);

  return self;
}

static VALUE rb_color_brightness(VALUE self, VALUE factor)
{
  Color *color = (Color *)DATA_PTR(self);
  float brightness_factor = NUM2DBL(factor);

  *color = ColorBrightness(*color, brightness_factor);

  return self;
}

static VALUE rb_color_contrast(VALUE self, VALUE contrast)
{
  Color *color = (Color *)DATA_PTR(self);
  float contrast_value = NUM2DBL(contrast);

  *color = ColorContrast(*color, contrast_value);

  return self;
}

static VALUE rb_color_alpha_blend(VALUE self, VALUE src, VALUE tint)
{
  Color *color = (Color *)DATA_PTR(self);
  Color *src_value = (Color *)DATA_PTR(src);
  Color *tint_value = (Color *)DATA_PTR(tint);

  *color = ColorAlphaBlend(*color, *src_value, *tint_value);

  return self;
}

void initializeColor()
{
  rb_cColor = rb_define_class("Color", rb_cObject);

  rb_define_alloc_func(rb_cColor, rb_color_alloc);
  rb_define_method(rb_cColor, "initialize", rb_color_initialize, -1);
  rb_define_method(rb_cColor, "red", rb_color_get_red, 0);
  rb_define_method(rb_cColor, "green", rb_color_get_green, 0);
  rb_define_method(rb_cColor, "blue", rb_color_get_blue, 0);
  rb_define_method(rb_cColor, "alpha", rb_color_get_alpha, 0);
  rb_define_method(rb_cColor, "red=", rb_color_set_red, 1);
  rb_define_method(rb_cColor, "green=", rb_color_set_green, 1);
  rb_define_method(rb_cColor, "blue=", rb_color_set_blue, 1);
  rb_define_method(rb_cColor, "set_alpha", rb_color_set_alpha, 1);

  rb_define_method(rb_cColor, "fade", rb_color_fade, 1);
  rb_define_method(rb_cColor, "to_int", rb_color_to_int, 0);
  rb_define_method(rb_cColor, "normalize", rb_color_normalize, 0);
  rb_define_method(rb_cColor, "to_hsv", rb_color_to_hsv, 0);
  rb_define_method(rb_cColor, "tint", rb_color_tint, 1);
  rb_define_method(rb_cColor, "brightness", rb_color_brightness, 1);
  rb_define_method(rb_cColor, "contrast", rb_color_contrast, 1);
  rb_define_method(rb_cColor, "alpha_blend", rb_color_alpha_blend, 2);
}
