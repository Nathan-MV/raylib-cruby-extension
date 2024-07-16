// RLAPI RenderTexture2D LoadRenderTexture(int width, int height);                                          // Load texture for rendering (framebuffer)
// static VALUE rb_load_render_texture(VALUE self, VALUE width, VALUE height) {
//   int w = NUM2INT(width);
//   int h = NUM2INT(height);

//   LoadRenderTexture(w, h);

//   return self;
// }
// RLAPI bool IsRenderTextureReady(RenderTexture2D target);                                                 // Check if a render texture is ready
// RLAPI void UnloadRenderTexture(RenderTexture2D target);                                                  // Unload render texture from GPU memory (VRAM)
