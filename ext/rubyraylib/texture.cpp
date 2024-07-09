#include "texture.hpp"

VALUE rb_cTexture;

static void rb_texture_free(void *ptr) {
  Texture* texture = static_cast<Texture*>(ptr);
  //UnloadTexture(*texture);
  delete texture;
}

static VALUE rb_texture_alloc(VALUE klass) {
  Texture* texture = nullptr;
  try {
    texture = new Texture();
  } catch (const std::bad_alloc&) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Texture.");
    return Qnil;
  }

  return Data_Wrap_Struct(klass, NULL, rb_texture_free, texture);
}

RB_TEXTURE_GETTER(rb_texture_width, width)
RB_TEXTURE_GETTER(rb_texture_height, height)
RB_TEXTURE_GETTER(rb_texture_mipmaps, mipmaps)
RB_TEXTURE_GETTER(rb_texture_format, format)

static VALUE rb_texture_initialize(VALUE self, VALUE fileName) {
  Texture *texture = get_texture(self);
  const char *name = StringValueCStr(fileName);

  *texture = LoadTexture(name);

  return self;
}

static VALUE rb_unload_texture(VALUE self) {
  Texture *texture = get_texture(self);

  if (texture != NULL) {
    UnloadTexture(*texture);
    free(texture);
  }

  return Qnil;
}

RB_DRAW_TEXTURE(rb_draw_texture, DrawTexture(*texture, NUM2INT(x), NUM2INT(y), *get_color(col)),
																 VALUE x, VALUE y, VALUE col)
RB_DRAW_TEXTURE(rb_draw_texture_v, DrawTextureV(*texture, *get_vec2(pos), *get_color(col)),
																 VALUE pos, VALUE col)
RB_DRAW_TEXTURE(rb_draw_texture_ex, DrawTextureEx(*texture, *get_vec2(pos), NUM2DBL(rot), NUM2DBL(scale), *get_color(col)),
																 VALUE pos, VALUE rot, VALUE scale, VALUE col)

static VALUE rb_draw(int argc, VALUE *argv, VALUE self) {
  VALUE x, y, tint, pos, rot, scale;

  switch (argc) {
  case 2:
    rb_scan_args(argc, argv, "2", &pos, &tint);
    return rb_draw_texture_v(self, pos, tint);
  case 3:
    rb_scan_args(argc, argv, "3", &x, &y, &tint);
    return rb_draw_texture(self, x, y, tint);
  case 4:
    rb_scan_args(argc, argv, "4", &pos, &rot, &scale, &tint);
    return rb_draw_texture_ex(self, pos, rot, scale, tint);
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments, expected 2, 3, or 4.");
    return Qnil;
  }
}

void initializeTexture() {
  rb_cTexture = rb_define_class("Texture", rb_cObject);

  rb_define_alloc_func(rb_cTexture, rb_texture_alloc);
  rb_define_method(rb_cTexture, "initialize", rb_texture_initialize, 1);
  rb_define_method(rb_cTexture, "width", rb_texture_width, 0);
  rb_define_method(rb_cTexture, "height", rb_texture_height, 0);
  rb_define_method(rb_cTexture, "mipmaps", rb_texture_mipmaps, 0);
  rb_define_method(rb_cTexture, "format", rb_texture_format, 0);

  rb_define_method(rb_cTexture, "unload", rb_unload_texture, 0);
  rb_define_method(rb_cTexture, "draw", rb_draw, -1);
}
