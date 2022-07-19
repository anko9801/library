template <typename T>
class BIT {
  int N;
  vector<T> bit;
  BIT(int n) : N(n), bit(n + 1, 0) {}

  void add(int i, T x) {
    for (++i; i <= N; i += (i & -i)) bit[i] += x;
  }

  T sum(int i) {
    T res(0);
    for (++i; i > 0; i -= (i & -i)) res += bit[i];
    return res;
  }
  T sum(int l, int r) { return sum(r - 1) - sum(l - 1); }
  T all_sum() { return sum(N); }
};
