#include "kernel.hpp"
#include "ruby_values.hpp"

// Random values generation functions
// RLAPI void SetRandomSeed(unsigned int seed);                      // Set the seed for the random number generator
// RLAPI int GetRandomValue(int min, int max);                       // Get a random value between min and max (both included)
RB_METHOD_INT_ARG_2(rb_get_random_value, GetRandomValue)
// RLAPI int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
// RLAPI void UnloadRandomSequence(int *sequence);                   // Unload random values sequence

// Compression/Encoding functionality
// RLAPI unsigned char *CompressData(const unsigned char *data, int dataSize, int *compDataSize);        // Compress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI unsigned char *DecompressData(const unsigned char *compData, int compDataSize, int *dataSize);  // Decompress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI char *EncodeDataBase64(const unsigned char *data, int dataSize, int *outputSize);               // Encode data to Base64 string, memory must be MemFree()
// RLAPI unsigned char *DecodeDataBase64(const unsigned char *data, int *outputSize);                    // Decode Base64 string data, memory must be MemFree()

// Get a random float between min and max included
float GetRandomFloat(float min, float max)
{
  float value = min + ((float)GetRandomValue(0, RAND_MAX) / (float)RAND_MAX) * (max - min);

  return value;
}
RB_METHOD_ARG_FLOAT_2(rb_get_random_float, GetRandomFloat)

static int fibonacci(int n) {
  if (n <= 1)
    return n;

  return fibonacci(n - 1) + fibonacci(n - 2);
}
RB_METHOD_INT_ARG(rb_fibonacci, fibonacci)

extern "C" void initializeKernel() {
  rb_define_module_function(rb_mKernel, "random", rb_get_random_value, 2);

  rb_define_module_function(rb_mKernel, "random_f", rb_get_random_float, 2);
  rb_define_module_function(rb_mKernel, "fib", rb_fibonacci, 1);
}
