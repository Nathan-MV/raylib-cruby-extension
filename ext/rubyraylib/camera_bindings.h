#ifndef CAMERA_H
#define CAMERA_H

#include "ruby_values.h"
#include "raylib_values.h"

extern VALUE rb_cCamera;
extern "C" void Init_Camera();

inline Camera2D *get_camera(VALUE obj) {
  Camera2D *camera;
  Data_Get_Struct(obj, Camera2D, camera);

  return camera;
}

#define RB_CAMERA_GETTER_VEC2(name, member)                           \
  static VALUE name(VALUE self) {                                     \
    Camera2D *camera = get_camera(self);                              \
    Vector2 *vec2 = &camera->member;                                  \
    return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, vec2); \
  }

#define RB_CAMERA_SETTER_VEC2(name, member)    \
  static VALUE name(VALUE self, VALUE value) { \
    Camera2D *camera = get_camera(self);       \
    Vector2 *vec2 = get_vec2(value);       \
    camera->member = *vec2;                \
    return self;                               \
  }

#define RB_CAMERA_GETTER(name, member)   \
  static VALUE name(VALUE self) {        \
    Camera2D *camera = get_camera(self); \
                                         \
    return DBL2NUM(camera->member);      \
  }

#define RB_CAMERA_SETTER(name, member)         \
  static VALUE name(VALUE self, VALUE value) { \
    Camera2D *camera = get_camera(self);       \
    camera->member = NUM2DBL(value);           \
    return self;                               \
  }

#endif // CAMERA_H
