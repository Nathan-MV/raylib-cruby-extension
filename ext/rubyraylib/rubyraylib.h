#ifndef RUBYRAYLIB_H
#define RUBYRAYLIB_H 1

#include "ruby.h"
#include "raylib_values.h"

#include "color.h"
#include "draw.h"
#include "image.h"
#include "kernel.h"
#include "texture.h"
#include "vec2.h"
#include "vec3.h"
#include "vec4.h"
#include "window.h"

// Function declarations for initialization
void initializeVec2();
void initializeVec3();
void initializeVec4();
void initializeWindow();
void initializeDraw();
void initializeTexture();
void initializeColor();
void initializeImage();
void initializeKernel();

#endif // RUBYRAYLIB_H
