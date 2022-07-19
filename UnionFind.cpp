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

	bool same(ll x, ll y) {
		return find(x) == find(y);
	}

	ll size(ll x) {
		return sz[find(x)];
	}

	void unite(ll x, ll y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (rank[x] < rank[y]) {
			par[x] = y;
			sz[y] += sz[x];
		} else {
			par[y] = x;
			sz[x] += sz[y];
			if (rank[x] == rank[y]) {
				rank[x]++;
			}
		}
		cnt--;
	}
};

struct WeightedUnionFind {
	ll n, cnt;
	vector<ll> par, rank, sz;

	UnionFind(ll n) : n(n), cnt(n), par(n), rank(n), sz(n, 1) {
		iota(par.begin(), par.end(), 0);
	}

	ll find(ll x) {
		if (x == par[x]) return x;
		return par[x] = find(par[x]);
	}

	ll root(ll x) {
		if (par[x] == x) return x;
		else{
			ll r = root(par[x]);
			diff_weight[x] += diff_weight[par[x]];
			return par[x] = r;
		}
	}

	bool same(ll x, ll y) {
		return find(x) == find(y);
	}

	ll size(ll x) {
		return sz[find(x)];
	}

	void unite(ll x, ll y) {
		x = find(x), y = find(y);
		if (x == y) return;
		if (rank[x] < rank[y]) {
			par[x] = y;
			sz[y] += sz[x];
		} else {
			par[y] = x;
			sz[x] += sz[y];
			if (rank[x] == rank[y]) {
				rank[x]++;
			}
		}
		cnt--;
	}
};

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
		}else{
			par[x] = y;
			time[x] = t;
			if (rank[x] == rank[y]) {
				rank[y]++;
			}
		}
		return true;
	}

	bool same(ll t, ll x, ll y) {
		return find(t, x) == find(t, y);
	}
};

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

struct UnionFindUndo {
	vector<ll> data;
	stack<pll> history;
};