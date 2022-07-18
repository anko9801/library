#include <vector>

template <typename T>
std::vector<std::pair<T, int>> factors(T N) {
  std::vector<std::pair<T, int>> res;
  for (T a = 2; a * a <= N; ++a) {
    if (N % a != 0)
      continue;
    int e = 0;
    while (N % a == 0) {
      ++e;
      N /= a;
    }
    res.push_back({a, e});
  }
  if (N != 1)
    res.push_back({N, 1});
  return res;
}