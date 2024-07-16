// // Shader management functions
// // NOTE: Shader functionality is not available on OpenGL 1.1
// RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);   // Load shader from files and bind default locations
// RLAPI Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode); // Load shader from code strings and bind default locations
// RLAPI bool IsShaderReady(Shader shader);                                   // Check if a shader is ready
// RLAPI int GetShaderLocation(Shader shader, const char *uniformName);       // Get shader uniform location
// RLAPI int GetShaderLocationAttrib(Shader shader, const char *attribName);  // Get shader attribute location
// RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
// RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
// RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);         // Set shader uniform value (matrix 4x4)
// RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value for texture (sampler2d)
// RLAPI void UnloadShader(Shader shader);                                    // Unload shader from GPU memory (VRAM)

// Shader location index
// typedef enum {
//     SHADER_LOC_VERTEX_POSITION = 0, // Shader location: vertex attribute: position
//     SHADER_LOC_VERTEX_TEXCOORD01,   // Shader location: vertex attribute: texcoord01
//     SHADER_LOC_VERTEX_TEXCOORD02,   // Shader location: vertex attribute: texcoord02
//     SHADER_LOC_VERTEX_NORMAL,       // Shader location: vertex attribute: normal
//     SHADER_LOC_VERTEX_TANGENT,      // Shader location: vertex attribute: tangent
//     SHADER_LOC_VERTEX_COLOR,        // Shader location: vertex attribute: color
//     SHADER_LOC_MATRIX_MVP,          // Shader location: matrix uniform: model-view-projection
//     SHADER_LOC_MATRIX_VIEW,         // Shader location: matrix uniform: view (camera transform)
//     SHADER_LOC_MATRIX_PROJECTION,   // Shader location: matrix uniform: projection
//     SHADER_LOC_MATRIX_MODEL,        // Shader location: matrix uniform: model (transform)
//     SHADER_LOC_MATRIX_NORMAL,       // Shader location: matrix uniform: normal
//     SHADER_LOC_VECTOR_VIEW,         // Shader location: vector uniform: view
//     SHADER_LOC_COLOR_DIFFUSE,       // Shader location: vector uniform: diffuse color
//     SHADER_LOC_COLOR_SPECULAR,      // Shader location: vector uniform: specular color
//     SHADER_LOC_COLOR_AMBIENT,       // Shader location: vector uniform: ambient color
//     SHADER_LOC_MAP_ALBEDO,          // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
//     SHADER_LOC_MAP_METALNESS,       // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
//     SHADER_LOC_MAP_NORMAL,          // Shader location: sampler2d texture: normal
//     SHADER_LOC_MAP_ROUGHNESS,       // Shader location: sampler2d texture: roughness
//     SHADER_LOC_MAP_OCCLUSION,       // Shader location: sampler2d texture: occlusion
//     SHADER_LOC_MAP_EMISSION,        // Shader location: sampler2d texture: emission
//     SHADER_LOC_MAP_HEIGHT,          // Shader location: sampler2d texture: height
//     SHADER_LOC_MAP_CUBEMAP,         // Shader location: samplerCube texture: cubemap
//     SHADER_LOC_MAP_IRRADIANCE,      // Shader location: samplerCube texture: irradiance
//     SHADER_LOC_MAP_PREFILTER,       // Shader location: samplerCube texture: prefilter
//     SHADER_LOC_MAP_BRDF             // Shader location: sampler2d texture: brdf
// } ShaderLocationIndex;

// #define SHADER_LOC_MAP_DIFFUSE      SHADER_LOC_MAP_ALBEDO
// #define SHADER_LOC_MAP_SPECULAR     SHADER_LOC_MAP_METALNESS

// Shader uniform data type
// typedef enum {
//     SHADER_UNIFORM_FLOAT = 0,       // Shader uniform type: float
//     SHADER_UNIFORM_VEC2,            // Shader uniform type: vec2 (2 float)
//     SHADER_UNIFORM_VEC3,            // Shader uniform type: vec3 (3 float)
//     SHADER_UNIFORM_VEC4,            // Shader uniform type: vec4 (4 float)
//     SHADER_UNIFORM_INT,             // Shader uniform type: int
//     SHADER_UNIFORM_IVEC2,           // Shader uniform type: ivec2 (2 int)
//     SHADER_UNIFORM_IVEC3,           // Shader uniform type: ivec3 (3 int)
//     SHADER_UNIFORM_IVEC4,           // Shader uniform type: ivec4 (4 int)
//     SHADER_UNIFORM_SAMPLER2D        // Shader uniform type: sampler2d
// } ShaderUniformDataType;

// Shader attribute data types
// typedef enum {
//     SHADER_ATTRIB_FLOAT = 0,        // Shader attribute type: float
//     SHADER_ATTRIB_VEC2,             // Shader attribute type: vec2 (2 float)
//     SHADER_ATTRIB_VEC3,             // Shader attribute type: vec3 (3 float)
//     SHADER_ATTRIB_VEC4              // Shader attribute type: vec4 (4 float)
// } ShaderAttributeDataType;
