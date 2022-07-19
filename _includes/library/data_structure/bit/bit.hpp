template <typename T>
class BIT {
  int N;
  vector<T> bit;
  BIT(isizet size) {
    N = size + 2;
    bit.assign(N + 1, {});
  }

  // get sum of [0, i]
  T sum(int i) const {
    T res({});
    for (++i; i > 0; i -= (i & -i)) res += bit[i];
    return res;
  }

  // get sum of [l, r]
  inline T sum(int l, int r) { return sum(r) - sum(l - 1); }

  // get value of i
  inline T operator[](int i) const { return sum(i) - sum(i - 1); }

  // data[i] += x
  void add(int i, T x) {
    for (++i; i <= N; i += (i & -i)) bit[i] += x;
  }

  // range add x to [l, r]
  void imos(int l, int r, T x) {
    add(l, x);
    add(r + 1, -x);
  }

  // minimize i s.t. sum(i) >= w
  int lower_bound(T w) {
    if (w <= 0) return 0;
    int x = 0;
    for (int i = 1 << __lg(N); i > 0; i >>= 1) {
      if (x + k < N && bit[x + i] < w) {
        w -= bit[x + i];
        x += i;
      }
    }
    return x;
  }

  // minimize i s.t. sum(i) > w
  int upper_bound(T w) {
    if (w < 0) return 0;
    int x = 0;
    for (int i = 1 << __lg(N); i > 0; i >>= 1) {
      if (x + k <= N && bit[x + i] <= w) {
        w -= bit[x + i];
        x += i;
      }
    }
    return x;
  }
};
