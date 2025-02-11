#include <kernel_bindings.h>

// Random values generation functions
// RLAPI void SetRandomSeed(unsigned int seed);                      // Set the seed for the random number generator
// RLAPI int GetRandomValue(int min, int max);                       // Get a random value between min and max (both included)
// RLAPI int *LoadRandomSequence(unsigned int count, int min, int max); // Load random values sequence, no values repeated
// RLAPI void UnloadRandomSequence(int *sequence);                   // Unload random values sequence

// Compression/Encoding functionality
// RLAPI unsigned char *CompressData(const unsigned char *data, int dataSize, int *compDataSize);        // Compress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI unsigned char *DecompressData(const unsigned char *compData, int compDataSize, int *dataSize);  // Decompress data (DEFLATE algorithm), memory must be MemFree()
// RLAPI char *EncodeDataBase64(const unsigned char *data, int dataSize, int *outputSize);               // Encode data to Base64 string, memory must be MemFree()
// RLAPI unsigned char *DecodeDataBase64(const unsigned char *data, int *outputSize);                    // Decode Base64 string data, memory must be MemFree()
// RLAPI unsigned int ComputeCRC32(unsigned char* data, int dataSize);  // Compute CRC32 hash code
// RLAPI unsigned int* ComputeMD5(unsigned char* data, int dataSize);  // Compute MD5 hash code, returns static int[4] (16 bytes)
// RLAPI unsigned int *ComputeSHA1(unsigned char *data, int dataSize);      // Compute SHA1 hash code, returns static int[5] (20 bytes)

RB_METHOD_INT_ARG_INT_INT(rb_get_random_value, GetRandomValue)
//RB_METHOD_INT_ARG(rb_fibonacci, fibonacci)

static VALUE rb_load_csv(int argc, VALUE* argv, VALUE self) {
  VALUE str;
  rb_scan_args(argc, argv, "1", &str);
  SafeStringValue(str);

  const char* csv_data = RSTRING_PTR(str);
  long csv_length = RSTRING_LEN(str);
  VALUE ret = rb_ary_new();

  try {
    rapidcsv::Document doc(std::string(csv_data, csv_length), rapidcsv::LabelParams(-1, -1),
                           rapidcsv::SeparatorParams(',', false, true, true, true));
    int row_count = doc.GetRowCount();
    int col_count = doc.GetColumnCount();
    rb_ary_resize(ret, row_count);
    for (int r = 0; r < row_count; r++) {
      VALUE col = rb_ary_new2(col_count);
      for (int c = 0; c < col_count; c++) {
        const std::string& cell = doc.GetCell<std::string>(c, r);
        VALUE rb_str = rb_utf8_str_new(cell.c_str(), cell.size());
        rb_ary_store(col, c, rb_str);
      }
      rb_ary_store(ret, r, col);
    }
  } catch (const std::exception& e) {
    rb_raise(rb_eRuntimeError, "Failed to parse CSV: %s", e.what());
  }

  return ret;
}

// Wrapper for the levenshtein_distance function
// VALUE rb_levenshtein_distance(VALUE self, VALUE str1, VALUE str2) {
//   std::string s1 = StringValueCStr(str1);
//   std::string s2 = StringValueCStr(str2);
//   int result = levenshtein_distance(s1, s2);
//   return INT2NUM(result);
// }

extern "C" void Init_Kernel() {
  rb_define_module_function(rb_mKernel, "random", rb_get_random_value, 2);

  //rb_define_module_function(rb_mKernel, "fib", rb_fibonacci, 1);
  // rb_define_module_function(rb_mKernel, "levenshtein_distance", rb_levenshtein_distance, 2);
  rb_define_module_function(rb_mKernel, "load_csv", rb_load_csv, -1);
}
