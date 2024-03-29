
/**
 * @brief 多次元 vector の作成
 * @author えびちゃん
 */
#include <bits/stdc++.h>
using namespace std;
using ll = long long;

namespace detail {
template <typename Tp, size_t Nb>
auto make_vector(std::vector<size_t> &sizes, Tp const &x) {
  if constexpr (Nb == 1) {
    return std::vector(sizes[0], x);
  } else {
    size_t size = sizes[Nb - 1];
    sizes.pop_back();
    return std::vector(size, make_vector<Tp, Nb - 1>(sizes, x));
  }
}
} // namespace detail

template <typename Tp, size_t Nb>
auto make_vector(size_t const (&sizes)[Nb], Tp const &x = Tp()) {
  std::vector<size_t> s(Nb);
  for (size_t i = 0; i < Nb; ++i)
    s[i] = sizes[Nb - i - 1];
  return detail::make_vector<Tp, Nb>(s, x);
}