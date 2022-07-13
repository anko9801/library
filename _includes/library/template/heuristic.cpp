#include <sys/time.h>

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
const double TL = 1.95;

double start_time_ = -1;
bool first_time = true;

double get_time() {
  timeval tv;
  gettimeofday(&tv, 0);
  auto ret = tv.tv_sec + tv.tv_usec * 1e-6;
  if (first_time) {
    start_time_ = ret;
    first_time = false;
  }
  return ret - start_time_;
}

struct rand_gen {
  static const int MAX = 2147483647;
  static constexpr double Q_MAX = 1.0 / MAX;

  int x = 8753, y = 239017, z = 1000000123;

  inline int next_int() {
    int t = x ^ (x << 11);
    x = y;
    y = z;
    z ^= (z >> 19) ^ t ^ (t >> 8);
    return z;
  }

  double next_double() { return next_int() * Q_MAX; }
} rng;

// function<void(int, int)> Dfs = [&](int v, int depth) {}

ll calculate_score() {
  ll last[26] = {};
  ll score = 0;
  ll sumc = 0;
  rep(i, 0, 26) sumc += c[i];
  ll mem_diff = 0;
  rep(d, 0, D) {
    score += s[d][t[d] - 1];
    mem_diff += -sumc + c[t[d] - 1] * (d + 1 - last[t[d] - 1]);
    score += mem_diff;
    last[t[d] - 1] = d + 1;
  }
  return score;
}

double T0 = 1735, T1 = 10;

int main() {
  cin >> D;
  rep(i, 0, 26) cin >> c[i];
  rep(i, 0, D) rep(j, 0, 26) cin >> s[i][j];

  // 初期解
  rep(i, 0, D) t[i] = i % 26 + 1;

  // 焼きなまし法
  ll score = calculate_score(), old_score = -LINF;
  while (get_time() < TL) {
    // 更新
    ll r1 = rng.next_int() % D, r2 = rng.next_int() % D;
    ll oldt[2] = {t[r1], t[r2]};
    ll newt[2] = {t[r2], t[r2]};
    if (rng.next_int() % 2 == 0) {
      t[r1] = rng.next_int() % 26 + 1;
      newt[1] = t[r1];
    } else {
      t[r1] = t[r2];
      t[r2] = oldt[0];
      newt[1] = oldt[0];
    }

    // スコアに応じた処理
    ll k = score;
    score = calculate_score();
    ll r;
    rep(m, 0, 2) {
      if (m == 0)
        r = r1;
      else
        r = r2;
      ll back[2] = {0, 0}, forward[2] = {365, 365};
      rep(i, 0, r) if (t[i] == oldt[m]) back[0] = i;
      rep(i, r + 1, 365) if (t[i] == oldt[m]) {
        forward[0] = i;
        break;
      }
      rep(i, 0, r) if (t[i] == newt[m]) back[1] = i;
      rep(i, r + 1, 365) if (t[i] == newt[m]) {
        forward[1] = i;
        break;
      }
      k += (r - back[0]) * (forward[0] - r);
      k -= (r - back[1]) * (forward[1] - r);
    }
    cout << k - old_score << " " << score - old_score << endl;

    if (score >= old_score) {
      old_score = score;
    } else {
      double per = get_time() / TL;
      double T = pow(T0, 1 - per) * pow(T1, per);
      T = exp((double)(score - old_score) / T);

      if (rng.next_double() < T) {
        old_score = score;
      } else {
        t[r1] = oldt[0];
        t[r2] = oldt[1];
      }
    }
  }

  // 出力
  rep(i, 0, D) cout << t[i] << endl;
  return 0;
}
