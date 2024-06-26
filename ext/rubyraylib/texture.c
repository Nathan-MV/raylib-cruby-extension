#include "texture.h"

static void rb_texture_free(void *ptr) {
  Texture *texture = (Texture *)ptr;
  if (texture) {
    UnloadTexture(*texture);
    free(texture);
  }
}

static VALUE rb_texture_alloc(VALUE klass) {
  Texture *texture = ALLOC(Texture);
  return Data_Wrap_Struct(klass, NULL, rb_texture_free, texture);
}

void initializeTexture() {
  VALUE rb_cTexture = rb_define_class("Texture", rb_cObject);

  rb_define_alloc_func(rb_cTexture, rb_texture_alloc);
}
