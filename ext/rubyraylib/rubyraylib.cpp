#include "rubyraylib.hpp"

RUBY_FUNC_EXPORTED void Init_rubyraylib(void) {
  initializeKernel();

  // Modules
  initializeWindow();
  initializeInput();
  initializeKeyboard();
  initializeMouse();
  initializeGamepad();
  initializeTouch();
  initializeGestures();
  initializeDraw();
  initializeShapes();

  // Classes
  initializeColor();
  initializeRect();
  initializeVec2();
  initializeVec3();
  initializeVec4();
  initializeTexture();
  initializeImage();

  // External
  initializeGui();
  initializeEase();

  // Custom
  initializeTextureAtlas();
}
