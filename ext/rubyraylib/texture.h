#ifndef TEXTURE_H
#define TEXTURE_H

#include "ruby.h"
#include "raylib_values.h"
#include "color.h"
#include "vec2.h"

Texture* get_texture(VALUE obj);
void initializeTexture();

#endif // TEXTURE_H
