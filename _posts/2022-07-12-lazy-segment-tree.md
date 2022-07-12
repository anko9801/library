---
title: "遅延セグメント木"
permalink: /posts/lazy-segment-tree
writer: anko9801
layout: library
---

## 説明

## 計算量

## 実装

```cpp
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
```

## 使用例

```cpp
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

#include <bits/stdc++.h>
// #include <atcoder/all>
using namespace std;
// using namespace atcoder;
using ll = long long;
using ld = long double;
using uint = unsigned;
using ull = unsigned long long;
using u64 = uint_fast64_t;
using pll = pair<ll, ll>;
using pdd = pair<ld, ld>;
using C = complex<double>;
template <class T> using pq = priority_queue<T, vector<T>, greater<T>>;

const int IINF = 0x1fffffff;
const ll LINF = 0x1fffffffffffffff;
const ll INF = 0x1fffffffffffffff;
const ll MINF = 0x7fffffffffff;
const ll MOD = 1000000007;
const ll MODD = 998244353;
const ld DINF = numeric_limits<ld>::infinity();
const ld EPS = 1e-9;
const ld PI = 3.1415926535897932;
const ll dx[] = {0, 1, 0, -1, 1, -1, 1, -1};
const ll dy[] = {1, 0, -1, 0, 1, 1, -1, -1};

#define overload4(_1, _2, _3, _4, name, ...) name
#define overload3(_1, _2, _3, name, ...) name
#define rep1(n) for (ll i = 0; i < n; ++i)
#define rep2(i, n) for (ll i = 0; i < n; ++i)
#define rep3(i, a, b) for (ll i = a; i < b; ++i)
#define rep4(i, a, b, c) for (ll i = a; i < b; i += c)
#define rep(...) overload4(__VA_ARGS__, rep4, rep3, rep2, rep1)(__VA_ARGS__)
#define rrep1(n) for (ll i = n; i--;)
#define rrep2(i, n) for (ll i = n; i--;)
#define rrep3(i, a, b) for (ll i = b; i-- > (a);)
#define rrep4(i, a, b, c)                                                      \
  for (ll i = (a) + ((b) - (a)-1) / (c) * (c); i >= (a); i -= c)
#define rrep(...)                                                              \
  overload4(__VA_ARGS__, rrep4, rrep3, rrep2, rrep1)(__VA_ARGS__)
#define each1(i, a) for (auto &&i : a)
#define each2(x, y, a) for (auto &&[x, y] : a)
#define each3(x, y, z, a) for (auto &&[x, y, z] : a)
#define each(...) overload4(__VA_ARGS__, each3, each2, each1)(__VA_ARGS__)
#define all1(i) begin(i), end(i)
#define all2(i, a) begin(i), begin(i) + a
#define all3(i, a, b) begin(i) + a, begin(i) + b
#define all(...) overload3(__VA_ARGS__, all3, all2, all1)(__VA_ARGS__)
#define rall1(i) (i).rbegin(), (i).rend()
#define rall2(i, k) (i).rbegin(), (i).rbegin() + k
#define rall3(i, a, b) (i).rbegin() + a, (i).rbegin() + b
#define rall(...) overload3(__VA_ARGS__, rall3, rall2, rall1)(__VA_ARGS__)
// g++ -DDBUG -I . ...
#ifdef DEBUG
inline ll __lg(ull x) { return 63 - __builtin_clzll(x); }
#define debug(...)                                                             \
  {                                                                            \
    print(#__VA_ARGS__);                                                       \
    print(":");                                                                \
    out(__VA_ARGS__);                                                          \
  }
#else
#define debug(...) void(0)
#endif

#define vec vector
#define fi first
#define se second
#define MM << " " <<
#define chmax(x, y) (x = max(x, y))
#define chmin(x, y) (x = min(x, y))
void debug_out() { std::cerr << std::endl; }
template <typename Head, typename... Tail> void debug_out(Head h, Tail... t) {
  std::cerr << " " << h;
  if (sizeof...(t) > 0)
    std::cout << " :";
  debug_out(t...);
}

constexpr u64 Modulus = MODD;
class Modint {
public:
  u64 num = 0;
  constexpr Modint() noexcept {}
  constexpr Modint(const u64 x) noexcept : num(x % Modulus) {}
  inline constexpr operator ll() const noexcept { return num; }
  inline constexpr Modint &operator+=(const Modint rhs) noexcept {
    num += rhs.num;
    if (num >= Modulus)
      num -= Modulus;
    return *this;
  }
  inline constexpr Modint operator+(const Modint rhs) const noexcept {
    return Modint(*this) += rhs;
  }
  inline constexpr Modint &operator-=(const Modint rhs) noexcept {
    if (num < rhs.num)
      num += Modulus;
    num -= rhs.num;
    return *this;
  }
  inline constexpr Modint operator-(const Modint rhs) const noexcept {
    return Modint(*this) -= rhs;
  }
  inline constexpr Modint &operator*=(const Modint rhs) noexcept {
    num = num * rhs.num % Modulus;
    return *this;
  }
  inline constexpr Modint operator*(const Modint rhs) const noexcept {
    return Modint(*this) *= rhs;
  }
  inline constexpr Modint &operator/=(const Modint rhs) noexcept {
    return operator*=(rhs.inv());
  }
  constexpr Modint operator/(const Modint rhs) const noexcept {
    return Modint(*this) /= rhs;
  }
  inline constexpr Modint &operator++() noexcept {
    if (num == Modulus - 1)
      num = 0;
    else
      num++;
    return *this;
  }
  inline constexpr Modint operator++(int) noexcept {
    Modint ans(*this);
    operator++();
    return ans;
  }
  inline constexpr Modint &operator--() noexcept {
    if (num == 0)
      num = Modulus - 1;
    else
      num--;
    return *this;
  }
  inline constexpr Modint operator--(int) noexcept {
    Modint ans(*this);
    operator--();
    return ans;
  }
  inline constexpr Modint operator-() noexcept { return Modint(0) -= *this; }
  template <class T> inline constexpr Modint &operator+=(T x) noexcept {
    return operator+=(Modint(x));
  }
  template <class T> inline constexpr Modint &operator+(T x) noexcept {
    return Modint(*this) += x;
  }
  template <class T> inline constexpr Modint &operator-=(T x) noexcept {
    return operator-=(Modint(x));
  }
  template <class T> inline constexpr Modint &operator-(T x) noexcept {
    return Modint(*this) -= x;
  }
  template <class T> inline constexpr Modint &operator*=(T x) noexcept {
    return operator*=(Modint(x));
  }
  template <class T> inline constexpr Modint &operator*(T x) noexcept {
    return Modint(*this) *= x;
  }
  template <class T> inline constexpr Modint &operator/=(T x) noexcept {
    return operator/=(Modint(x));
  }
  template <class T> inline constexpr Modint &operator/(T x) noexcept {
    return Modint(*this) /= x;
  }
  inline constexpr Modint inv() const noexcept {
    ll x = 0, y = 0;
    extgcd(num, Modulus, x, y);
    return x;
  }
  static inline constexpr ll extgcd(ll a, ll b, ll &x, ll &y) noexcept {
    ll g = a;
    x = 1;
    y = 0;
    if (b) {
      g = extgcd(b, a % b, y, x);
      y -= a / b * x;
    }
    return g;
  }
  inline constexpr Modint pow(ull x) const noexcept {
    Modint ans = 1, cnt = *this;
    while (x) {
      if (x & 1)
        ans *= cnt;
      cnt *= cnt;
      x /= 2;
    }
    return ans;
  }
  template <class T> constexpr Modint(T x) noexcept {
    using U = typename conditional<sizeof(T) >= 4, T, int>::type;
    U y = x;
    y %= U(Modulus);
    if (y < 0)
      y += Modulus;
    num = uint(y);
  }
};
std::istream &operator>>(std::istream &is, Modint &x) {
  ll a;
  cin >> a;
  x = a;
  return is;
}
// inline constexpr Modint operator""_M(ull x) noexcept { return Modint(x); }
std::vector<Modint> fac(1, 1), inv(1, 1);
inline void reserve(ll a) {
  if (fac.size() >= a)
    return;
  if (a < fac.size() * 2)
    a = fac.size() * 2;
  if (a >= Modulus)
    a = Modulus;
  while (fac.size() < a)
    fac.push_back(fac.back() * Modint(fac.size()));
  inv.resize(fac.size());
  inv.back() = fac.back().inv();
  for (ll i = inv.size() - 1; !inv[i - 1]; i--)
    inv[i - 1] = inv[i] * i;
}
inline Modint fact(ll n) {
  if (n < 0)
    return 0;
  reserve(n + 1);
  return fac[n];
}
inline Modint perm(ll n, ll r) {
  if (r < 0 || n < r)
    return 0;
  if (n >> 24) {
    Modint ans = 1;
    for (ll i = 0; i < r; i++)
      ans *= n--;
    return ans;
  }
  reserve(n + 1);
  return fac[n] * inv[n - r];
}
// 階乗やその逆元をメモ化すると速い
// modを取りたくないならnCk/2^Nをパスカルの三角形で作る
inline Modint comb(ll n, ll r) {
  if (r < 0 || n < r)
    return 0;
  reserve(r + 1);
  return perm(n, r) * inv[r];
}
inline Modint Mcomb(ll n, ll r) {
  return comb(n + r - 1, n - 1);
} // r balls into n boxes
inline Modint catalan(ll n) {
  reserve(n * 2 + 1);
  return fac[n * 2] * inv[n] * inv[n + 1];
}

class runtime_modint {
  using u64 = std::uint_fast64_t;

  static u64 &mod() {
    static u64 mod_ = 0;
    return mod_;
  }

public:
  u64 a;

  runtime_modint(const u64 x = 0) : a(x % get_mod()) {}
  u64 &value() noexcept { return a; }
  const u64 &value() const noexcept { return a; }
  inline constexpr operator ll() const noexcept { return a; }
  runtime_modint operator+(const runtime_modint rhs) const {
    return runtime_modint(*this) += rhs;
  }
  runtime_modint operator-(const runtime_modint rhs) const {
    return runtime_modint(*this) -= rhs;
  }
  runtime_modint operator*(const runtime_modint rhs) const {
    return runtime_modint(*this) *= rhs;
  }
  runtime_modint operator/(const runtime_modint rhs) const {
    return runtime_modint(*this) /= rhs;
  }
  runtime_modint &operator+=(const runtime_modint rhs) {
    a += rhs.a;
    if (a >= get_mod()) {
      a -= get_mod();
    }
    return *this;
  }
  runtime_modint &operator-=(const runtime_modint rhs) {
    if (a < rhs.a) {
      a += get_mod();
    }
    a -= rhs.a;
    return *this;
  }
  runtime_modint &operator*=(const runtime_modint rhs) {
    a = a * rhs.a % get_mod();
    return *this;
  }
  runtime_modint &operator/=(runtime_modint rhs) {
    u64 exp = get_mod() - 2;
    while (exp) {
      if (exp % 2) {
        *this *= rhs;
      }
      rhs *= rhs;
      exp /= 2;
    }
    return *this;
  }

  template <class T> inline constexpr runtime_modint &operator+=(T x) noexcept {
    return operator+=(runtime_modint(x));
  }
  template <class T> inline constexpr runtime_modint &operator+(T x) noexcept {
    return runtime_modint(*this) += x;
  }
  template <class T> inline constexpr runtime_modint &operator-=(T x) noexcept {
    return operator-=(runtime_modint(x));
  }
  template <class T> inline constexpr runtime_modint &operator-(T x) noexcept {
    return runtime_modint(*this) -= x;
  }
  template <class T> inline constexpr runtime_modint &operator*=(T x) noexcept {
    return operator*=(runtime_modint(x));
  }
  template <class T> inline constexpr runtime_modint &operator*(T x) noexcept {
    return runtime_modint(*this) *= x;
  }
  template <class T> inline constexpr runtime_modint &operator/=(T x) noexcept {
    return operator/=(runtime_modint(x));
  }
  template <class T> inline constexpr runtime_modint &operator/(T x) noexcept {
    return runtime_modint(*this) /= x;
  }

  static void set_mod(const u64 x) { mod() = x; }
  static u64 get_mod() { return mod(); }
};

ll n, m;
bool used[100000];
vec<pair<ll, runtime_modint>> G[100000];

runtime_modint dfs(ll x) {
  used[x] = true;
  bool end = true;
  runtime_modint res = 1;
  each(p, G[x]) {
    if (used[p.fi] == true)
      continue;
    end = false;
    if (p.se != 0) {
      res *= p.se;
    } else {
      p.se = dfs(p.fi);
      // cout << x MM p.fi MM p.se << endl;
      res *= p.se;
    }
  }
  used[x] = false;
  return res + 1;
}

int main() { return 0; }
```