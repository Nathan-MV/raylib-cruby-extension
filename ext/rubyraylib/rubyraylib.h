#ifndef RUBYRAYLIB_H
#define RUBYRAYLIB_H 1

#include "ruby.h"
#include "raylib.h"
#include "vector2.h"
#include "window.h"
#include "texture.h"
#include "sprite.h"
#include "color.h"
#include "draw.h"
#include "image.h"
#include "kernel.h"

// Function declarations for initialization
void initializeVec2();
void initializeWindow();
void initializeDraw();
void initializeTexture();
void initializeSprite();
void initializeColor();
void initializeImage();
void initializeKernel();

#endif /* RUBYRAYLIB_H */
