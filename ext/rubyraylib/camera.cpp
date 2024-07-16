//------------------------------------------------------------------------------------
// Camera System Functions (Module: rcamera)
//------------------------------------------------------------------------------------
// RLAPI void UpdateCamera(Camera *camera, int mode);      // Update camera position for selected mode
// RLAPI void UpdateCameraPro(Camera *camera, Vector3 movement, Vector3 rotation, float zoom); // Update camera movement/rotation

// Screen-space-related functions
// #define GetMouseRay GetScreenToWorldRay     // Compatibility hack for previous raylib versions
// RLAPI Ray GetScreenToWorldRay(Vector2 position, Camera camera);         // Get a ray trace from screen position (i.e mouse)
// RLAPI Ray GetScreenToWorldRayEx(Vector2 position, Camera camera, int width, int height); // Get a ray trace from screen position (i.e mouse) in a viewport
// RLAPI Vector2 GetWorldToScreen(Vector3 position, Camera camera);        // Get the screen space position for a 3d world space position
// RLAPI Vector2 GetWorldToScreenEx(Vector3 position, Camera camera, int width, int height); // Get size position for a 3d world space position
// RLAPI Vector2 GetWorldToScreen2D(Vector2 position, Camera2D camera);    // Get the screen space position for a 2d camera world space position
// RLAPI Vector2 GetScreenToWorld2D(Vector2 position, Camera2D camera);    // Get the world space position for a 2d camera screen space position
// RLAPI Matrix GetCameraMatrix(Camera camera);                            // Get camera transform matrix (view matrix)
// RLAPI Matrix GetCameraMatrix2D(Camera2D camera);                        // Get camera 2d transform matrix

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
