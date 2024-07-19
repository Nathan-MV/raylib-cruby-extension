#include "texture_atlas.hpp"

VALUE rb_cTextureAtlas;

void free_texture_atlas(void *p) {
  if (TextureAtlas *atlas = static_cast<TextureAtlas *>(p)) {
    delete[] atlas->rects;
    UnloadRenderTexture(atlas->texture);
    delete atlas;
  }
}

VALUE texture_atlas_alloc(VALUE klass) {
  try {
    auto *atlas = new TextureAtlas(); // Uses default constructor
    return Data_Wrap_Struct(klass, nullptr, free_texture_atlas, atlas);
  } catch (const std::bad_alloc &) {
    rb_raise(rb_eNoMemError, "Failed to allocate memory for TextureAtlas.");
  }
  return Qnil; // Safety
}

VALUE texture_atlas_initialize(VALUE self, VALUE width, VALUE height) {
  auto *atlas = get_texture_atlas(self);
  atlas->texture = LoadRenderTexture(NUM2INT(width), NUM2INT(height));
  return self;
}

VALUE texture_atlas_add_texture(VALUE self, VALUE texture, VALUE rect) {
  auto *atlas = get_texture_atlas(self);
  RayRectangle newRect = *get_rect(rect);
  RayRectangle *newRects = static_cast<RayRectangle *>(
      REALLOC_N(atlas->rects, RayRectangle, atlas->count + 1));

  if (!newRects)
    rb_raise(rb_eNoMemError, "Failed to allocate memory for texture rects");

  atlas->rects = newRects;
  atlas->rects[atlas->count++] = newRect;

  RayRectangle source = {0, 0, newRect.width,
                      newRect.height};
  Vector2 origin = {newRect.width / 2.0f,
                    newRect.height / 2.0f};
  float rotation = 0.0f;
  Vector2 destPos = {newRect.x, newRect.y};
  BeginTextureMode(atlas->texture);


  DrawTexturePro(*get_texture(texture), source, newRect, origin, rotation,
                 WHITE);

  EndTextureMode();

  return self;
}

VALUE texture_atlas_draw(VALUE self, VALUE position) {
  auto *atlas = get_texture_atlas(self);
  DrawTextureV(atlas->texture.texture, *get_vec2(position), WHITE);
  return self;
}

VALUE texture_atlas_draw_index(VALUE self, VALUE index, VALUE position) {
  auto *atlas = get_texture_atlas(self);
  int idx = NUM2INT(index);
  if (idx < 0 || idx >= atlas->count) {
    rb_raise(rb_eArgError, "Index out of bounds");
  }
  RayRectangle rect = atlas->rects[idx];
  Vector2 pos = *get_vec2(position);
  DrawTextureRec(atlas->texture.texture, rect, pos, WHITE);
  return self;
}

VALUE rb_texture_atlas_draw_batch(VALUE self, VALUE positions) {
  auto *atlas = get_texture_atlas(self);
  int len = RARRAY_LEN(positions);
  for (int i = 0; i < len; i++) {
    DrawTextureV(atlas->texture.texture, *get_vec2(rb_ary_entry(positions, i)),
                 WHITE);
  }
  return self;
}

extern "C" void initializeTextureAtlas() {
  rb_cTextureAtlas = rb_define_class_under(rb_mRl, "TextureAtlas", rb_cObject);
  rb_define_alloc_func(rb_cTextureAtlas, texture_atlas_alloc);
  rb_define_method(rb_cTextureAtlas, "initialize", texture_atlas_initialize, 2);
  rb_define_method(rb_cTextureAtlas, "add", texture_atlas_add_texture, 2);
  rb_define_method(rb_cTextureAtlas, "draw", texture_atlas_draw, 1);
  rb_define_method(rb_cTextureAtlas, "draw_index", texture_atlas_draw_index, 2);
  rb_define_method(rb_cTextureAtlas, "draw_batch", rb_texture_atlas_draw_batch,
                   1);
}
