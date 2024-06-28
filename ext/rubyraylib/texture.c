#include "texture.h"

VALUE rb_cTexture;

static void rb_texture_free(void *ptr) {
  if (ptr) {
    Texture *texture = (Texture *)ptr;
    free(texture);
  }
}

static VALUE rb_texture_alloc(VALUE klass) {
  Texture *texture = ALLOC(Texture);

  if (!texture) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Texture.");
  }

  return Data_Wrap_Struct(klass, NULL, rb_texture_free, texture);
}

Texture* get_texture(VALUE obj) {
  Texture *texture;
  Data_Get_Struct(obj, Texture, texture);

  return texture;
}

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

static VALUE rb_draw_texture(VALUE self, VALUE posX, VALUE posY, VALUE tint_val) {
  Texture *texture = get_texture(self);
  int x = NUM2INT(posX);
  int y = NUM2INT(posY);
  Color *tint = get_color(tint_val);

  DrawTexture(*texture, x, y, *tint);

  return Qnil;
}

static VALUE rb_draw_texture_v(VALUE self, VALUE position, VALUE tint_val) {
  Texture *texture = get_texture(self);
  Vector2 *pos = get_vec2(position);
  Color *tint = get_color(tint_val);

  DrawTextureV(*texture, *pos, *tint);

  return Qnil;
}

static VALUE rb_draw_texture_ex(VALUE self, VALUE position, VALUE rotation, VALUE scale_val, VALUE tint_val) {
  Texture *texture = get_texture(self);
  Vector2 *pos = get_vec2(position);
  float rot = NUM2DBL(rotation);
  float scale = NUM2DBL(scale_val);
  Color *tint = get_color(tint_val);

  DrawTextureEx(*texture, *pos, rot, scale, *tint);

  return Qnil;
}

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
  rb_define_method(rb_cTexture, "unload", rb_unload_texture, 0);
  rb_define_method(rb_cTexture, "draw", rb_draw, -1);
}
