#include "texture.h"

VALUE rb_cTexture;

static void rb_texture_free(void *ptr) {
  Texture *texture = (Texture *)ptr;

  if (texture) {
    free(texture);
  }
}

static VALUE rb_texture_alloc(VALUE klass) {
  Texture *texture = ALLOC(Texture);

  if (!texture) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for Texture.");
  } else {
    return Data_Wrap_Struct(klass, NULL, rb_texture_free, texture);
  }
}

static VALUE rb_texture_initialize(VALUE self, VALUE fileName) {
  const char *file_name_str = StringValueCStr(fileName);

  Texture *texture = (Texture *)DATA_PTR(self);
  *texture = LoadTexture(file_name_str);

  return self;
}

static VALUE rb_unload_texture(VALUE self) {
  Texture2D *texture = (Texture *)DATA_PTR(self);

  if (texture) {
    UnloadTexture(*texture);
    free(texture);
  }

  return Qnil;
}

static VALUE rb_draw_texture(VALUE self, VALUE posX_value, VALUE posY_value, VALUE tint_value) {
    Texture *texture = (Texture *)DATA_PTR(self);
    int posX = NUM2INT(posX_value);
    int posY = NUM2INT(posY_value);

    Color *tint = (Color *)DATA_PTR(tint_value);

    DrawTexture(*texture, posX, posY, *tint);

    return Qnil;
}

static VALUE rb_draw_texture_v(VALUE self, VALUE position_value, VALUE tint_value) {
    Texture *texture = (Texture *)DATA_PTR(self);
    Vector2 *position = (Vector2 *)DATA_PTR(position_value);
    Color *tint = (Color *)DATA_PTR(tint_value);

    DrawTextureV(*texture, *position, *tint);

    return Qnil;
}

static VALUE rb_draw_texture_ex(VALUE self, VALUE position_value, VALUE rotation_value, VALUE scale_value, VALUE tint_value) {
    Texture *texture = (Texture *)DATA_PTR(self);
    Vector2 *position = (Vector2 *)DATA_PTR(position_value);
    float rotation = NUM2DBL(rotation_value);
    float scale = NUM2DBL(scale_value);
    Color *tint = (Color *)DATA_PTR(tint_value);

    DrawTextureEx(*texture, *position, rotation, scale, *tint);

    return Qnil;
}

static VALUE rb_draw(int argc, VALUE *argv, VALUE self) {
    VALUE posX_value, posY_value, tint_value, position_value, rotation_value, scale_value;

    switch (argc) {
        case 2:
            rb_scan_args(argc, argv, "2", &position_value, &tint_value);
            return rb_draw_texture_v(self, position_value, tint_value);
        case 3:
            rb_scan_args(argc, argv, "3", &posX_value, &posY_value, &tint_value);
            return rb_draw_texture(self, posX_value, posY_value, tint_value);
        case 4:
            rb_scan_args(argc, argv, "4", &position_value, &rotation_value, &scale_value, &tint_value);
            return rb_draw_texture_ex(self, position_value, rotation_value, scale_value, tint_value);
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
