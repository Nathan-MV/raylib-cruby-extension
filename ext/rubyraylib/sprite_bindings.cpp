#include <sprite_bindings.h>
#include "ruby/internal/intern/object.h"

VALUE rb_cSprite;

// Load texture from file into GPU memory (VRAM)
// RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
// RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
static auto rb_texture_initialize(int argc, VALUE *argv, VALUE self) {
  auto *texture = get_texture(self);

  if (argc == 1) {
    if (rb_obj_is_kind_of(argv[0], rb_cString)) {
      const auto *filename = StringValueCStr(argv[0]);
      *texture = LoadTexture(filename);
    } else if (rb_obj_is_kind_of(argv[0], rb_cBitmap)) {
      auto *img = get_image(argv[0]);
      *texture = LoadTextureFromImage(*img);
    } else {
      rb_raise(rb_eTypeError, "expected a String or Image");
    }
  } else if (argc == 2) {
    if (rb_obj_is_kind_of(argv[0], rb_cBitmap) &&
        rb_obj_is_kind_of(argv[1], rb_cInteger)) {
      auto *img = get_image(argv[0]);
      int layout = NUM2INT(argv[1]);

      *texture = LoadTextureCubemap(*img, layout);
    } else {
      rb_raise(rb_eTypeError, "expected image and layout");
    }
  } //else {
  //  rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1 or 2 arguments)", argc);
  //}

  return self;
}

RB_TEXTURE_GETTER_INT(rb_texture_width, width)
RB_TEXTURE_GETTER_INT(rb_texture_height, height)
RB_TEXTURE_GETTER_INT(rb_texture_mipmaps, mipmaps)
RB_TEXTURE_GETTER_INT(rb_texture_format, format)

// Texture loading functions
// NOTE: These functions require GPU access
// RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
static auto rb_load_texture_from_image(VALUE self, VALUE rb_image) {
    auto *texture = get_texture(self);
    auto *img = get_image(rb_image);

    *texture = LoadTextureFromImage(*img);

    return self;
}
// RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
static auto rb_load_texture_cubemap(VALUE self, VALUE rb_image, VALUE rb_layout) {
  auto *texture = get_texture(self);
  auto *img = get_image(rb_image);
  int layout = NUM2INT(rb_layout);

  *texture = LoadTextureCubemap(*img, layout);

  return self;
}

// RLAPI bool IsTextureValid(Texture2D texture);                                                            // Check if a texture is ready
static auto rb_is_texture_ready(VALUE self) {
  auto *texture = get_texture(self);

  return IsTextureValid(*texture)? Qtrue : Qfalse;
}
// Unload texture from GPU memory (VRAM)
static auto rb_unload_texture(VALUE self) {
  auto *texture = get_texture(self);

  UnloadTexture(*texture);
  delete texture;

  return self;
}
// RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
static auto rb_update_texture(VALUE self, VALUE rb_pixels) {
  auto *texture = get_texture(self);
  const auto *pixels = RSTRING_PTR(rb_pixels);

  UpdateTexture(*texture, pixels);

  return self;
}
// RLAPI void UpdateTextureRec(Texture2D texture, RayRectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data
static auto rb_update_texture_rec(VALUE self, VALUE rb_rec, VALUE rb_pixels) {
  auto *texture = get_texture(self);
  auto *rect = get_rect(rb_rec);
  const auto *pixels = RSTRING_PTR(rb_pixels);

  UpdateTextureRec(*texture, *rect, pixels);

  return self;
}

// Texture configuration functions
// RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
static auto rb_gen_texture_mipmaps(VALUE self) {
  auto texture = get_texture(self);

  GenTextureMipmaps(texture);

  return self;
}
// RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
static auto rb_set_texture_filter(VALUE self, VALUE rb_filter) {
  auto *texture = get_texture(self);
  int filter = NUM2INT(rb_filter);

  SetTextureFilter(*texture, filter);

  return Qnil;
}
// RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode
static auto rb_set_texture_wrap(VALUE self, VALUE rb_wrap) {
  auto *texture = get_texture(self);
  int wrap = NUM2INT(rb_wrap);

  SetTextureWrap(*texture, wrap);

  return Qnil;
}

// Texture drawing functions
// RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
static auto rb_draw_texture(VALUE self, VALUE rb_pos_y, VALUE rb_pos_x, VALUE rb_tint) {
  auto *texture = get_texture(self);
  int posY = NUM2INT(rb_pos_y);
  int posX = NUM2INT(rb_pos_x);
  auto *tint = get_color(rb_tint);

  DrawTexture(*texture, posY, posX, *tint);

  return self;
}
// RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
static auto rb_draw_texture_v(VALUE self, VALUE rb_position, VALUE rb_tint) {
  auto *texture = get_texture(self);
  auto *position = get_vec2(rb_position);
  auto *tint = get_color(rb_tint);

  DrawTextureV(*texture, *position, *tint);

  return self;
}
// RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
static auto rb_draw_texture_ex(int argc, VALUE *argv, VALUE self) {
  VALUE rb_position, rb_rotation, rb_tint;

  rb_scan_args(argc, argv, "03", &rb_position, &rb_rotation, &rb_tint);

  auto *texture = get_texture(self);
  auto position = !NIL_P(rb_position) ? *get_vec2(rb_position) : (Vector2){0, 0};
  auto rotation = NIL_P(rb_rotation) ? 0 : NUM2DBL(rb_rotation);
  auto scale = 1.0f;
  auto tint = !NIL_P(rb_tint) ? *get_color(rb_tint) : (Color){255, 255, 255, 255};

  DrawTextureEx(*texture, position, rotation, scale, tint);

  return self;
}
// Draw a part of a texture defined by a rectangle
static auto rb_draw_texture_rec(int argc, VALUE *argv, VALUE self) {
  VALUE rb_source, rb_position, rb_tint;

  rb_scan_args(argc, argv, "21", &rb_source, &rb_position, &rb_tint);

  auto *texture = get_texture(self);
  auto *source = get_rect(rb_source);
  auto *position = get_vec2(rb_position);
  auto tint = !NIL_P(rb_tint) ? *get_color(rb_tint) : (Color){255, 255, 255, 255};

  DrawTextureRec(*texture, *source, *position, tint);

  return self;
}
// Draw a part of a texture defined by a rectangle with 'pro' parameters
static auto rb_draw_texture_pro(int argc, VALUE *argv, VALUE self) {
  VALUE rb_source, rb_dest, rb_origin, rb_rotation, rb_tint;

  rb_scan_args(argc, argv, "14", &rb_source, &rb_dest, &rb_origin, &rb_rotation, &rb_tint);

  auto *texture = get_texture(self);
  auto source = *get_rect(rb_source);
  auto dst = !NIL_P(rb_dest)
                 ? *get_rect(rb_dest)
                 : (RayRectangle){source.x, source.y, fabsf(source.width), fabsf(source.height)};
  auto origin = !NIL_P(rb_origin) ? *get_vec2(rb_origin) : (Vector2){0.0f, 0.0f};
  auto rotation = NIL_P(rb_rotation) ? 0 : NUM2DBL(rb_rotation);
  auto tint = !NIL_P(rb_tint) ? *get_color(rb_tint) : (Color){255, 255, 255, 255};

  DrawTexturePro(*texture, source, dst, origin, rotation, tint);

  return self;
}
// RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, RayRectangle dest, Vector2 origin, float rotation, Color tint); // Draws a texture (or part of it) that stretches or shrinks nicely

// Texture parameters: filter mode
// NOTE 1: Filtering considers mipmaps if available in the texture
// NOTE 2: Filter is accordingly set for minification and magnification
// typedef enum {
//     TEXTURE_FILTER_POINT = 0,               // No filter, just pixel approximation
//     TEXTURE_FILTER_BILINEAR,                // Linear filtering
//     TEXTURE_FILTER_TRILINEAR,               // Trilinear filtering (linear with mipmaps)
//     TEXTURE_FILTER_ANISOTROPIC_4X,          // Anisotropic filtering 4x
//     TEXTURE_FILTER_ANISOTROPIC_8X,          // Anisotropic filtering 8x
//     TEXTURE_FILTER_ANISOTROPIC_16X,         // Anisotropic filtering 16x
// } TextureFilter;

// Texture parameters: wrap mode
// typedef enum {
//     TEXTURE_WRAP_REPEAT = 0,                // Repeats texture in tiled mode
//     TEXTURE_WRAP_CLAMP,                     // Clamps texture to edge pixel in tiled mode
//     TEXTURE_WRAP_MIRROR_REPEAT,             // Mirrors and repeats the texture in tiled mode
//     TEXTURE_WRAP_MIRROR_CLAMP               // Mirrors and clamps to border the texture in tiled mode
// } TextureWrap;

// Pixel formats
// NOTE: Support depends on OpenGL version and platform
// typedef enum {
//     PIXELFORMAT_UNCOMPRESSED_GRAYSCALE = 1, // 8 bit per pixel (no alpha)
//     PIXELFORMAT_UNCOMPRESSED_GRAY_ALPHA,    // 8*2 bpp (2 channels)
//     PIXELFORMAT_UNCOMPRESSED_R5G6B5,        // 16 bpp
//     PIXELFORMAT_UNCOMPRESSED_R8G8B8,        // 24 bpp
//     PIXELFORMAT_UNCOMPRESSED_R5G5B5A1,      // 16 bpp (1 bit alpha)
//     PIXELFORMAT_UNCOMPRESSED_R4G4B4A4,      // 16 bpp (4 bit alpha)
//     PIXELFORMAT_UNCOMPRESSED_R8G8B8A8,      // 32 bpp
//     PIXELFORMAT_UNCOMPRESSED_R32,           // 32 bpp (1 channel - float)
//     PIXELFORMAT_UNCOMPRESSED_R32G32B32,     // 32*3 bpp (3 channels - float)
//     PIXELFORMAT_UNCOMPRESSED_R32G32B32A32,  // 32*4 bpp (4 channels - float)
//     PIXELFORMAT_UNCOMPRESSED_R16,           // 16 bpp (1 channel - half float)
//     PIXELFORMAT_UNCOMPRESSED_R16G16B16,     // 16*3 bpp (3 channels - half float)
//     PIXELFORMAT_UNCOMPRESSED_R16G16B16A16,  // 16*4 bpp (4 channels - half float)
//     PIXELFORMAT_COMPRESSED_DXT1_RGB,        // 4 bpp (no alpha)
//     PIXELFORMAT_COMPRESSED_DXT1_RGBA,       // 4 bpp (1 bit alpha)
//     PIXELFORMAT_COMPRESSED_DXT3_RGBA,       // 8 bpp
//     PIXELFORMAT_COMPRESSED_DXT5_RGBA,       // 8 bpp
//     PIXELFORMAT_COMPRESSED_ETC1_RGB,        // 4 bpp
//     PIXELFORMAT_COMPRESSED_ETC2_RGB,        // 4 bpp
//     PIXELFORMAT_COMPRESSED_ETC2_EAC_RGBA,   // 8 bpp
//     PIXELFORMAT_COMPRESSED_PVRT_RGB,        // 4 bpp
//     PIXELFORMAT_COMPRESSED_PVRT_RGBA,       // 4 bpp
//     PIXELFORMAT_COMPRESSED_ASTC_4x4_RGBA,   // 8 bpp
//     PIXELFORMAT_COMPRESSED_ASTC_8x8_RGBA    // 2 bpp
// } PixelFormat;

static auto rb_set_texture_scale(VALUE self, VALUE value) {
  auto *texture = get_texture(self);
  auto val = NUM2DBL(value);

  texture->width *= val;
  texture->height *= val;

  return self;
}

// Load texture from file into GPU memory (VRAM)
static auto rb_load_texture(VALUE self, VALUE rb_string) {
  auto *texture = get_texture(self);
  const auto *filename = StringValueCStr(rb_string);

  *texture = LoadTexture(filename);

  return self;
}

extern "C" void Init_Sprite() {
  rb_cSprite = rb_define_class_under(rb_mRL, "Sprite", rb_cObject);
  rb_define_alloc_func(rb_cSprite, rb_texture_alloc<Texture2D>);

  rb_define_method(rb_cSprite, "initialize", rb_texture_initialize, -1);
  rb_define_method(rb_cSprite, "width", rb_texture_width, 0);
  rb_define_method(rb_cSprite, "height", rb_texture_height, 0);
  rb_define_method(rb_cSprite, "mipmaps", rb_texture_mipmaps, 0);
  rb_define_method(rb_cSprite, "format", rb_texture_format, 0);

  rb_define_method(rb_cSprite, "bitmap=", rb_load_texture_from_image, 1);
  rb_define_method(rb_cSprite, "load_cubemap", rb_load_texture_cubemap, 2);
  rb_define_method(rb_cSprite, "ready?", rb_is_texture_ready, 0);
  rb_define_method(rb_cSprite, "unload", rb_unload_texture, 0);
  rb_define_method(rb_cSprite, "dispose", rb_unload_texture, 0); // unload alias
  rb_define_method(rb_cSprite, "update", rb_update_texture, 1);
  rb_define_method(rb_cSprite, "update_rect", rb_update_texture_rec, 2);
  rb_define_method(rb_cSprite, "gen_mipmaps", rb_gen_texture_mipmaps, 0);
  rb_define_method(rb_cSprite, "filter=", rb_set_texture_filter, 1);
  rb_define_method(rb_cSprite, "wrap=", rb_set_texture_wrap, 1);
  rb_define_method(rb_cSprite, "draw", rb_draw_texture_ex, -1);
  rb_define_method(rb_cSprite, "draw_rect", rb_draw_texture_rec, -1);
  rb_define_method(rb_cSprite, "draw_pro", rb_draw_texture_pro, -1);

  rb_define_method(rb_cSprite, "scale=", rb_set_texture_scale, 1);
  rb_define_method(rb_cSprite, "load=", rb_load_texture, 1);
}
