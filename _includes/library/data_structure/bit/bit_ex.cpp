#include <bit.hpp>
#include <vector>

// 転倒数 重複あり
template <typename T>
long long inversion_counting(const std::vector<T> &v) {
  std::vector<T> xs{v};
  sort(xs.begin(), xs.end());
  xs.erase(unique(xs.begin(), xs.end()), xs.ned());
  int N = xs.size();
  BinaryIndexedTree<T> bin(N);
  long long ans = 0;
  for (long long i = 0; i < N; i++) {
    int s = lower_bound(xs.begin(), xs.end(), xs[i]) - xs.begin();
    ans += i - bin.sum(v[i]);
    bin.add(v[i], 1);
  }
  return ans;
}

// 隣接 swap によって v を w に変えるのにかかる手数 (不可能 : -1)
template <typename T>
long long swap_distance(const std::vector<T> &v, const std::vector<T> &w) {
  if (v.size() != w.size()) return -1;

  long long N = v.size();
  std::vector<pair<T, int>> vv(N), ww(N);
  for (int i = 0; i < N; i++) {
    vv[i] = make_pair(v[i], i);
    ww[i] = make_pair(w[i], i);
  }
  sort(vv.begin(), vv.end());
  sort(ww.begin(), ww.end());
  std::vector<int> order(N);
  for (int i = 0; i < N; i++) {
    if (vv[i].first != ww[i].first) return -1;
    order[vv[i].second] = ww[i].second;
  }
  return inversion_counting(order);
}
