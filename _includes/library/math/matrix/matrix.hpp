#include <bits/stdc++.h>
#include <gcd.hpp>
using namespace std;

using ll = long long;
using ull = uint_fast64_t;
using pll = pair<ll, ll>;
using i64 = int_fast64_t;
using u64 = uint_fast64_t;

const ll MOD = 1e9 + 7;
const ll MODD = 998244353;

ll invmod(ll a, ll mod) {
  ll x, y;
  extgcd(a, mod, x, y);
  x %= mod;
  if (x < 0)
    x += mod;
  return x;
}

constexpr ll mx = 4;
class Matrix {
public:
  using T = ll;
  T m[mx][mx];
  // コンストラクタ
  constexpr Matrix() noexcept {}
  // アクセス
  const T *operator[](const ll i) const { return m[i]; } // read
  T *operator[](const ll i) { return m[i]; }             // write
  // 演算
  inline constexpr Matrix &operator+=(const Matrix &x) noexcept {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] += x[i][j];
    return *this;
  }
  inline constexpr Matrix operator+(const Matrix x) const noexcept {
    return Matrix(*this) += x;
  }
  inline constexpr Matrix &operator-=(const Matrix &x) noexcept {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] -= x[i][j];
    return *this;
  }
  inline constexpr Matrix operator-(const Matrix &x) noexcept {
    return Matrix(*this) -= x;
  }
  // O(N^3)
  inline constexpr Matrix &operator*=(Matrix &x) noexcept {
    *this = *this * x;
    return *this;
  }
  inline constexpr Matrix operator*(Matrix &x) {
    Matrix c;
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        for (ll k = 0; k < mx; k++) {
          T a = m[i][j] * x[j][k];
          c[i][k] += a;
        }
    return c;
  }
  // E^M O(N^3logM)
  inline constexpr Matrix pow(ll b) const noexcept {
    Matrix a = *this, c = E();
    while (b) {
      if (b & 1)
        c *= a;
      if (b >>= 1)
        a *= a;
    }
    return c;
  }
  inline constexpr Matrix static E() noexcept {
    Matrix a;
    for (ll i = 0; i < mx; i++)
      a[i][i] = 1;
    return a;
  }
  inline constexpr bool operator==(const Matrix &a) {
    bool flg = true;
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        if (m[i][j] != a[i][j])
          flg = false;
    return flg;
  }
  // 行列とスカラの演算
  inline constexpr Matrix &operator+=(const T &a) {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] += a;
    return *this;
  }
  inline constexpr Matrix &operator-=(const T &a) {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] -= a;
    return *this;
  }
  inline constexpr Matrix &operator*=(const T &a) {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] *= a;
    return *this;
  }
  inline constexpr Matrix &operator/=(const T &a) {
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m[i][j] /= a;
    return *this;
  }
  inline constexpr Matrix operator+(const T &a) const {
    return Matrix(*this) += a;
  }
  inline constexpr Matrix operator-(const T &a) const {
    return Matrix(*this) -= a;
  }
  inline constexpr Matrix operator*(const T &a) const {
    return Matrix(*this) *= a;
  }
  inline constexpr Matrix operator/(const T &a) const {
    return Matrix(*this) /= a;
  }
  // 転置行列
  inline constexpr Matrix t() {
    Matrix m2;
    for (ll i = 0; i < mx; i++)
      for (ll j = 0; j < mx; j++)
        m2[i][j] = m[j][i];
    return m2;
  }

  inline constexpr void show() {
    for (ll i = 0; i < mx; i++) {
      for (ll j = 0; j < mx; j++) {
        if (j != 0)
          cout << " ";
        cout << m[i][j];
      }
      cout << endl;
    }
    return;
  }
};
