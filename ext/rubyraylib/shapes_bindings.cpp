#include <shapes_bindings.h>

//------------------------------------------------------------------------------------
// Basic Shapes Drawing Functions (Module: shapes)
//------------------------------------------------------------------------------------
// Set texture and rectangle to be used on shapes drawing
// NOTE: It can be useful when using basic shapes and one single font,
// defining a font char white rectangle would allow drawing everything in a single draw call
// RLAPI void SetShapesTexture(Texture2D texture, RayRectangle source);       // Set texture and rectangle to be used on shapes drawing
// RLAPI Texture2D GetShapesTexture(void);                                 // Get texture that is used for shapes drawing
// RLAPI RayRectangle GetShapesTextureRectangle(void);                        // Get texture source rectangle that is used for shapes drawing

extern "C" void Init_Shapes(void) {
  VALUE rb_mShapes = rb_define_module_under(rb_mRL, "Shapes");

}
