#include "sprite.h"

static void rb_texture2d_free(void *ptr) {
  Texture2D *texture2d = (Texture2D *)ptr;
  if (texture2d) {
    UnloadTexture(*texture2d);
    free(texture2d);
  }
}

static VALUE rb_texture2d_alloc(VALUE klass) {
  Texture2D *texture2d = (Texture2D *)malloc(sizeof(Texture2D));
  return Data_Wrap_Struct(klass, NULL, rb_texture2d_free, texture2d);
}

static VALUE rb_load_texture(VALUE self, VALUE fileName) {
  const char *file_name_str = StringValueCStr(fileName);

  Texture2D *texture = (Texture2D *)malloc(sizeof(Texture2D));
  *texture = LoadTexture(file_name_str);

  return Data_Wrap_Struct(rb_cObject, NULL, free, texture);
}

static VALUE rb_unload_texture(VALUE self, VALUE texture_obj) {
  Texture2D *texture = NULL;
  Data_Get_Struct(texture_obj, Texture2D, texture);

  if (texture) {
    UnloadTexture(*texture);
    free(texture);
  }

  return Qnil;
}

static VALUE rb_draw_texture(VALUE texture_value, VALUE posX_value,
                             VALUE posY_value, VALUE tint_value) {
  Texture2D *texture = (Texture2D *)DATA_PTR(texture_value);
  int posX = NUM2INT(posX_value);
  int posY = NUM2INT(posY_value);
  Color *tint = (Color *)DATA_PTR(tint_value);

  DrawTexture(*texture, posX, posY, *tint);

  return Qnil;
}

static VALUE rb_draw_texture_v(VALUE texture_value, VALUE position_value,
                               VALUE tint_value) {
  Texture2D *texture = (Texture2D *)DATA_PTR(texture_value);
  Vector2 *position = (Vector2 *)DATA_PTR(position_value);
  Color *tint = (Color *)DATA_PTR(tint_value);

  DrawTextureV(*texture, *position, *tint);

  return Qnil;
}

static VALUE rb_draw_texture_ex(VALUE texture_value, VALUE position_value,
                                VALUE rotation_value, VALUE scale_value,
                                VALUE tint_value) {
  Texture2D *texture = (Texture2D *)DATA_PTR(texture_value);
  Vector2 *position = (Vector2 *)DATA_PTR(position_value);
  float rotation = NUM2DBL(rotation_value);
  float scale = NUM2DBL(scale_value);
  Color *tint = (Color *)DATA_PTR(tint_value);

  DrawTextureEx(*texture, *position, rotation, scale, *tint);

  return Qnil;
}

static VALUE rb_draw_sprite(int argc, VALUE *argv, VALUE self) {
  switch (argc) {
  case 3:
    rb_scan_args(argc, argv, "3", &argv[0], &argv[1], &argv[2]);
    rb_draw_texture_v(argv[0], argv[1], argv[2]);
    break;
  case 4:
    rb_scan_args(argc, argv, "4", &argv[0], &argv[1], &argv[2], &argv[3]);
    rb_draw_texture(argv[0], argv[1], argv[2], argv[3]);
    break;
  case 5:
    rb_scan_args(argc, argv, "5", &argv[0], &argv[1], &argv[2], &argv[3],
                 &argv[4]);
    rb_draw_texture_ex(argv[0], argv[1], argv[2], argv[3], argv[4]);
    break;
  default:
    rb_raise(rb_eArgError, "Wrong number of arguments. Expected 3, 4, or 5.");
    break;
  }

  return Qnil;
}

void initializeSprite() {
  VALUE rb_cSprite = rb_define_class("Sprite", rb_cObject);

  rb_define_alloc_func(rb_cSprite, rb_texture2d_alloc);
  rb_define_singleton_method(rb_cSprite, "load", rb_load_texture, 1);
  rb_define_singleton_method(rb_cSprite, "unload", rb_unload_texture, 1);
  rb_define_singleton_method(rb_cSprite, "draw", rb_draw_sprite, -1);
}
