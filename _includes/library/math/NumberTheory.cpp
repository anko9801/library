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

// x % m[i] = r[i] % m[i] を満たす正で最小の x を返す
// mは互いに素であると仮定
// とりあえず解の存在判定は保留
ll garner(vector<ll> r, vector<ll> m) {
  ll n = r.size();
  ll m_prod = 1;
  ll x = r[0] % m[0];
  for (ll i = 1; i < n; i++) {
    m_prod *= m[i - 1];
    ll t = ((r[i] - x) * invmod(m_prod, m[i])) % m[i];
    if (t < 0)
      t += m[i];
    x += t * m_prod;
  }
  return x;
}

class Eratosthenes {
public:
  vector<bool> isprime; // 素数
  vector<ll> minfactor; // 最小の素因数
  // メビウス関数 μ
  // μ(1)=1
  // n がある素数pで2回以上割り切れるとき、μ(n)=0
  // n=p1×p2×…pK と素因数分解できるとき、μ(n)=(−1)^K
  // f(1)=∑[i=1~N]μ(i)F(i) 約数系包除原理
  vector<ll> mobius;

  // エラトステネスの篩 O(NloglogN)
  Eratosthenes(int N)
      : isprime(N + 1, true), minfactor(N + 1, -1), mobius(N + 1, 1) {
    isprime[1] = false;
    minfactor[1] = 1;

    for (ll p = 2; p <= N; ++p) {
      if (!isprime[p])
        continue;
      minfactor[p] = p;
      mobius[p] = -1;
      for (ll q = p * 2; q <= N; q += p) {
        isprime[q] = false;
        if (minfactor[q] == -1)
          minfactor[q] = p;
        if ((q / p) % p == 0)
          mobius[q] = 0;
        else
          mobius[q] = -mobius[q / p];
      }
    }
  }

  // 高速素因数分解 O(NlogN)
  vector<pll> factorize(int n) {
    vector<pll> res;
    while (n > 1) {
      ll p = minfactor[n];
      ll exp = 0;

      while (minfactor[n] == p) {
        n /= p;
        ++exp;
      }
      res.emplace_back(p, exp);
    }
    return res;
  }

  // 高速約数列挙 O(\sigma n)
  vector<ll> divisors(ll n) {
    vector<ll> res({1});
    vector<pll> pf = factorize(n);

    for (auto [p, e] : pf) {
      ll s = (ll)res.size();
      for (ll i = 0; i < s; ++i) {
        ll v = res[i];
        for (ll j = 0; j < e; ++j) {
          v *= p;
          res.push_back(v);
        }
      }
    }
    return res;
  }

  // 高速ゼータ変換 O(NloglogN)
  // F(n)=∑[n|i]f(i)
  template <class T>
  void fast_zeta(vector<T> &f) {
    ll N = f.size();
    for (ll p = 2; p < N; ++p) {
      if (!isprime[p])
        continue;
      for (ll k = (N - 1) / p; k >= 1; --k) {
        f[k] += f[k * p];
      }
    }
  }

  // 高速メビウス変換 O(NloglogN)
  // f(n)=∑[n|i]μ(i/n)F(i)
  template <class T>
  void fast_mobius(vector<T> &F) {
    ll N = F.size();
    for (ll p = 2; p < N; ++p) {
      if (!isprime[p])
        continue;
      for (ll k = 1; k * p < N; ++k) {
        F[k] -= F[k * p];
      }
    }
  }

  // 添字GCD畳み込み O(NloglogN)
  // h(n)=∑[GCD(i,j)=n]f(i)g(j)
  // H(n)=F(n)G(n)
  template <class T>
  vector<T> gcd_conv(const vector<T> &f, const vector<T> &g) {
    ll N = max(f.size(), g.size());
    vector<T> F(N, 0), G(N, 0), H(N);
    for (ll i = 0; i < f.size(); ++i)
      F[i] = f[i];
    for (ll i = 0; i < g.size(); ++i)
      G[i] = g[i];

    fast_zeta(F);
    fast_zeta(G);

    for (ll i = 1; i < N; ++i)
      H[i] = F[i] * G[i];

    fast_mobius(H);

    return H;
  }
};

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
  template <class T>
  inline constexpr Modint &operator+=(T x) noexcept {
    return operator+=(Modint(x));
  }
  template <class T>
  inline constexpr Modint &operator+(T x) noexcept {
    return Modint(*this) += x;
  }
  template <class T>
  inline constexpr Modint &operator-=(T x) noexcept {
    return operator-=(Modint(x));
  }
  template <class T>
  inline constexpr Modint &operator-(T x) noexcept {
    return Modint(*this) -= x;
  }
  template <class T>
  inline constexpr Modint &operator*=(T x) noexcept {
    return operator*=(Modint(x));
  }
  template <class T>
  inline constexpr Modint &operator*(T x) noexcept {
    return Modint(*this) *= x;
  }
  template <class T>
  inline constexpr Modint &operator/=(T x) noexcept {
    return operator/=(Modint(x));
  }
  template <class T>
  inline constexpr Modint &operator/(T x) noexcept {
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
  template <class T>
  constexpr Modint(T x) noexcept {
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

/*
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

        static void set_mod(const u64 x) { mod() = x; }
        static u64 get_mod() { return mod(); }
};*/

constexpr ll mx = 4;
class Matrix {
public:
  using T = Modint;
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

int main() {
  Modint k = 20;
  Modint b = 30;
  k += k * b;
  cout << k * b << endl;
  Matrix a = Matrix::E();
  a.t();
  a += a;
  a *= a;
  a.show();
  return 0;
}