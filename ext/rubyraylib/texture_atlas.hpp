#ifndef TEXTURE_ATLAS_H
#define TEXTURE_ATLAS_H

#include <new>
#include "ruby_values.hpp"
#include "raylib_values.hpp"
#include "vec2.hpp"
#include "rect.hpp"
#include "texture.hpp"
#include <iostream>

struct TextureAtlas {
  RenderTexture2D texture;
  Rectangle *rects;
  int count;

  TextureAtlas() : rects(nullptr), count(0) {} // Default values
};

extern VALUE rb_cTextureAtlas;
extern "C" void initializeTextureAtlas();

inline TextureAtlas* get_texture_atlas(VALUE obj) {
  TextureAtlas *atlas;
  Data_Get_Struct(obj, TextureAtlas, atlas);
  return atlas;
}

#endif // TEXTURE_ATLAS_H
