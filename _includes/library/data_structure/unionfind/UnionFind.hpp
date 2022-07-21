struct UnionFind {
  ll n, cnt;
  vector<ll> par, rank, sz;

  UnionFind(ll n) : n(n), cnt(n), par(n), rank(n), sz(n, 1) {
    iota(par.begin(), par.end(), 0);
  }

  ll find(ll x) {
    if (x == par[x]) return x;
    return par[x] = find(par[x]);
  }

  bool same(ll x, ll y) { return find(x) == find(y); }

  ll size(ll x) { return sz[find(x)]; }

  void unite(ll x, ll y) {
    x = find(x), y = find(y);
    if (x == y) return;
    if (rank[x] < rank[y]) {
      par[x] = y;
      sz[y] += sz[x];
    } else {
      par[y] = x;
      sz[x] += sz[y];
      if (rank[x] == rank[y]) { rank[x]++; }
    }
    cnt--;
  }
};
