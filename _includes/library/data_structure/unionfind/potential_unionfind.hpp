struct PotentialUnionFindTree {
  vec<ll> par, diff;

  PotentialUnionFindTree(ll n) {
    par.resize(n);
    diff.resize(n);
  }

  ll find(ll x) {
    if (par[x] == x) return x;
    ll r = find(par[x]);
    diff[x] += diff[par[x]];
    return par[x] = r;
  }

  ll weight(ll x) {
    find(x);
    return diff[x];
  }

  void unite(ll x, ll y, ll w) {
    w += weight(x);
    w += weight(y);
    x = find(x);
    y = find(y);
    par[y] = x;
    diff[y] = w;
  }
};
