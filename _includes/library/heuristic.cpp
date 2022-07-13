#include <sys/time.h>

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
