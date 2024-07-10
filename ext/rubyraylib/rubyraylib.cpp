#include "rubyraylib.hpp"

RUBY_FUNC_EXPORTED void Init_rubyraylib(void) {
  initializeRect();
  initializeVec2();
  initializeVec3();
  initializeVec4();
  initializeColor();
  initializeImage();
  initializeTexture();
  initializeWindow();
  initializeDraw();
  initializeKernel();
  initializeGui();
  initializeEase();
  initializeKeyboard();
  initializeMouse();
  initializeGamepad();
  initializeTouch();
}
