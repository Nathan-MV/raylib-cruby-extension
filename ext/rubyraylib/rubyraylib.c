#include "rubyraylib.h"

RUBY_FUNC_EXPORTED void
Init_rubyraylib(void)
{
  initializeVec2();
  initializeVec3();
  initializeVec4();
  initializeColor();
  initializeImage();
  initializeTexture();
  initializeWindow();
  initializeDraw();
  initializeKernel();
}
