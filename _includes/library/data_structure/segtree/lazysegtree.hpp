#include <algorithm>
#include <cassert>
#include <iostream>
#include <vector>

namespace internal {
int ceil_pow2(int n) {
  int x = 0;
  while ((1U << x) < (unsigned int)(n))
    x++;
  return x;
}

} // namespace internal

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
    for (int i = size - 1; i >= 1; i--)
      update(i);
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
