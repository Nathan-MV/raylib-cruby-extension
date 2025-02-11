#include <camera_bindings.h>

VALUE rb_cCamera;

//------------------------------------------------------------------------------------
// Camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
// RLAPI void UpdateCamera(Camera *camera, int mode);      // Update camera position for selected
// mode static auto rb_update_camera(VALUE self, VALUE rb_mode) {
//   auto *camera = get_camera(self);
//   auto mode = NUM2INT(rb_mode);

//   UpdateCamera(camera, mode);

//   return self;
// }
// RLAPI void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation
// static auto rb_update_camera_pro(VALUE self, VALUE rb_movement, VALUE rb_rotation, VALUE rb_zoom) {
//   auto *camera = get_camera(self);
//   auto movement = get_vec3(rb_movement);
//   auto rotation = get_vec3(rb_rotation);
//   auto zoom = NUM2FLOAT(rb_zoom);

//   UpdateCameraPro(camera, movement, rotation, zoom);

//   return self;
// }

// Screen-space-related functions
// #define GetMouseRay GetScreenToWorldRay     // Compatibility hack for previous raylib versions
// RLAPI Ray GetScreenToWorldRay(Vector2 position, Camera camera);         // Get a ray trace from screen position (i.e mouse)
// RLAPI Ray GetScreenToWorldRayEx(Vector2 position, Camera camera, int width, int height); // Get a ray trace from screen position (i.e mouse) in a viewport
// RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);        // Get the screen space position for a 3d world space position
// RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Get size position for a 3d world space position
// RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);    // Get the screen space position for a 2d camera world space position
static auto rb_get_world_to_screen_2d(VALUE self, VALUE rb_position) {
  auto *camera = get_camera(self);
  auto *position = get_vec2(rb_position);

  auto result = GetWorldToScreen2D(*position, *camera);

  return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, &result);
}
// RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);    // Get the world space position for a 2d camera screen space position
static auto rb_get_screen_to_world_2d(VALUE self, VALUE rb_position) {
  auto *camera = get_camera(self);
  auto *position = get_vec2(rb_position);

  auto result = GetScreenToWorld2D(*position, *camera);

  return Data_Wrap_Struct(rb_cVec2, NULL, rb_object_free<Vector2>, &result);
}
// RLAPI Matrix GetCameraMatrix(Camera camera);                            // Get camera transform matrix (view matrix)
// RLAPI Matrix GetCameraMatrix2D(Camera2D camera);                        // Get camera 2d transform matrix
// static VALUE rb_get_camera_matrix_2d(VALUE self) {
//   Camera2D *camera = get_camera_2d(self);

//   auto matrix = GetCameraMatrix2D(*camera);

//   return wrap_matrix(matrix);
// }

// RLAPI Vector3 GetCameraForward(Camera *camera);
// RLAPI Vector3 GetCameraUp(Camera *camera);
// RLAPI Vector3 GetCameraRight(Camera *camera);

// // Camera movement
// RLAPI void CameraMoveForward(Camera *camera, float distance, bool moveInWorldPlane);
// RLAPI void CameraMoveUp(Camera *camera, float distance);
// RLAPI void CameraMoveRight(Camera *camera, float distance, bool moveInWorldPlane);
// RLAPI void CameraMoveToTarget(Camera *camera, float delta);

// // Camera rotation
// RLAPI void CameraYaw(Camera *camera, float angle, bool rotateAroundTarget);
// RLAPI void CameraPitch(Camera *camera, float angle, bool lockView, bool rotateAroundTarget, bool rotateUp);
// RLAPI void CameraRoll(Camera *camera, float angle);

// RLAPI Matrix GetCameraViewMatrix(Camera *camera);
// RLAPI Matrix GetCameraProjectionMatrix(Camera* camera, float aspect);

// Camera system modes
// typedef enum {
//     CAMERA_CUSTOM = 0,              // Camera custom, controlled by user (UpdateCamera() does nothing)
//     CAMERA_FREE,                    // Camera free mode
//     CAMERA_ORBITAL,                 // Camera orbital, around target, zoom supported
//     CAMERA_FIRST_PERSON,            // Camera first person
//     CAMERA_THIRD_PERSON             // Camera third person
// } CameraMode;

// // Camera projection
// typedef enum {
//     CAMERA_PERSPECTIVE = 0,         // Perspective projection
//     CAMERA_ORTHOGRAPHIC             // Orthographic projection
// } CameraProjection;

// Camera, defines position/orientation in 3d space
// typedef struct Camera3D {
//     Vector3 position;       // Camera position
//     Vector3 target;         // Camera target it looks-at
//     Vector3 up;             // Camera up vector (rotation over its axis)
//     float fovy;             // Camera field-of-view aperture in Y (degrees) in perspective, used as near plane width in orthographic
//     int projection;         // Camera projection: CAMERA_PERSPECTIVE or CAMERA_ORTHOGRAPHIC
// } Camera3D;

// typedef Camera3D Camera;    // Camera type fallback, defaults to Camera3D

// Camera2D, defines position/orientation in 2d space
// typedef struct Camera2D {
//     Vector2 offset;         // Camera offset (displacement from target)
//     Vector2 target;         // Camera target (rotation and zoom origin)
//     float rotation;         // Camera rotation in degrees
//     float zoom;             // Camera zoom (scaling), should be 1.0f by default
// } Camera2D;
static auto rb_camera_initialize(VALUE self, VALUE rb_offset, VALUE rb_target, VALUE rb_rotation, VALUE rb_zoom) {
  auto *camera = get_camera(self);
  auto *offset = get_vec2(rb_offset);
  auto *target = get_vec2(rb_target);
  auto rotation = NUM2DBL(rb_rotation);
  auto zoom = NUM2DBL(rb_zoom);

  camera->offset = *offset;
  camera->target = *target;
  camera->rotation = rotation;
  camera->zoom = zoom;

  return self;
}

RB_CAMERA_GETTER_VEC2(rb_camera_get_offset, offset)
RB_CAMERA_GETTER_VEC2(rb_camera_get_target, target)
RB_CAMERA_GETTER(rb_camera_get_rotation, rotation)
RB_CAMERA_GETTER(rb_camera_get_zoom, zoom)
RB_CAMERA_SETTER_VEC2(rb_camera_set_offset, offset)
RB_CAMERA_SETTER_VEC2(rb_camera_set_target, target)
RB_CAMERA_SETTER(rb_camera_set_rotation, rotation)
RB_CAMERA_SETTER(rb_camera_set_zoom, zoom)

// RLAPI void BeginMode2D(Camera2D camera);                          // Begin 2D mode with custom camera (2D)
// RLAPI void EndMode2D(void);                                       // Ends 2D mode with custom camera
static auto rb_begin_mode_2d(VALUE self) {
  auto *camera = get_camera(self);

  rb_need_block();
  BeginMode2D(*camera);
  rb_yield(Qnil);
  EndMode2D();

  return Qnil;
}

extern "C" void Init_Camera() {
  rb_cCamera = rb_define_class_under(rb_mRL, "Camera", rb_cObject);
  rb_define_alloc_func(rb_cCamera, rb_object_alloc<Camera2D>);

  rb_define_method(rb_cCamera, "initialize", rb_camera_initialize, 4);

  rb_define_method(rb_cCamera, "offset", rb_camera_get_offset, 0);
  rb_define_method(rb_cCamera, "target", rb_camera_get_target, 0);
  rb_define_method(rb_cCamera, "rotation", rb_camera_get_rotation, 0);
  rb_define_method(rb_cCamera, "zoom", rb_camera_get_zoom, 0);

  rb_define_method(rb_cCamera, "offset=", rb_camera_set_offset, 1);
  rb_define_method(rb_cCamera, "target=", rb_camera_set_target, 1);
  rb_define_method(rb_cCamera, "rotation=", rb_camera_set_rotation, 1);
  rb_define_method(rb_cCamera, "zoom=", rb_camera_set_zoom, 1);

  rb_define_method(rb_cCamera, "world_to_screen", rb_get_world_to_screen_2d, 1);
  rb_define_method(rb_cCamera, "screen_to_world", rb_get_screen_to_world_2d, 1);
  rb_define_method(rb_cCamera, "begin", rb_begin_mode_2d, 0);
}
