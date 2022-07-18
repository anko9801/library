#include <vector>

// x % m[i] = r[i] % m[i] を満たす正で最小の x を返す
// mは互いに素であると仮定
// とりあえず解の存在判定は保留
template <typename T>
T CRT(std::vector<T> r, std::vector<T> m) {
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