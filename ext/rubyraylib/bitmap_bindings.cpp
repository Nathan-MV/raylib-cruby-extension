#include <bitmap_bindings.h>

VALUE rb_cBitmap;

//------------------------------------------------------------------------------------
// Texture Loading and Drawing Functions (Module: textures)
//------------------------------------------------------------------------------------

// Image loading functions
// NOTE: These functions do not require GPU access
// RLAPI Image RayLoadImage(const char *fileName);                                                             // Load image from file into CPU memory (RAM)auto
static auto rb_image_initialize(int argc, VALUE *argv, VALUE self) {
  auto *img = get_image(self);

  if (argc == 1) {
    // Handle String or Texture input
    if (rb_obj_is_kind_of(argv[0], rb_cString)) {
      const auto *name = StringValueCStr(argv[0]);
      *img = RayLoadImage(name);
    } else if (rb_obj_is_kind_of(argv[0], rb_cSprite)) {
      auto *texture = get_texture(argv[0]);
      *img = LoadImageFromTexture(*texture);
    } else {
      rb_raise(rb_eTypeError, "expected a String or Texture");
    }
  } else if (argc == 2 || argc == 3) {
    // Handle width, height, and optional color input
    if (rb_obj_is_kind_of(argv[0], rb_cInteger) && rb_obj_is_kind_of(argv[1], rb_cInteger)) {
      auto width = NUM2INT(argv[0]);
      auto height = NUM2INT(argv[1]);

      Color color = {0, 0, 0, 0};

      if (argc == 3) {
        if (rb_obj_is_kind_of(argv[2], rb_cObject)) {
          color = *get_color(argv[2]);
        } else {
          rb_raise(rb_eTypeError, "expected a color object as the third argument");
        }
      }

      *img = GenImageColor(width, height, color);
    } else {
      rb_raise(rb_eTypeError, "expected width and height as integers");
    }
  } else {
    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 1, 2, or 3)", argc);
  }

  return self;
}
// RLAPI Image LoadImageRaw(const char *fileName, int width, int height, int format, int headerSize);       // Load image from RAW file data
static auto rb_load_image_raw(VALUE self, VALUE rb_file_name, VALUE rb_width, VALUE rb_height, VALUE rb_format, VALUE rb_header_size) {
  auto *fileName = StringValueCStr(rb_file_name);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto format = NUM2INT(rb_format);
  auto headerSize = NUM2INT(rb_header_size);

  auto *img = get_image(self);

  *img = LoadImageRaw(fileName, width, height, format, headerSize);

  return self;
}
// RLAPI Image LoadImageAnim(const char *fileName, int *frames);
static auto rb_load_image_anim(VALUE self, VALUE rb_file_name, VALUE rb_frames) {
  auto *fileName = StringValueCStr(rb_file_name);
  auto *frames = get_int_array(rb_frames);

  auto *img = get_image(self);

  *img = LoadImageAnim(fileName, frames);

  free(frames);

  return self;
}
// RLAPI Image LoadImageAnimFromMemory(const char *fileType, const unsigned char *fileData, int
// dataSize, int *frames);
static auto rb_load_image_anim_from_memory(VALUE self, VALUE rb_file_type, VALUE rb_file_data,
                                           VALUE rb_data_size, VALUE rb_frames) {
  auto *fileType = StringValueCStr(rb_file_type);
  const unsigned char *fileData
      = reinterpret_cast<const unsigned char *>(RSTRING_PTR(rb_file_data));
  auto dataSize = NUM2INT(rb_data_size);
  auto *frames = get_int_array(rb_frames);

  auto *img = get_image(self);

  *img = LoadImageAnimFromMemory(fileType, fileData, dataSize, frames);

  free(frames);

  return self;
}
// RLAPI Image LoadImageFromMemory(const char *fileType, const unsigned char *fileData, int dataSize);      // Load image from memory buffer, fileType refers to extension: i.e. '.png'
static auto rb_load_image_from_memory(VALUE self, VALUE rb_file_type, VALUE rb_file_data,
                                      VALUE rb_data_size) {
  auto *fileType = StringValueCStr(rb_file_type);
  const unsigned char *fileData
      = reinterpret_cast<const unsigned char *>(RSTRING_PTR(rb_file_data));
  auto dataSize = NUM2INT(rb_data_size);

  auto *img = get_image(self);

  *img = LoadImageFromMemory(fileType, fileData, dataSize);

  return self;
}
// RLAPI Image LoadImageFromTexture(Texture2D texture);                                                     // Load image from GPU texture data
static auto rb_load_image_from_texture(VALUE self, VALUE rb_texture) {
  auto *texture = get_texture(rb_texture);
  auto *img = get_image(self);

  *img = LoadImageFromTexture(*texture);

  return self;
}
// RLAPI bool IsImageValid(Image image);                                                                    // Check if an image is ready
static auto rb_is_image_ready(VALUE self) {
  auto *img = get_image(self);

  return IsImageValid(*img)? Qtrue : Qfalse;
}
// RLAPI Image LoadImageFromScreen(void);                                                                   // Load image from screen buffer and (screenshot)
static auto rb_load_image_from_screen(VALUE self) {
  auto *img = get_image(self);

  *img = LoadImageFromScreen();

  return self;
}
// RLAPI void UnloadImage(Image image);                                                                     // Unload image from CPU memory (RAM)
static auto rb_unload_image(VALUE self) {
  auto *img = get_image(self);

  UnloadImage(*img);
  delete img;

  return self;
}
// RLAPI bool ExportImage(Image image, const char *fileName);                                               // Export image data to file, returns true on success
static auto rb_export_image(VALUE self, VALUE rb_filename) {
  auto *img = get_image(self);
  const auto *fileName = StringValueCStr(rb_filename);

  auto result = ExportImage(*img, fileName);

  return result ? Qtrue : Qfalse;
}
// RLAPI unsigned char *ExportImageToMemory(Image image, const char *fileType, int *fileSize);              // Export image to memory buffer
// RLAPI bool ExportImageAsCode(Image image, const char *fileName);                                         // Export image as code file defining an array of bytes, returns true on success

// Image generation functions
// RLAPI Image GenImageColor(int width, int height, Color color);                                           // Generate image: plain color
static auto rb_gen_image_color(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_color) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto color = *get_color(rb_color);

  *img = GenImageColor(width, height, color);

  return self;
}
// RLAPI Image GenImageGradientLinear(int width, int height, int direction, Color start, Color end);        // Generate image: linear gradient, direction in degrees [0..360], 0=Vertical gradient
static auto rb_gen_image_gradient_linear(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_direction, VALUE rb_start, VALUE rb_end) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto direction = NUM2INT(rb_direction);
  auto start = *get_color(rb_start);
  auto end = *get_color(rb_end);

  *img = GenImageGradientLinear(width, height, direction, start, end);

  return self;
}
// RLAPI Image GenImageGradientRadial(int width, int height, float density, Color inner, Color outer);      // Generate image: radial gradient
static auto rb_gen_image_gradient_radial(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_density, VALUE rb_inner, VALUE rb_outer) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto density = NUM2DBL(rb_density);
  auto inner = *get_color(rb_inner);
  auto outer = *get_color(rb_outer);

  *img = GenImageGradientRadial(width, height, density, inner, outer);

  return self;
}
// RLAPI Image GenImageGradientSquare(int width, int height, float density, Color inner, Color outer);      // Generate image: square gradient
static auto rb_gen_image_gradient_square(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_density, VALUE rb_inner, VALUE rb_outer) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto density = NUM2DBL(rb_density);
  auto inner = *get_color(rb_inner);
  auto outer = *get_color(rb_outer);

  *img = GenImageGradientSquare(width, height, density, inner, outer);

  return self;
}
// RLAPI Image GenImageChecked(int width, int height, int checksX, int checksY, Color col1, Color col2);    // Generate image: checked
static auto rb_gen_image_checked(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_checks_x, VALUE rb_checks_y, VALUE rb_col1, VALUE rb_col2) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto checks_x = NUM2INT(rb_checks_x);
  auto checks_y = NUM2INT(rb_checks_y);
  auto col1 = *get_color(rb_col1);
  auto col2 = *get_color(rb_col2);

  *img = GenImageChecked(width, height, checks_x, checks_y, col1, col2);

  return self;
}
// RLAPI Image GenImageWhiteNoise(int width, int height, float factor);                                     // Generate image: white noise
static auto rb_gen_image_white_noise(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_factor) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto factor = NUM2DBL(rb_factor);

  *img = GenImageWhiteNoise(width, height, factor);

  return self;
}
// RLAPI Image GenImagePerlinNoise(int width, int height, int offsetX, int offsetY, float scale);           // Generate image: perlin noise
static auto rb_gen_image_perlin_noise(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_offset_x, VALUE rb_offset_y, VALUE rb_scale) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto offset_x = NUM2INT(rb_offset_x);
  auto offset_y = NUM2INT(rb_offset_y);
  auto scale = NUM2DBL(rb_scale);

  *img = GenImagePerlinNoise(width, height, offset_x, offset_y, scale);

  return self;
}
// RLAPI Image GenImageCellular(int width, int height, int tileSize);                                       // Generate image: cellular algorithm, bigger tileSize means bigger cells
static auto rb_gen_image_cellular(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_tile_size) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto tile_size = NUM2INT(rb_tile_size);

  *img = GenImageCellular(width, height, tile_size);

  return self;
}
// RLAPI Image GenImageText(int width, int height, const char *text);                                       // Generate image: grayscale image from text data
static auto rb_gen_image_text(VALUE self, VALUE rb_width, VALUE rb_height, VALUE rb_text) {
  auto *img = get_image(self);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto text = StringValueCStr(rb_text);

  *img = GenImageText(width, height, text);

  return self;
}

// Image manipulation functions
// RLAPI Image ImageCopy(Image image);                                                                      // Create an image duplicate (useful for transformations)
static auto rb_image_copy(VALUE self) {
  auto *img = get_image(self);

  *img = ImageCopy(*img);

  return self;
}
// RLAPI Image ImageFromImage(Image image, RayRectangle rec);                                                  // Create an image from another image piece
static auto rb_image_from_image(VALUE self, VALUE rb_image, VALUE rb_rec) {
  auto *img = get_image(self);
  auto *rec = get_rect(rb_rec);

  *img = ImageFromImage(*img, *rec);

  return self;
}
// RLAPI Image ImageFromChannel(Image image, int selectedChannel);                                          // Create an image from a selected channel of another image (GRAYSCALE)
static auto rb_image_from_channel(VALUE self, VALUE rb_image, VALUE rb_selected_channel) {
  auto *img = get_image(self);
  auto selected_channel = NUM2INT(rb_selected_channel);

  *img = ImageFromChannel(*img, selected_channel);

  return self;
}
// RLAPI Image ImageText(const char *text, int fontSize, Color color);                                      // Create an image from text (default font)
static auto rb_image_text_default(VALUE self, VALUE rb_text, VALUE rb_font_size, VALUE rb_color) {
  auto *img = get_image(self);
  auto font_size = NUM2INT(rb_font_size);
  auto *color = get_color(rb_color);

  *img = ImageText(StringValueCStr(rb_text), font_size, *color);

  return self;
}
// RLAPI Image ImageTextEx(Font font, const char *text, float fontSize, float spacing, Color tint);         // Create an image from text (custom sprite font)
static auto rb_image_text_custom(VALUE self, VALUE rb_font, VALUE rb_text, VALUE rb_font_size, VALUE rb_spacing, VALUE rb_color) {
  auto *img = get_image(self);
  auto *font = get_font(rb_font);
  auto font_size = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);
  auto *color = get_color(rb_color);

  *img = ImageTextEx(*font, StringValueCStr(rb_text), font_size, spacing, *color);

  return self;
}
// RLAPI void ImageFormat(Image *image, int newFormat);                                                     // Convert image data to desired format
static auto rb_image_format(VALUE self, VALUE rb_new_format) {
  auto *img = get_image(self);
  auto new_format = NUM2INT(rb_new_format);

  ImageFormat(img, new_format);

  return self;
}
// RLAPI void ImageToPOT(Image *image, Color fill);                                                         // Convert image to POT (power-of-two)
static auto rb_image_to_pot(VALUE self, VALUE rb_fill) {
  auto *img = get_image(self);
  auto *fill = get_color(rb_fill);

  ImageToPOT(img, *fill);

  return self;
}
// RLAPI void ImageCrop(Image *image, RayRectangle crop);                                                      // Crop an image to a defined rectangle
static auto rb_image_crop(VALUE self, VALUE rb_crop) {
  auto *img = get_image(self);
  auto *crop = get_rect(rb_crop);

  ImageCrop(img, *crop);

  return self;
}
// RLAPI void ImageAlphaCrop(Image *image, float threshold);                                                // Crop image depending on alpha value
static auto rb_image_alpha_crop(VALUE self, VALUE rb_threshold) {
  auto *img = get_image(self);
  auto threshold = NUM2DBL(rb_threshold);

  ImageAlphaCrop(img, threshold);

  return self;
}
// RLAPI void ImageAlphaClear(Image *image, Color color, float threshold);                                  // Clear alpha channel to desired color
static auto rb_image_alpha_clear(VALUE self, VALUE rb_color, VALUE rb_threshold) {
  auto *img = get_image(self);
  auto *color = get_color(rb_color);
  auto threshold = NUM2DBL(rb_threshold);

  ImageAlphaClear(img, *color, threshold);

  return self;
}
// RLAPI void ImageAlphaMask(Image *image, Image alphaMask);                                                // Apply alpha mask to image
static auto rb_image_alpha_mask(VALUE self, VALUE rb_alpha_mask) {
  auto *img = get_image(self);
  auto *alpha_mask = get_image(rb_alpha_mask);

  ImageAlphaMask(img, *alpha_mask);

  return self;
}
// RLAPI void ImageAlphaPremultiply(Image *image);                                                          // Premultiply alpha channel
static auto rb_image_alpha_premultiply(VALUE self) {
  auto *img = get_image(self);

  ImageAlphaPremultiply(img);

  return self;
}
// RLAPI void ImageBlurGaussian(Image *image, int blurSize);                                                // Apply Gaussian blur using a box blur approximation
static auto rb_image_blur_gaussian(VALUE self, VALUE rb_blur_size) {
  auto *img = get_image(self);
  auto blur_size = NUM2INT(rb_blur_size);

  ImageBlurGaussian(img, blur_size);

  return self;
}
// RLAPI void ImageKernelConvolution(Image *image, const float *kernel, int kernelSize);                    // Apply custom square convolution kernel to image
static auto rb_image_kernel_convolution(VALUE self, VALUE rb_kernel, VALUE rb_kernel_size) {
  // Get the image pointer
  auto *img = get_image(self);

  // Convert the Ruby kernel array to a C array of floats
  Check_Type(rb_kernel, T_ARRAY);  // Ensure rb_kernel is an array
  auto kernel_size = NUM2INT(rb_kernel_size);
  auto *kernel = new float[kernel_size * kernel_size];  // Allocate memory for the kernel

  // Populate the kernel array
  for (int i = 0; i < kernel_size * kernel_size; ++i) {
    auto rb_elem = rb_ary_entry(rb_kernel, i);
    kernel[i] = NUM2DBL(rb_elem);
  }

  // Apply the kernel to the image
  ImageKernelConvolution(img, kernel, kernel_size);

  // Clean up
  delete[] kernel;

  return self;
}
// RLAPI void ImageResize(Image *image, int newWidth, int newHeight);                                       // Resize image (Bicubic scaling algorithm)
static auto rb_image_resize(VALUE self, VALUE rb_new_width, VALUE rb_new_height) {
  auto *img = get_image(self);
  auto new_width = NUM2INT(rb_new_width);
  auto new_height = NUM2INT(rb_new_height);

  ImageResize(img, new_width, new_height);

  return self;
}
// RLAPI void ImageResizeNN(Image *image, int newWidth,int newHeight);                                      // Resize image (Nearest-Neighbor scaling algorithm)
static auto rb_image_resize_nn(VALUE self, VALUE rb_new_width, VALUE rb_new_height) {
  auto *img = get_image(self);
  auto new_width = NUM2INT(rb_new_width);
  auto new_height = NUM2INT(rb_new_height);

  ImageResizeNN(img, new_width, new_height);

  return self;
}
// RLAPI void ImageResizeCanvas(Image *image, int newWidth, int newHeight, int offsetX, int offsetY, Color fill); // Resize canvas and fill with color
static auto rb_image_resize_canvas(VALUE self, VALUE rb_new_width, VALUE rb_new_height, VALUE rb_offset_x, VALUE rb_offset_y, VALUE rb_fill_color) {
  auto *img = get_image(self);
  auto new_width = NUM2INT(rb_new_width);
  auto new_height = NUM2INT(rb_new_height);
  auto offset_x = NUM2INT(rb_offset_x);
  auto offset_y = NUM2INT(rb_offset_y);
  auto *fill_color = get_color(rb_fill_color);

  ImageResizeCanvas(img, new_width, new_height, offset_x, offset_y, *fill_color);

  return self;
}
// RLAPI void ImageMipmaps(Image *image);                                                                   // Compute all mipmap levels for a provided image
static auto rb_image_mipmaps(VALUE self) {
  auto *img = get_image(self);

  ImageMipmaps(img);

  return self;
}
// RLAPI void ImageDither(Image *image, int rBpp, int gBpp, int bBpp, int aBpp);                            // Dither image data to 16bpp or lower (Floyd-Steinberg dithering)
static auto rb_image_dither(VALUE self, VALUE rb_r_bpp, VALUE rb_g_bpp, VALUE rb_b_bpp, VALUE rb_a_bpp) {
  auto *img = get_image(self);
  auto r_bpp = NUM2INT(rb_r_bpp);
  auto g_bpp = NUM2INT(rb_g_bpp);
  auto b_bpp = NUM2INT(rb_b_bpp);
  auto a_bpp = NUM2INT(rb_a_bpp);

  ImageDither(img, r_bpp, g_bpp, b_bpp, a_bpp);

  return self;
}
// RLAPI void ImageFlipVertical(Image *image);                                                              // Flip image vertically
static auto rb_image_flip_vertical(VALUE self) {
  auto *img = get_image(self);

  ImageFlipVertical(img);

  return self;
}
// RLAPI void ImageFlipHorizontal(Image *image);                                                            // Flip image horizontally
static auto rb_image_flip_horizontal(VALUE self) {
  auto *img = get_image(self);

  ImageFlipHorizontal(img);

  return self;
}
// RLAPI void ImageRotate(Image *image, int degrees);                                                       // Rotate image by input angle in degrees (-359 to 359)
static auto rb_image_rotate(VALUE self, VALUE rb_degrees) {
  auto *img = get_image(self);
  auto degrees = NUM2INT(rb_degrees);

  ImageRotate(img, degrees);

  return self;
}
// RLAPI void ImageRotateCW(Image *image);                                                                  // Rotate image clockwise 90deg
static auto rb_image_rotate_cw(VALUE self) {
  auto *img = get_image(self);

  ImageRotateCW(img);

  return self;
}
// RLAPI void ImageRotateCCW(Image *image);                                                                 // Rotate image counter-clockwise 90deg
static auto rb_image_rotate_ccw(VALUE self) {
  auto *img = get_image(self);

  ImageRotateCCW(img);

  return self;
}
// RLAPI void ImageColorTint(Image *image, Color color);                                                    // Modify image color: tint
static auto rb_image_color_tint(VALUE self, VALUE rb_color) {
  auto *img = get_image(self);
  auto *color = get_color(rb_color);

  ImageColorTint(img, *color);

  return self;
}
// RLAPI void ImageColorInvert(Image *image);                                                               // Modify image color: invert
static auto rb_image_color_invert(VALUE self) {
  auto *img = get_image(self);

  ImageColorInvert(img);

  return self;
}
// RLAPI void ImageColorGrayscale(Image *image);                                                            // Modify image color: grayscale
static auto rb_image_color_grayscale(VALUE self) {
  auto *img = get_image(self);

  ImageColorGrayscale(img);

  return self;
}
// RLAPI void ImageColorContrast(Image *image, float contrast);                                             // Modify image color: contrast (-100 to 100)
static auto rb_image_color(VALUE self, VALUE rb_contrast) {
  auto *img = get_image(self);
  auto contrast = NUM2DBL(rb_contrast);

  ImageColorContrast(img, contrast);

  return self;
}
// RLAPI void ImageColorBrightness(Image *image, int brightness);                                           // Modify image color: brightness (-255 to 255)
static auto rb_image_color_brightness(VALUE self, VALUE rb_brightness) {
  auto *img = get_image(self);
  auto brightness = NUM2INT(rb_brightness);

  ImageColorBrightness(img, brightness);

  return self;
}
// RLAPI void ImageColorReplace(Image *image, Color color, Color replace);                                  // Modify image color: replace color
static auto rb_image_color_replace(VALUE self, VALUE rb_color, VALUE rb_replace) {
  auto *img = get_image(self);
  auto *color = get_color(rb_color);
  auto *replace = get_color(rb_replace);

  ImageColorReplace(img, *color, *replace);

  return self;
}
// RLAPI Color *LoadImageColors(Image image);                                                               // Load color data from image as a Color array (RGBA - 32bit)
static auto rb_load_image_colors(VALUE self) {
  auto *img = get_image(self);
  Color *colors = LoadImageColors(*img);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, colors);
}
// RLAPI Color *LoadImagePalette(Image image, int maxPaletteSize, int *colorCount);                         // Load colors palette from image as a Color array (RGBA - 32bit)
static auto rb_load_image_palette(VALUE self, VALUE rb_max_palette_size) {
  auto *img = get_image(self);
  auto max_palette_size = NUM2INT(rb_max_palette_size);
  Color *colors = LoadImagePalette(*img, max_palette_size, NULL);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, colors);
}
// RLAPI void UnloadImageColors(Color *colors);                                                             // Unload color data loaded with LoadImageColors()
static auto rb_unload_image_colors(VALUE self, VALUE rb_colors) {
  auto *colors = get_color(rb_colors);

  UnloadImageColors(colors);

  return Qnil;
}
// RLAPI void UnloadImagePalette(Color *colors);                                                            // Unload colors palette loaded with LoadImagePalette()
static auto rb_unload_image_palette(VALUE self, VALUE rb_colors) {
  auto *colors = get_color(rb_colors);

  UnloadImagePalette(colors);

  return Qnil;
}
// RLAPI RayRectangle GetImageAlphaBorder(Image image, float threshold);                                       // Get image alpha border rectangle
static auto rb_get_image_alpha_border(VALUE self, VALUE rb_threshold) {
  auto *img = get_image(self);
  auto threshold = NUM2DBL(rb_threshold);

  auto result = GetImageAlphaBorder(*img, threshold);

  return Data_Wrap_Struct(rb_cRect, NULL, rb_object_free<RayRectangle>, &result);
}
// RLAPI Color GetImageColor(Image image, int x, int y);                                                    // Get image pixel color at (x, y) position
static auto rb_get_image_color(VALUE self, VALUE rb_x, VALUE rb_y) {
  auto *img = get_image(self);
  auto x = NUM2INT(rb_x);
  auto y = NUM2INT(rb_y);

  Color result = GetImageColor(*img, x, y);

  return Data_Wrap_Struct(rb_cColor, NULL, rb_object_free<Color>, &result);
}

// Image drawing functions
// NOTE: Image software-rendering functions (CPU)
// RLAPI void ImageClearBackground(Image *dst, Color color);                                                // Clear image background with given color
static auto rb_image_clear_background(VALUE self, VALUE rb_color) {
  auto *img = get_image(self);
  auto *color = get_color(rb_color);

  ImageClearBackground(img, *color);

  return self;
}
// RLAPI void ImageDrawPixel(Image *dst, int posX, int posY, Color color);                                  // Draw pixel within an image
static auto rb_image_draw_pixel(VALUE self, VALUE rb_x, VALUE rb_y, VALUE rb_color) {
  auto *img = get_image(self);
  auto x = NUM2INT(rb_x);
  auto y = NUM2INT(rb_y);
  auto *color = get_color(rb_color);

  ImageDrawPixel(img, x, y, *color);

  return self;
}
// RLAPI void ImageDrawPixelV(Image *dst, Vector2 position, Color color);                                   // Draw pixel within an image (Vector version)
static auto rb_image_draw_pixel_v(VALUE self, VALUE rb_position, VALUE rb_color) {
  auto *img = get_image(self);
  auto *position = get_vec2(rb_position);
  auto *color = get_color(rb_color);

  ImageDrawPixelV(img, *position, *color);

  return self;
}
// RLAPI void ImageDrawLine(Image *dst, int startPosX, int startPosY, int endPosX, int endPosY, Color color); // Draw line within an image
static auto rb_image_draw_line(VALUE self, VALUE rb_start_x, VALUE rb_start_y, VALUE rb_end_x, VALUE rb_end_y, VALUE rb_color) {
  auto *img = get_image(self);
  auto start_x = NUM2INT(rb_start_x);
  auto start_y = NUM2INT(rb_start_y);
  auto end_x = NUM2INT(rb_end_x);
  auto end_y = NUM2INT(rb_end_y);
  auto *color = get_color(rb_color);

  ImageDrawLine(img, start_x, start_y, end_x, end_y, *color);

  return self;
}
// RLAPI void ImageDrawLineV(Image *dst, Vector2 start, Vector2 end, Color color);                          // Draw line within an image (Vector version)
static auto rb_image_draw_line_v(VALUE self, VALUE rb_start, VALUE rb_end, VALUE rb_color) {
  auto *img = get_image(self);
  auto *start = get_vec2(rb_start);
  auto *end = get_vec2(rb_end);
  auto *color = get_color(rb_color);

  ImageDrawLineV(img, *start, *end, *color);

  return self;
}
// RLAPI void ImageDrawLineEx(Image *dst, Vector2 start, Vector2 end, int thick, Color color);              // Draw a line defining thickness within an image
static auto rb_image_draw_line_ex(VALUE self, VALUE rb_start, VALUE rb_end, VALUE rb_thick, VALUE rb_color) {
  auto *img = get_image(self);
  auto *start = get_vec2(rb_start);
  auto *end = get_vec2(rb_end);
  auto thick = NUM2INT(rb_thick);
  auto *color = get_color(rb_color);

  ImageDrawLineEx(img, *start, *end, thick, *color);

  return self;
}
// RLAPI void ImageDrawCircle(Image *dst, int centerX, int centerY, int radius, Color color);               // Draw a filled circle within an image
static auto rb_image_draw_circle(VALUE self, VALUE rb_center_x, VALUE rb_center_y, VALUE rb_radius, VALUE rb_color) {
  auto *img = get_image(self);
  auto center_x = NUM2INT(rb_center_x);
  auto center_y = NUM2INT(rb_center_y);
  auto radius = NUM2INT(rb_radius);
  auto *color = get_color(rb_color);

  ImageDrawCircle(img, center_x, center_y, radius, *color);

  return self;
}
// RLAPI void ImageDrawCircleV(Image *dst, Vector2 center, int radius, Color color);                        // Draw a filled circle within an image (Vector version)
static auto rb_image_draw_circle_v(VALUE self, VALUE rb_center, VALUE rb_radius, VALUE rb_color) {
  auto *img = get_image(self);
  auto *center = get_vec2(rb_center);
  auto radius = NUM2INT(rb_radius);
  auto *color = get_color(rb_color);

  ImageDrawCircleV(img, *center, radius, *color);

  return self;
}
// RLAPI void ImageDrawCircleLines(Image *dst, int centerX, int centerY, int radius, Color color);          // Draw circle outline within an image
static auto rb_image_draw_circle_lines(VALUE self, VALUE rb_center_x, VALUE rb_center_y, VALUE rb_radius, VALUE rb_color) {
  auto *img = get_image(self);
  auto center_x = NUM2INT(rb_center_x);
  auto center_y = NUM2INT(rb_center_y);
  auto radius = NUM2INT(rb_radius);
  auto *color = get_color(rb_color);

  ImageDrawCircleLines(img, center_x, center_y, radius, *color);

  return self;
}
// RLAPI void ImageDrawCircleLinesV(Image *dst, Vector2 center, int radius, Color color);                   // Draw circle outline within an image (Vector version)
static auto rb_image_draw_circle_lines_v(VALUE self, VALUE rb_center, VALUE rb_radius, VALUE rb_color) {
  auto *img = get_image(self);
  auto *center = get_vec2(rb_center);
  auto radius = NUM2INT(rb_radius);
  auto *color = get_color(rb_color);

  ImageDrawCircleLinesV(img, *center, radius, *color);

  return self;
}
// RLAPI void ImageDrawRectangle(Image *dst, int posX, int posY, int width, int height, Color color);       // Draw rectangle within an image
static auto rb_image_draw_rectangle(VALUE self, VALUE rb_pos_x, VALUE rb_pos_y, VALUE rb_width, VALUE rb_height, VALUE rb_color) {
  auto *img = get_image(self);
  auto pos_x = NUM2INT(rb_pos_x);
  auto pos_y = NUM2INT(rb_pos_y);
  auto width = NUM2INT(rb_width);
  auto height = NUM2INT(rb_height);
  auto *color = get_color(rb_color);

  ImageDrawRectangle(img, pos_x, pos_y, width, height, *color);

  return self;
}
// RLAPI void ImageDrawRectangleV(Image *dst, Vector2 position, Vector2 size, Color color);                 // Draw rectangle within an image (Vector version)
static auto rb_image_draw_rectangle_v(VALUE self, VALUE rb_position, VALUE rb_size, VALUE rb_color) {
  auto img = get_image(self);
  auto *position = get_vec2(rb_position);
  auto *size = get_vec2(rb_size);
  auto *color = get_color(rb_color);

  ImageDrawRectangleV(img, *position, *size, *color);

  return self;
}
// RLAPI void ImageDrawRectangleRec(Image *dst, RayRectangle rec, Color color);                                // Draw rectangle within an image
static auto rb_image_draw_rectangle_rec(VALUE self, VALUE rb_rec, VALUE rb_color) {
  auto *img = get_image(self);
  auto *rec = get_rect(rb_rec);
  auto *color = get_color(rb_color);

  ImageDrawRectangleRec(img, *rec, *color);

  return self;
}
// RLAPI void ImageDrawRectangleLines(Image *dst, RayRectangle rec, int thick, Color color);                   // Draw rectangle lines within an image
static auto rb_image_draw_rectangle_lines(VALUE self, VALUE rb_rec, VALUE rb_thick, VALUE rb_color) {
  auto *img = get_image(self);
  auto *rec = get_rect(rb_rec);
  auto thick = NUM2INT(rb_thick);
  auto *color = get_color(rb_color);

  ImageDrawRectangleLines(img, *rec, thick, *color);

  return self;
}
// RLAPI void ImageDrawTriangle(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);               // Draw triangle within an image
static auto rb_image_draw_triangle(VALUE self, VALUE rb_v1, VALUE rb_v2, VALUE rb_v3, VALUE rb_color) {
  auto *img = get_image(self);
  auto *v1 = get_vec2(rb_v1);
  auto *v2 = get_vec2(rb_v2);
  auto *v3 = get_vec2(rb_v3);
  auto *color = get_color(rb_color);

  ImageDrawTriangle(img, *v1, *v2, *v3, *color);

  return self;
}
// RLAPI void ImageDrawTriangleEx(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color c1, Color c2, Color c3); // Draw triangle with interpolated colors within an image
static auto rb_image_draw_triangle_ex(VALUE self, VALUE rb_v1, VALUE rb_v2, VALUE rb_v3, VALUE rb_c1, VALUE rb_c2, VALUE rb_c3) {
  auto *img = get_image(self);
  auto *v1 = get_vec2(rb_v1);
  auto *v2 = get_vec2(rb_v2);
  auto *v3 = get_vec2(rb_v3);
  auto *c1 = get_color(rb_c1);
  auto *c2 = get_color(rb_c2);
  auto *c3 = get_color(rb_c3);

  ImageDrawTriangleEx(img, *v1, *v2, *v3, *c1, *c2, *c3);

  return self;
}
// RLAPI void ImageDrawTriangleLines(Image *dst, Vector2 v1, Vector2 v2, Vector2 v3, Color color);          // Draw triangle outline within an image
static auto rb_image_draw_triangle_lines(VALUE self, VALUE rb_v1, VALUE rb_v2, VALUE rb_v3, VALUE rb_color) {
  auto *img = get_image(self);
  auto *v1 = get_vec2(rb_v1);
  auto *v2 = get_vec2(rb_v2);
  auto *v3 = get_vec2(rb_v3);
  auto *color = get_color(rb_color);

  ImageDrawTriangleLines(img, *v1, *v2, *v3, *color);

  return self;
}
// RLAPI void ImageDrawTriangleFan(Image *dst, Vector2 *points, int pointCount, Color color);               // Draw a triangle fan defined by points within an image (first vertex is the center)
static auto rb_image_draw_triangle_fan(VALUE self, VALUE rb_points, VALUE rb_point_count,
                                        VALUE rb_color) {
  auto *img = get_image(self);
  auto *points = get_vec2(rb_points);
  auto point_count = NUM2INT(rb_point_count);
  auto *color = get_color(rb_color);

  ImageDrawTriangleFan(img, points, point_count, *color);

  return self;
}
// RLAPI void ImageDrawTriangleStrip(Image *dst, Vector2 *points, int pointCount, Color color);             // Draw a triangle strip defined by points within an image
static auto rb_image_draw_triangle_strip(VALUE self, VALUE rb_points, VALUE rb_point_count,
                                        VALUE rb_color) {
  auto *img = get_image(self);
  auto *points = get_vec2(rb_points);
  auto point_count = NUM2INT(rb_point_count);
  auto *color = get_color(rb_color);

  ImageDrawTriangleStrip(img, points, point_count, *color);

  return self;
}
// RLAPI void ImageDraw(Image *dst, Image src, RayRectangle srcRec, RayRectangle dstRec, Color tint);             // Draw a source image within a destination image (tint applied to source)
static auto rb_image_draw(VALUE self, VALUE rb_src, VALUE rb_src_rec, VALUE rb_dst_rec, VALUE rb_tint) {
  auto *dst = get_image(self);
  auto *src = get_image(rb_src);
  auto *src_rec = get_rect(rb_src_rec);
  auto *dst_rec = get_rect(rb_dst_rec);
  auto *tint = get_color(rb_tint);

  ImageDraw(dst, *src, *src_rec, *dst_rec, *tint);

  return self;
}
// RLAPI void ImageDrawText(Image *dst, const char *text, int posX, int posY, int fontSize, Color color);   // Draw text (using default font) within an image (destination)
static auto rb_image_draw_text(VALUE self, VALUE rb_text, VALUE rb_pos_x, VALUE rb_pos_y,
                                VALUE rb_font_size, VALUE rb_color) {
  auto *dst = get_image(self);
  const auto *text = StringValueCStr(rb_text);
  auto pos_x = NUM2INT(rb_pos_x);
  auto pos_y = NUM2INT(rb_pos_y);
  auto font_size = NUM2INT(rb_font_size);
  auto *color = get_color(rb_color);

  ImageDrawText(dst, text, pos_x, pos_y, font_size, *color);

  return self;
}
// RLAPI void ImageDrawTextEx(Image *dst, Font font, const char *text, Vector2 position, float fontSize, float spacing, Color tint); // Draw text (custom sprite font) within an image (destination)
static auto rb_image_draw_text_ex(VALUE self, VALUE rb_dst, VALUE rb_font, VALUE rb_text, VALUE rb_position,
                                    VALUE rb_font_size, VALUE rb_spacing, VALUE rb_tint) {
  auto *dst = get_image(self);
  auto *font = get_font(rb_font);
  const auto *text = StringValueCStr(rb_text);
  auto *position = get_vec2(rb_position);
  auto font_size = NUM2DBL(rb_font_size);
  auto spacing = NUM2DBL(rb_spacing);
  auto *tint = get_color(rb_tint);

  ImageDrawTextEx(dst, *font, text, *position, font_size, spacing, *tint);

  return self;
}

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

extern "C" void Init_Bitmap() {
  rb_cBitmap = rb_define_class_under(rb_mRL, "Bitmap", rb_cObject);
  rb_define_alloc_func(rb_cBitmap, rb_image_alloc<Image>);

  // Define initialize and attribute accessors (getters and setters)
  rb_define_method(rb_cBitmap, "initialize", rb_image_initialize, -1);

  // Define additional methods
  rb_define_method(rb_cBitmap, "load_raw", rb_load_image_raw, 5);
  rb_define_method(rb_cBitmap, "load_anim", rb_load_image_anim, 2);
  rb_define_method(rb_cBitmap, "load_anim_from_memory", rb_load_image_anim_from_memory, 4);
  rb_define_method(rb_cBitmap, "from_memory", rb_load_image_from_memory, 3);
  rb_define_method(rb_cBitmap, "texture=", rb_load_image_from_texture, 1);
  rb_define_method(rb_cBitmap, "ready?", rb_is_image_ready, 0);
  rb_define_method(rb_cBitmap, "from_screen", rb_load_image_from_screen, 0);
  rb_define_method(rb_cBitmap, "unload", rb_unload_image, 0);
  rb_define_method(rb_cBitmap, "dispose", rb_unload_image, 0); // unload alias
  rb_define_method(rb_cBitmap, "export", rb_export_image, 1);
  rb_define_method(rb_cBitmap, "gen_color", rb_gen_image_color, 3);
  rb_define_method(rb_cBitmap, "gen_gradient_linear", rb_gen_image_gradient_linear, 5);
  rb_define_method(rb_cBitmap, "gen_gradient_radial", rb_gen_image_gradient_radial, 5);
  rb_define_method(rb_cBitmap, "gen_gradient_square", rb_gen_image_gradient_square, 5);
  rb_define_method(rb_cBitmap, "gen_checked", rb_gen_image_checked, 6);
  rb_define_method(rb_cBitmap, "gen_white_noise", rb_gen_image_white_noise, 3);
  rb_define_method(rb_cBitmap, "gen_perlin_noise", rb_gen_image_perlin_noise, 5);
  rb_define_method(rb_cBitmap, "gen_cellular", rb_gen_image_cellular, 3);
  rb_define_method(rb_cBitmap, "gen_text", rb_gen_image_text, 3);
  rb_define_method(rb_cBitmap, "copy", rb_image_copy, 0);
  rb_define_method(rb_cBitmap, "from_image", rb_image_from_image, 2);
  rb_define_method(rb_cBitmap, "from_channel", rb_image_from_channel, 2);
  rb_define_method(rb_cBitmap, "text_default", rb_image_text_default, 3);
  rb_define_method(rb_cBitmap, "text_custom", rb_image_text_custom, 5);
  rb_define_method(rb_cBitmap, "format", rb_image_format, 1);
  rb_define_method(rb_cBitmap, "to_pot", rb_image_to_pot, 1);
  rb_define_method(rb_cBitmap, "crop", rb_image_crop, 1);
  rb_define_method(rb_cBitmap, "alpha_crop", rb_image_alpha_crop, 1);
  rb_define_method(rb_cBitmap, "alpha_clear", rb_image_alpha_clear, 2);
  rb_define_method(rb_cBitmap, "alpha_mask", rb_image_alpha_mask, 1);
  rb_define_method(rb_cBitmap, "alpha_premultiply", rb_image_alpha_premultiply, 0);
  rb_define_method(rb_cBitmap, "gaussian_blur", rb_image_blur_gaussian, 1);
  rb_define_method(rb_cBitmap, "kernel_convolution", rb_image_kernel_convolution, 2);
  rb_define_method(rb_cBitmap, "resize", rb_image_resize, 2);
  rb_define_method(rb_cBitmap, "resize_nn", rb_image_resize_nn, 2);
  rb_define_method(rb_cBitmap, "resize_canvas", rb_image_resize_canvas, 5);
  rb_define_method(rb_cBitmap, "mipmaps", rb_image_mipmaps, 0);
  rb_define_method(rb_cBitmap, "dither", rb_image_dither, 4);
  rb_define_method(rb_cBitmap, "flip_v", rb_image_flip_vertical, 0);
  rb_define_method(rb_cBitmap, "flip_h", rb_image_flip_horizontal, 0);
  rb_define_method(rb_cBitmap, "rotate", rb_image_rotate, 1);
  rb_define_method(rb_cBitmap, "rotate_cw", rb_image_rotate_cw, 0);
  rb_define_method(rb_cBitmap, "rotate_ccw", rb_image_rotate_ccw, 0);
  rb_define_method(rb_cBitmap, "tint", rb_image_color_tint, 1);
  rb_define_method(rb_cBitmap, "color_invert", rb_image_color_invert, 0);
  rb_define_method(rb_cBitmap, "grayscale", rb_image_color_grayscale, 0);
  rb_define_method(rb_cBitmap, "brightness", rb_image_color_brightness, 1);
  rb_define_method(rb_cBitmap, "color_replace", rb_image_color_replace, 2);
  rb_define_method(rb_cBitmap, "load_colors", rb_load_image_colors, 0);
  rb_define_method(rb_cBitmap, "load_palette", rb_load_image_palette, 1);
  rb_define_method(rb_cBitmap, "unload_colors", rb_unload_image_colors, 1);
  rb_define_method(rb_cBitmap, "unload_palette", rb_unload_image_palette, 1);
  rb_define_method(rb_cBitmap, "alpha_border", rb_get_image_alpha_border, 1);
  rb_define_method(rb_cBitmap, "color", rb_get_image_color, 2);
  rb_define_method(rb_cBitmap, "clear_background", rb_image_clear_background, 1);
  rb_define_method(rb_cBitmap, "draw_pixel", rb_image_draw_pixel, 3);
  rb_define_method(rb_cBitmap, "draw_pixel_v", rb_image_draw_pixel_v, 2);
  rb_define_method(rb_cBitmap, "draw_line", rb_image_draw_line, 5);
  rb_define_method(rb_cBitmap, "draw_line_v", rb_image_draw_line_v, 3);
  rb_define_method(rb_cBitmap, "draw_line_ex", rb_image_draw_line_ex, 4);
  rb_define_method(rb_cBitmap, "draw_circle", rb_image_draw_circle, 4);
  rb_define_method(rb_cBitmap, "draw_circle_v", rb_image_draw_circle_v, 3);
  rb_define_method(rb_cBitmap, "draw_circle_lines", rb_image_draw_circle_lines, 4);
  rb_define_method(rb_cBitmap, "draw_circle_lines_v", rb_image_draw_circle_lines_v, 3);
  rb_define_method(rb_cBitmap, "draw_rectangle", rb_image_draw_rectangle, 5);
  rb_define_method(rb_cBitmap, "draw_rectangle_v", rb_image_draw_rectangle_v, 3);
  rb_define_method(rb_cBitmap, "draw_rectangle_rec", rb_image_draw_rectangle_rec, 2);
  rb_define_method(rb_cBitmap, "draw_rectangle_lines", rb_image_draw_rectangle_lines, 3);
  rb_define_method(rb_cBitmap, "draw_triangle", rb_image_draw_triangle, 4);
  rb_define_method(rb_cBitmap, "draw_triangle_ex", rb_image_draw_triangle_ex, 6);
  rb_define_method(rb_cBitmap, "draw_triangle_lines", rb_image_draw_triangle_lines, 4);
  rb_define_method(rb_cBitmap, "draw_triangle_fan", rb_image_draw_triangle_fan, 3);
  rb_define_method(rb_cBitmap, "draw_triangle_strip", rb_image_draw_triangle_strip, 3);
  rb_define_method(rb_cBitmap, "draw", rb_image_draw, 4);
  rb_define_method(rb_cBitmap, "draw_text", rb_image_draw_text, 5);
  rb_define_method(rb_cBitmap, "draw_text_ex", rb_image_draw_text_ex, 7);
}
