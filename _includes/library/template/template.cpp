#ifndef LOCAL
#pragma GCC optimize("Ofast")
#pragma GCC optimize("unroll-loops")
#endif

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
using C = complex<ld>;
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

int main() {
  cin.tie(0);
  ios::sync_with_stdio(0);
  cout << fixed << setprecision(20);

  return 0;
}
