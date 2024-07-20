#include "texture.hpp"

VALUE rb_cTexture;

RB_TEXTURE_GETTER_INT(rb_texture_width, width)
RB_TEXTURE_GETTER_INT(rb_texture_height, height)
RB_TEXTURE_GETTER_INT(rb_texture_mipmaps, mipmaps)
RB_TEXTURE_GETTER_INT(rb_texture_format, format)

// Texture loading functions
// NOTE: These functions require GPU access

// Load texture from file into GPU memory (VRAM)
static VALUE rb_texture_initialize(VALUE self, VALUE fileName) {
  Texture *texture = get_texture(self);
  const char *name = StringValueCStr(fileName);

  *texture = LoadTexture(name);

  return self;
}
// RLAPI Texture2D LoadTextureFromImage(Image image);                                                       // Load texture from image data
// RLAPI TextureCubemap LoadTextureCubemap(Image image, int layout);                                        // Load cubemap from image, multiple image cubemap layouts supported
// RLAPI bool IsTextureReady(Texture2D texture);                                                            // Check if a texture is ready
// Unload texture from GPU memory (VRAM)
static VALUE rb_unload_texture(VALUE self) {
  Texture *texture = get_texture(self);

  UnloadTexture(*texture);

  return Qnil;
}
// RLAPI void UpdateTexture(Texture2D texture, const void *pixels);                                         // Update GPU texture with new data
// RLAPI void UpdateTextureRec(Texture2D texture, RayRectangle rec, const void *pixels);                       // Update GPU texture rectangle with new data

// Texture configuration functions
// RLAPI void GenTextureMipmaps(Texture2D *texture);                                                        // Generate GPU mipmaps for a texture
// RLAPI void SetTextureFilter(Texture2D texture, int filter);                                              // Set texture scaling filter mode
// RLAPI void SetTextureWrap(Texture2D texture, int wrap);                                                  // Set texture wrapping mode

// Texture drawing functions
// RLAPI void DrawTexture(Texture2D texture, int posX, int posY, Color tint);                               // Draw a Texture2D
// RLAPI void DrawTextureV(Texture2D texture, Vector2 position, Color tint);                                // Draw a Texture2D with position defined as Vector2
// RLAPI void DrawTextureEx(Texture2D texture, Vector2 position, float rotation, float scale, Color tint);  // Draw a Texture2D with extended parameters
static VALUE rb_draw_texture_ex(int argc, VALUE *argv, VALUE self) {
    VALUE position, rotation, tint;

    rb_scan_args(argc, argv, "12", &position, &rotation, &tint);

    Texture* tex = get_texture(self);
    Vector2* pos = get_vec2(position);
    float rot = NIL_P(rotation) ? 0 : NUM2DBL(rotation);
    float scl = 1.0f;
    Color col = !NIL_P(tint) ? *get_color(tint) : (Color){ 255, 255, 255, 255 };

    DrawTextureEx(*tex, *pos, rot, scl, col);

    return Qnil;
}
// Draw a part of a texture defined by a rectangle
static VALUE rb_draw_texture_rec(VALUE self, VALUE source, VALUE position, VALUE tint) {
  Texture *tex = get_texture(self);
  RayRectangle *src = get_rect(source);
  Vector2 *pos = get_vec2(position);
  Color *col = get_color(tint);

  DrawTextureRec(*tex, *src, *pos, *col);

  return Qnil;
}
// Draw a part of a texture defined by a rectangle with 'pro' parameters
static VALUE rb_draw_texture_pro(int argc, VALUE *argv, VALUE self) {
    VALUE source, dest, origin, rotation, tint;

    rb_scan_args(argc, argv, "14", &source, &dest, &origin, &rotation, &tint);

    Texture* tex = get_texture(self);
    RayRectangle src = *get_rect(source);
    RayRectangle dst = !NIL_P(dest) ? *get_rect(dest) : (RayRectangle){ src.x, src.y, fabsf(src.width), fabsf(src.height) };
    Vector2 orig = !NIL_P(origin) ? *get_vec2(origin) : (Vector2){ 0.0f, 0.0f };
    float rot = NIL_P(rotation) ? 0 : NUM2DBL(rotation);
    Color col = !NIL_P(tint) ? *get_color(tint) : (Color){ 255, 255, 255, 255 };

    DrawTexturePro(*tex, src, dst, orig, rot, col);

    return Qnil;
}
// RLAPI void DrawTextureNPatch(Texture2D texture, NPatchInfo nPatchInfo, RayRectangle dest, Vector2 origin, float rotation, Color tint); // Draws a texture (or part of it) that stretches or shrinks nicely

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

static VALUE rb_set_texture_scale(VALUE self, VALUE value) {
  Texture *texture = get_texture(self);
  int val = NUM2INT(value);

  texture->width *= val;
  texture->height *= val;

  return self;
}

extern "C" void initializeTexture() {
  rb_cTexture = rb_define_class_under(rb_mRL, "Texture", rb_cObject);
  rb_define_alloc_func(rb_cTexture, rb_texture_alloc<Texture>);

  rb_define_method(rb_cTexture, "initialize", rb_texture_initialize, 1);
  rb_define_method(rb_cTexture, "width", rb_texture_width, 0);
  rb_define_method(rb_cTexture, "height", rb_texture_height, 0);
  rb_define_method(rb_cTexture, "mipmaps", rb_texture_mipmaps, 0);
  rb_define_method(rb_cTexture, "format", rb_texture_format, 0);

  rb_define_method(rb_cTexture, "scale=", rb_set_texture_scale, 1);

  rb_define_method(rb_cTexture, "unload", rb_unload_texture, 0);
  rb_define_method(rb_cTexture, "draw", rb_draw_texture_ex, -1);
  rb_define_method(rb_cTexture, "draw_rec", rb_draw_texture_rec, 3);
  rb_define_method(rb_cTexture, "draw_pro", rb_draw_texture_pro, -1);
}
