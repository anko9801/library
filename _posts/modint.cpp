#include <bits/stdc++.h>

using ll = long long;
using u64 = std::uint_fast64_t;

constexpr u64 Modulus = MOD;
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