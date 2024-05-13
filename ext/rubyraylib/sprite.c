#include "sprite.h"

// Ruby method to allocate memory for a new Texture
static VALUE texture2d_alloc(VALUE klass) {
  Texture2D *texture;
  VALUE obj = Data_Make_Struct(klass, Texture2D, 0, -1, texture);
  return obj;
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

// Function to draw texture with four arguments
static VALUE rb_draw_texture(VALUE texture_value, VALUE posX_value,
                             VALUE posY_value, VALUE tint_value) {
  Texture2D *texture = (Texture2D *)DATA_PTR(texture_value);
  int posX = NUM2INT(posX_value);
  int posY = NUM2INT(posY_value);
  Color *tint = (Color *)DATA_PTR(tint_value);

  DrawTexture(*texture, posX, posY, *tint);

  return Qnil;
}

// Function to draw texture with three arguments
static VALUE rb_draw_texture_v(VALUE texture_value, VALUE position_value,
                               VALUE tint_value) {
  Texture2D *texture = (Texture2D *)DATA_PTR(texture_value);
  Vector2 *position = (Vector2 *)DATA_PTR(position_value);
  Color *tint = (Color *)DATA_PTR(tint_value);

  DrawTextureV(*texture, *position, *tint);

  return Qnil;
}

// Function to draw texture with five arguments
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

// Main function to handle drawing based on the number of arguments
static VALUE rb_draw_sprite(int argc, VALUE *argv, VALUE self) {
  // Check the number of arguments
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
    // Incorrect number of arguments
    rb_raise(rb_eArgError, "Wrong number of arguments. Expected 3, 4, or 5.");
    break;
  }

  return Qnil;
}

void initializeSprite() {
  VALUE rb_cSprite = rb_define_class("Sprite", rb_cObject);

  rb_define_alloc_func(rb_cSprite, texture2d_alloc);
  rb_define_singleton_method(rb_cSprite, "load", rb_load_texture, 1);
  rb_define_singleton_method(rb_cSprite, "unload", rb_unload_texture, 1);
  rb_define_singleton_method(rb_cSprite, "draw", rb_draw_sprite, -1);
}
