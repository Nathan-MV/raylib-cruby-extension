#include "rubyraylib.h"

RUBY_FUNC_EXPORTED void
Init_rubyraylib(void)
{
  initializeVec2();
  initializeColor();
  initializeImage();
  initializeTexture();
  initializeSprite();
  initializeWindow();
  initializeDraw();
  initializeKernel();
}
