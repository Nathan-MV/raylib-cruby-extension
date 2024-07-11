#include "texture.hpp"

VALUE rb_cTexture;

RB_TEXTURE_GETTER_INT(rb_texture_width, width)
RB_TEXTURE_GETTER_INT(rb_texture_height, height)
RB_TEXTURE_GETTER_INT(rb_texture_mipmaps, mipmaps)
RB_TEXTURE_GETTER_INT(rb_texture_format, format)

static VALUE rb_texture_initialize(VALUE self, VALUE fileName) {
  Texture *texture = get_texture(self);
  const char *name = StringValueCStr(fileName);

  *texture = LoadTexture(name);

  return self;
}

static VALUE rb_unload_texture(VALUE self) {
  Texture *texture = get_texture(self);

  UnloadTexture(*texture);
  delete texture;

  return Qnil;
}

static VALUE rb_draw_texture_ex(int argc, VALUE *argv, VALUE self) {
    VALUE position, rotation, tint;

    rb_scan_args(argc, argv, "12", &position, &rotation, &tint);

    Texture* tex = get_texture(self);
    Vector2* pos = get_vec2(position);
    float rot = NIL_P(rotation) ? 0 : NUM2DBL(rotation);
    float scl = 1.0f;
    Color col = !NIL_P(tint) ? *get_color(tint) : (Color){ 255, 255, 255, 255 };

    DrawTextureEx(*tex, *pos, rot, scl, col);

    return Qnil;
}

static VALUE rb_draw_texture_pro(int argc, VALUE *argv, VALUE self) {
    VALUE source, dest, origin, rotation, tint;

    rb_scan_args(argc, argv, "14", &source, &dest, &origin, &rotation, &tint);

    Texture* tex = get_texture(self);
    Rectangle src = *get_rect(source);
    Rectangle dst = !NIL_P(dest) ? *get_rect(dest) : (Rectangle){ src.x, src.y, fabsf(src.width), fabsf(src.height) };
    Vector2 orig = !NIL_P(origin) ? *get_vec2(origin) : (Vector2){ 0.0f, 0.0f };
    float rot = NIL_P(rotation) ? 0 : NUM2DBL(rotation);
    Color col = !NIL_P(tint) ? *get_color(tint) : (Color){ 255, 255, 255, 255 };

    DrawTexturePro(*tex, src, dst, orig, rot, col);

    return Qnil;
}

static VALUE rb_set_texture_scale(VALUE self, VALUE value) {
  Texture *texture = get_texture(self);
  int val = NUM2INT(value);

  texture->width *= val;
  texture->height *= val;

  return self;
}

extern "C" void initializeTexture() {
  rb_cTexture = rb_define_class("Texture", rb_cObject);
  rb_define_alloc_func(rb_cTexture, rb_texture_alloc<Texture>);

  rb_define_method(rb_cTexture, "initialize", rb_texture_initialize, 1);
  rb_define_method(rb_cTexture, "width", rb_texture_width, 0);
  rb_define_method(rb_cTexture, "height", rb_texture_height, 0);
  rb_define_method(rb_cTexture, "mipmaps", rb_texture_mipmaps, 0);
  rb_define_method(rb_cTexture, "format", rb_texture_format, 0);

  rb_define_method(rb_cTexture, "scale=", rb_set_texture_scale, 1);

  rb_define_method(rb_cTexture, "unload", rb_unload_texture, 0);
  rb_define_method(rb_cTexture, "draw", rb_draw_texture_ex, -1);
  rb_define_method(rb_cTexture, "draw_pro", rb_draw_texture_pro, -1);
}
