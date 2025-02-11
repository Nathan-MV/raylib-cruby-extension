#include <shader_bindings.h>

VALUE rb_cShader;

// // Shader management functions
// // NOTE: Shader functionality is not available on OpenGL 1.1
// RLAPI Shader LoadShader(const char *vsFileName, const char *fsFileName);   // Load shader from files and bind default locations
static auto rb_shader_initialize(int argc, VALUE *argv, VALUE self) {
  auto *shader = get_shader(self);

  if (argc == 2) {
    const char *vsFileName = NIL_P(argv[0]) ? nullptr : StringValueCStr(argv[0]);
    const char *fsFileName = NIL_P(argv[1]) ? nullptr : StringValueCStr(argv[1]);
    *shader = LoadShader(vsFileName, fsFileName);
  } else {
    rb_raise(rb_eArgError, "wrong number of arguments (given %d, expected 2 arguments)", argc);
  }

  return self;
}
// RLAPI Shader LoadShaderFromMemory(const char *vsCode, const char *fsCode); // Load shader from code strings and bind default locations
// RLAPI bool IsShaderValid(Shader shader);                                   // Check if a shader is ready
static auto rb_is_shader_ready(VALUE self) {
  auto *shader = get_shader(self);

  return IsShaderValid(*shader)? Qtrue : Qfalse;
}
// RLAPI int GetShaderLocation(Shader shader, const char *uniformName);       // Get shader uniform location
static auto rb_get_shader_location(VALUE self, VALUE rb_uniform_name) {
  auto *shader = get_shader(self);
  const char *uniformName = StringValueCStr(rb_uniform_name);

  int location = GetShaderLocation(*shader, uniformName);

  return INT2NUM(location);
}
// RLAPI int GetShaderLocationAttrib(Shader shader, const char *attribName);  // Get shader attribute location
static auto rb_get_shader_location_attrib(VALUE self, VALUE rb_attrib_name) {
  auto *shader = get_shader(self);
  const char *attribName = StringValueCStr(rb_attrib_name);

  int location = GetShaderLocationAttrib(*shader, attribName);

  return INT2NUM(location);
}
// RLAPI void SetShaderValue(Shader shader, int locIndex, const void *value, int uniformType);               // Set shader uniform value
static auto rb_set_shader_value(VALUE self, VALUE rb_loc_index, VALUE rb_value, VALUE rb_uniform_type) {
  auto *shader = get_shader(self);
  auto locIndex = NUM2INT(rb_loc_index);
  float value = NUM2DBL(rb_value);
  auto uniformType = NUM2INT(rb_uniform_type);

  SetShaderValue(*shader, locIndex, &value, uniformType);

  return self;
}
// RLAPI void SetShaderValueV(Shader shader, int locIndex, const void *value, int uniformType, int count);   // Set shader uniform value vector
static auto rb_set_shader_value_v(VALUE self, VALUE rb_loc_index, VALUE rb_value, VALUE rb_uniform_type, VALUE rb_count) {
  auto *shader = get_shader(self);
  auto locIndex = NUM2INT(rb_loc_index);
  float value = NUM2DBL(rb_value);
  auto uniformType = NUM2INT(rb_uniform_type);
  auto count = NUM2INT(rb_count);

  SetShaderValueV(*shader, locIndex, &value, uniformType, count);

  return self;
}
// RLAPI void SetShaderValueMatrix(Shader shader, int locIndex, Matrix mat);         // Set shader uniform value (matrix 4x4)
// RLAPI void SetShaderValueTexture(Shader shader, int locIndex, Texture2D texture); // Set shader uniform value for texture (sampler2d)
static auto rb_set_shader_value_texture(VALUE self, VALUE rb_loc_index, VALUE rb_texture) {
  auto *shader = get_shader(self);
  auto locIndex = NUM2INT(rb_loc_index);
  auto *texture = get_texture(rb_texture);

  SetShaderValueTexture(*shader, locIndex, *texture);

  return self;
}
// RLAPI void UnloadShader(Shader shader);                                    // Unload shader from GPU memory (VRAM)
static auto rb_unload_shader(VALUE self) {
  auto *shader = get_shader(self);

  UnloadShader(*shader);

  return self;
}

static auto rb_set_shader(VALUE self, VALUE rb_uniform_name, VALUE rb_value,
                          VALUE rb_uniform_type) {
  auto *shader = get_shader(self);
  const auto *uniformName = StringValueCStr(rb_uniform_name);
  auto location = GetShaderLocation(*shader, uniformName);

  // Allocate and populate values
  float *values = nullptr;
  long value_size = (TYPE(rb_value) == T_ARRAY) ? RARRAY_LEN(rb_value) : 1;
  values = (float *)malloc(sizeof(float) * value_size);

  if (TYPE(rb_value) == T_ARRAY) {
    for (long i = 0; i < value_size; ++i) {
      values[i] = NUM2DBL(rb_ary_entry(rb_value, i));
    }
  } else if (TYPE(rb_value) == T_FLOAT || TYPE(rb_value) == T_FIXNUM) {
    values[0] = NUM2DBL(rb_value);
  } else {
    free(values);  // Prevent memory leak before raising an exception
    rb_raise(rb_eTypeError, "Expected value to be an Array or a Float");
  }

  SetShaderValue(*shader, location, values, NUM2INT(rb_uniform_type));
  free(values);  // Clean up allocated memory
  return self;
}

// RLAPI void BeginShaderMode(Shader shader);                        // Begin custom shader drawing
// RLAPI void EndShaderMode(void);                                   // End custom shader drawing (use default shader)
static auto rb_begin_shader_mode(VALUE self) {
  auto *shader = get_shader(self);

  rb_need_block();
  BeginShaderMode(*shader);
  rb_yield(Qnil);
  EndShaderMode();

  return Qnil;
}

extern "C" void Init_Shader() {
  rb_cShader = rb_define_class_under(rb_mRL, "Shader", rb_cObject);
  rb_define_alloc_func(rb_cShader, rb_shader_alloc<Shader>);

  rb_define_method(rb_cShader, "initialize", rb_shader_initialize, -1);
  rb_define_method(rb_cShader, "ready?", rb_is_shader_ready, 0);
  rb_define_method(rb_cShader, "location", rb_get_shader_location, 1);
  rb_define_method(rb_cShader, "location_attrib", rb_get_shader_location_attrib, 1);
  rb_define_method(rb_cShader, "set_value", rb_set_shader_value, 3);
  rb_define_method(rb_cShader, "set_value_v", rb_set_shader_value_v, 4);
  rb_define_method(rb_cShader, "set_texture", rb_set_shader_value_texture, 2);
  rb_define_method(rb_cShader, "unload", rb_unload_shader, 0);
  rb_define_method(rb_cShader, "dispose", rb_unload_shader, 0);  // unload alias
  rb_define_method(rb_cShader, "begin", rb_begin_shader_mode, 0);

  rb_define_method(rb_cShader, "set", rb_set_shader, 3);

  // Shader location index
  // Shader location: vertex attribute: position
  rb_define_const(rb_mKernel, "LOC_VERTEX_POSITION", INT2NUM(0));
  // Shader location: vertex attribute: texcoord01
  rb_define_const(rb_mKernel, "LOC_VERTEX_TEXCOORD01", INT2NUM(1));
  // Shader location: vertex attribute: texcoord02
  rb_define_const(rb_mKernel, "LOC_VERTEX_TEXCOORD02", INT2NUM(2));
  // Shader location: vertex attribute: normal
  rb_define_const(rb_mKernel, "LOC_VERTEX_NORMAL", INT2NUM(3));
  // Shader location: vertex attribute: tangent
  rb_define_const(rb_mKernel, "LOC_VERTEX_TANGENT", INT2NUM(4));
  // Shader location: vertex attribute: color
  rb_define_const(rb_mKernel, "LOC_VERTEX_COLOR", INT2NUM(5));
  // Shader location: matrix uniform: model-view-projection
  rb_define_const(rb_mKernel, "LOC_MATRIX_MVP", INT2NUM(6));
  // Shader location: matrix uniform: view (camera transform)
  rb_define_const(rb_mKernel, "LOC_MATRIX_VIEW", INT2NUM(7));
  // Shader location: matrix uniform: projection
  rb_define_const(rb_mKernel, "LOC_MATRIX_PROJECTION", INT2NUM(8));
  // Shader location: matrix uniform: model (transform)
  rb_define_const(rb_mKernel, "LOC_MATRIX_MODEL", INT2NUM(9));
  // Shader location: matrix uniform: normal
  rb_define_const(rb_mKernel, "LOC_MATRIX_NORMAL", INT2NUM(10));
  // Shader location: vector uniform: view
  rb_define_const(rb_mKernel, "LOC_VECTOR_VIEW", INT2NUM(11));
  // Shader location: vector uniform: diffuse color
  rb_define_const(rb_mKernel, "LOC_COLOR_DIFFUSE", INT2NUM(12));
  // Shader location: vector uniform: specular color
  rb_define_const(rb_mKernel, "LOC_COLOR_SPECULAR", INT2NUM(13));
  // Shader location: vector uniform: ambient color
  rb_define_const(rb_mKernel, "LOC_COLOR_AMBIENT", INT2NUM(14));
  // Shader location: sampler2d texture: albedo (same as: SHADER_LOC_MAP_DIFFUSE)
  rb_define_const(rb_mKernel, "LOC_MAP_ALBEDO", INT2NUM(15));
  rb_define_const(rb_mKernel, "LOC_MAP_DIFFUSE", INT2NUM(15));
  // Shader location: sampler2d texture: metalness (same as: SHADER_LOC_MAP_SPECULAR)
  rb_define_const(rb_mKernel, "LOC_MAP_METALNESS", INT2NUM(16));
  rb_define_const(rb_mKernel, "LOC_MAP_SPECULAR", INT2NUM(16));
  // Shader location: sampler2d texture: normal
  rb_define_const(rb_mKernel, "LOC_MAP_NORMAL", INT2NUM(17));
  // Shader location: sampler2d texture: roughness
  rb_define_const(rb_mKernel, "LOC_MAP_ROUGHNESS", INT2NUM(18));
  // Shader location: sampler2d texture: occlusion
  rb_define_const(rb_mKernel, "LOC_MAP_OCCLUSION", INT2NUM(19));
  // Shader location: sampler2d texture: emission
  rb_define_const(rb_mKernel, "LOC_MAP_EMISSION", INT2NUM(20));
  // Shader location: sampler2d texture: height
  rb_define_const(rb_mKernel, "LOC_MAP_HEIGHT", INT2NUM(21));
  // Shader location: samplerCube texture: cubemap
  rb_define_const(rb_mKernel, "LOC_MAP_CUBEMAP", INT2NUM(22));
  // Shader location: samplerCube texture: irradiance
  rb_define_const(rb_mKernel, "LOC_MAP_IRRADIANCE", INT2NUM(23));
  // Shader location: samplerCube texture: prefilter
  rb_define_const(rb_mKernel, "LOC_MAP_PREFILTER", INT2NUM(24));
  // Shader location: sampler2d texture: brdf
  rb_define_const(rb_mKernel, "LOC_MAP_BRDF", INT2NUM(25));

  // Shader uniform data type
  // Shader uniform type: float
  rb_define_const(rb_mKernel, "UNIFORM_FLOAT", INT2NUM(0));
  // Shader uniform type: vec2 (2 float)
  rb_define_const(rb_mKernel, "UNIFORM_VEC2", INT2NUM(1));
  // Shader uniform type: vec3 (3 float)
  rb_define_const(rb_mKernel, "UNIFORM_VEC3", INT2NUM(2));
  // Shader uniform type: vec4 (4 float)
  rb_define_const(rb_mKernel, "UNIFORM_VEC4", INT2NUM(3));
  // Shader uniform type: int
  rb_define_const(rb_mKernel, "UNIFORM_INT", INT2NUM(4));
  // Shader uniform type: ivec2 (2 int)
  rb_define_const(rb_mKernel, "UNIFORM_IVEC2", INT2NUM(5));
  // Shader uniform type: ivec3 (3 int)
  rb_define_const(rb_mKernel, "UNIFORM_IVEC3", INT2NUM(6));
  // Shader uniform type: ivec4 (4 int)
  rb_define_const(rb_mKernel, "UNIFORM_IVEC4", INT2NUM(7));
  // Shader uniform type: sampler2d
  rb_define_const(rb_mKernel, "UNIFORM_SAMPLER2D", INT2NUM(8));

  // Shader attribute data types
  // Shader attribute type: float
  rb_define_const(rb_mKernel, "ATTRIB_FLOAT", INT2NUM(0));
  // Shader attribute type: vec2 (2 float)
  rb_define_const(rb_mKernel, "ATTRIB_VEC2", INT2NUM(1));
  // Shader attribute type: vec3 (3 float)
  rb_define_const(rb_mKernel, "ATTRIB_VEC3", INT2NUM(2));
  // Shader attribute type: vec4 (4 float)
  rb_define_const(rb_mKernel, "ATTRIB_VEC4", INT2NUM(3));
}
