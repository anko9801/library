struct PartiallyParsistUnionFind {
  vector<ll> rank, par, time;

  PartiallyParsistUnionFind(ll n) {
    rank.resize(n);
    par.resize(n, -1);
    time.resize(n, LINF);
  }

  ll find(ll t, ll x) {
    if (time[x] > t) return x;
    return find(t, par[x]);
  }

  bool unite(ll t, ll x, ll y) {
    x = find(t, x);
    y = find(t, y);
    if (x == y) return false;
    if (rank[x] > rank[y]) {
      par[y] = x;
      time[y] = t;
    } else {
      par[x] = y;
      time[x] = t;
      if (rank[x] == rank[y]) { rank[y]++; }
    }
    return true;
  }

  bool same(ll t, ll x, ll y) { return find(t, x) == find(t, y); }
};
