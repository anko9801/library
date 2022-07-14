template <typename T> class BIT {
  int N;
  vector<T> bit;
  BIT(int n) : N(n), bit(n + 1, 0) {}

  void add(int i, T x) {
    for (int idx = i; idx <= N; idx += (idx & -idx))
      bit[idx] += x;
  }

  T sum(int i) {
    T res(0);
    for (int idx = i; idx >= 0; idx -= (idx & -idx))
      res += bit[idx];
    return res;
  }
  T sum(int l, int r) { return sum(r - 1) - sum(l - 1); }
  T all_sum() { return prod(N); }
};