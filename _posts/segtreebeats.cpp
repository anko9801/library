
#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>
using namespace std;

using ll = long long;
#define N 10003

class SegmentTree {
  const ll inf = 1e18;
  int n, n0;
  ll max_v[4 * N], smax_v[4 * N];
  ll sum[4 * N], max_c[4 * N];

  void update_node_max(int k, ll x) {
    sum[k] += (x - max_v[k]) * max_c[k];
    max_v[k] = x;
  }

  void push(int k) {
    if (max_v[k] < max_v[2 * k + 1]) {
      update_node_max(2 * k + 1, max_v[k]);
    }
    if (max_v[k] < max_v[2 * k + 2]) {
      update_node_max(2 * k + 2, max_v[k]);
    }
  }

  void update(int k) {
    sum[k] = sum[2 * k + 1] + sum[2 * k + 2];

    if (max_v[2 * k + 1] < max_v[2 * k + 2]) {
      max_v[k] = max_v[2 * k + 2];
      max_c[k] = max_c[2 * k + 2];
      smax_v[k] = max(max_v[2 * k + 1], smax_v[2 * k + 2]);
    } else if (max_v[2 * k + 1] > max_v[2 * k + 2]) {
      max_v[k] = max_v[2 * k + 1];
      max_c[k] = max_c[2 * k + 1];
      smax_v[k] = max(smax_v[2 * k + 1], max_v[2 * k + 2]);
    } else {
      max_v[k] = max_v[2 * k + 1];
      max_c[k] = max_c[2 * k + 1] + max_c[2 * k + 2];
      smax_v[k] = max(smax_v[2 * k + 1], smax_v[2 * k + 2]);
    }
  }

  void _update_min(ll x, int a, int b, int k, int l, int r) {
    if (b <= l || r <= a || max_v[k] <= x) {
      return;
    }
    if (a <= l && r <= b && smax_v[k] < x) {
      update_node_max(k, x);
      return;
    }

    push(k);
    _update_min(x, a, b, 2 * k + 1, l, (l + r) / 2);
    _update_min(x, a, b, 2 * k + 2, (l + r) / 2, r);
    update(k);
  }

  ll _query_max(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) {
      return 0;
    }
    if (a <= l && r <= b) {
      return max_v[k];
    }
    push(k);
    ll lv = _query_max(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = _query_max(a, b, 2 * k + 2, (l + r) / 2, r);
    return max(lv, rv);
  }

  ll _query_sum(int a, int b, int k, int l, int r) {
    if (b <= l || r <= a) {
      return 0;
    }
    if (a <= l && r <= b) {
      return sum[k];
    }
    push(k);
    ll lv = _query_sum(a, b, 2 * k + 1, l, (l + r) / 2);
    ll rv = _query_sum(a, b, 2 * k + 2, (l + r) / 2, r);
    return lv + rv;
  }

public:
  SegmentTree(int n) { SegmentTree(n, nullptr); }

  SegmentTree(int n, ll *a) : n(n) {
    n0 = 1;
    while (n0 < n)
      n0 <<= 1;

    for (int i = 0; i < n; ++i) {
      max_v[n0 - 1 + i] = sum[n0 - 1 + i] = (a != nullptr ? a[i] : 0);
      smax_v[n0 - 1 + i] = -inf;
      max_c[n0 - 1 + i] = 1;
    }

    for (int i = n; i < n0; ++i) {
      max_v[n0 - 1 + i] = smax_v[n0 - 1 + i] = -inf;
      sum[n0 - 1 + i] = max_c[n0 - 1 + i] = 0;
    }
    for (int i = n0 - 2; i >= 0; i--)
      update(i);
  }

  // range minimize query
  void update_min(int a, int b, ll x) { return _update_min(x, a, b, 0, 0, n0); }

  // range maximum query
  ll query_max(int a, int b) { return _query_max(a, b, 0, 0, n0); }

  // range sum query
  ll query_sum(int a, int b) { return _query_sum(a, b, 0, 0, n0); }
};

template <class S, S (*op)(S, S), S (*e)(), class F, S (*mapping)(F, S),
          F (*composition)(F, F), F (*id)()>
struct lazy_segtree {
private:
  int _n, size, log;
  std::vector<S> node;
  std::vector<F> lazy;

public:
  lazy_segtree() : lazy_segtree(0) {}
  explicit lazy_segtree(int n) : lazy_segtree(std::vector<S>(n, e())) {}
  explicit lazy_segtree(const std::vector<S> &v) : _n(int(v.size())) {
    log = internal::ceil_pow2(_n);
    size = 1 << log;
    node = std::vector<S>(2 * size, e());
    lazy = std::vector<F>(size, id());
    // セグ木の初期化
    // 最下層: size + k
    // 親 k >> 1
    // 子 2*k, 2*k + 1
    for (int i = 0; i < _n; i++)
      node[size + i] = v[i];
    for (int i = size - 1; i >= 1; i--) {
      update(i);
    }
  }

  // a[p] = x : O(logN)
  void set(int p, S x) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--)
      push(p >> i);
    node[p] = x;
    for (int i = 1; i <= log; i++)
      update(p >> i);
  }

  // a[p] : O(1)
  S get(int p) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--)
      push(p >> i);
    return node[p];
  }

  // op(a[l, r)) をモノイドの性質を満たしていると仮定して計算 : O(logN)
  S prod(int l, int r) {
    assert(0 <= l && l <= r && r <= _n);
    if (l == r)
      return e();

    l += size;
    r += size;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l)
        push(l >> i);
      if (((r >> i) << i) != r)
        push((r - 1) >> i);
    }

    S sml = e(), smr = e();
    while (l < r) {
      if (l & 1)
        sml = op(sml, node[l++]);
      if (r & 1)
        smr = op(node[--r], smr);
      l >>= 1;
      r >>= 1;
    }

    return op(sml, smr);
  }

  // op(a[0, n)) : O(logN)
  S all_prod() { return node[1]; }

  // a[p] = f(a[p]) : O(logN)
  void apply(int p, F f) {
    assert(0 <= p && p < _n);
    p += size;
    for (int i = log; i >= 1; i--)
      push(p >> i);
    node[p] = mapping(f, node[p]);
    for (int i = 1; i <= log; i++)
      update(p >> i);
  }
  // a[i] = f(a[i]) in [l, r) : O(logN)
  void apply(int l, int r, F f) {
    assert(0 <= l && l <= r && r <= _n);
    if (l == r)
      return;

    l += size;
    r += size;

    for (int i = log; i >= 1; i--) {
      if (((l >> i) << i) != l)
        push(l >> i);
      if (((r >> i) << i) != r)
        push((r - 1) >> i);
    }

    {
      int l2 = l, r2 = r;
      while (l < r) {
        if (l & 1)
          all_apply(l++, f);
        if (r & 1)
          all_apply(--r, f);
        l >>= 1;
        r >>= 1;
      }
      l = l2;
      r = r2;
    }

    for (int i = 1; i <= log; i++) {
      if (((l >> i) << i) != l)
        update(l >> i);
      if (((r >> i) << i) != r)
        update((r - 1) >> i);
    }
  }

  // 二分探索
  // r where g(op(a[l, r))) = true & g(op(a[l, r])) = false : O(logN)
  template <bool (*g)(S)> int max_right(int l) {
    return max_right(l, [](S x) { return g(x); });
  }
  template <class G> int max_right(int l, G g) {
    assert(0 <= l && l <= _n);
    assert(g(e()));
    if (l == _n)
      return _n;
    l += size;
    for (int i = log; i >= 1; i--)
      push(l >> i);
    S sm = e();
    do {
      while (l % 2 == 0)
        l >>= 1;
      if (!g(op(sm, node[l]))) {
        while (l < size) {
          push(l);
          l = (2 * l);
          if (g(op(sm, node[l]))) {
            sm = op(sm, node[l]);
            l++;
          }
        }
        return l - size;
      }
      sm = op(sm, node[l]);
      l++;
    } while ((l & -l) != l);
    return _n;
  }

  // 二分探索
  // l where g(op(a[l, r))) = true & g(op(a[l-1, r))) = false
  template <bool (*g)(S)> int min_left(int r) {
    return min_left(r, [](S x) { return g(x); });
  }
  template <class G> int min_left(int r, G g) {
    assert(0 <= r && r <= _n);
    assert(g(e()));
    if (r == 0)
      return 0;
    r += size;
    for (int i = log; i >= 1; i--)
      push((r - 1) >> i);
    S sm = e();
    do {
      r--;
      while (r > 1 && (r % 2))
        r >>= 1;
      if (!g(op(node[r], sm))) {
        while (r < size) {
          push(r);
          r = (2 * r + 1);
          if (g(op(node[r], sm))) {
            sm = op(node[r], sm);
            r--;
          }
        }
        return r + 1 - size;
      }
      sm = op(node[r], sm);
    } while ((r & -r) != r);
    return 0;
  }

private:
  // node[k]の更新
  void update(int k) { node[k] = op(node[2 * k], node[2 * k + 1]); }
  // nodeの更新
  void all_apply(int k, F f) {
    node[k] = mapping(f, node[k]);
    if (k < size)
      lazy[k] = composition(f, lazy[k]);
  }

  // 遅延評価
  void push(int k) {
    all_apply(2 * k, lazy[k]);
    all_apply(2 * k + 1, lazy[k]);
    lazy[k] = id();
  }
};
