#include "ease.hpp"

RB_EASE(rb_ease_linear, EaseLinear)
RB_EASE(rb_ease_sine, EaseSine)
RB_EASE(rb_ease_circ, EaseCirc)
RB_EASE(rb_ease_cubic, EaseCubic)
RB_EASE(rb_ease_quad, EaseQuad)
RB_EASE(rb_ease_expo, EaseExpo)
RB_EASE(rb_ease_back, EaseBack)
RB_EASE(rb_ease_bounce, EaseBounce)
RB_EASE(rb_ease_elastic, EaseElastic)

// Initializes the Ease module and defines its functions
extern "C" void initializeEase() {
  VALUE rb_cEase = rb_define_module_under(rb_mRl, "Ease");

  rb_define_module_function(rb_cEase, "linear", rb_ease_linear, 5);
  rb_define_module_function(rb_cEase, "sine", rb_ease_sine, 5);
  rb_define_module_function(rb_cEase, "circ", rb_ease_circ, 5);
  rb_define_module_function(rb_cEase, "cubic", rb_ease_cubic, 5);
  rb_define_module_function(rb_cEase, "quad", rb_ease_quad, 5);
  rb_define_module_function(rb_cEase, "expo", rb_ease_expo, 5);
  rb_define_module_function(rb_cEase, "back", rb_ease_back, 5);
  rb_define_module_function(rb_cEase, "bounce", rb_ease_bounce, 5);
  rb_define_module_function(rb_cEase, "elastic", rb_ease_elastic, 5);
}
