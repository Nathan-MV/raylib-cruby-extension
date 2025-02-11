#include "kernel.h"

// Get a random float between min and max included
float GetRandomFloat(float min, float max) {
  auto value = min + ((float)GetRandomValue(0, RAND_MAX) / (float)RAND_MAX) * (max - min);

  return value;
}

int fibonacci(int number) {
  if (number <= 1) return number;

  return fibonacci(number - 1) + fibonacci(number - 2);
}

// Levenshtein distance function
// int levenshtein_distance(const std::string& str1, const std::string& str2) {
//   uint16_t n = str1.length();
//   uint16_t m = str2.length();
//   if (n == 0) return m;
//   if (m == 0) return n;

//   std::vector<uint16_t> prev(m + 1);
//   std::vector<uint16_t> curr(m + 1);

//   for (uint16_t j = 0; j <= m; j++) prev[j] = j;

//   for (uint16_t i = 1; i <= n; i++) {
//     curr[0] = i;
//     for (uint16_t j = 1; j <= m; j++) {
//       uint16_t cost = (str1[i - 1] == str2[j - 1]) ? 0 : 1;
//       curr[j] = std::min({curr[j - 1] + 1, prev[j] + 1, prev[j - 1] + cost});
//     }
//     std::swap(prev, curr);
//   }

//   return prev[m];
// }

