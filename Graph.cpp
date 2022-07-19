class DAG {
	ll n;
	vector<vector<ll>> adj;
	vector<ll> visited;

	void dfs(ll v) {
		// 2回目
		if (visited[v] == 2) {
			is_acyclic = false;
			return;
		// 1回目
		}else if (!visited[v]) {
			visited[v] = 2;
			for (ll s : adj[v]) {
				dfs(s);
			}
			visited[v] = 1;
			sorted.push_back(v);
		}
	}

public:
	vector<ll> sorted;
	DAG(ll n) : n(n), adj(n), visited(n) {}
	bool is_acyclic = true; // isDAG

	void add_edge(ll a, ll b) {
		assert(0 <= a && a < n && 0 <= b && b < n);
		adj[a].push_back(b);
	}

	void tsort() {
		for (ll i = 0; i < n; i++) {
			if (!visited[i]) dfs(i);
		}
		reverse(all(sorted));
	}
};

class SCC {
	ll n;
	vector<vector<ll>> G, rG;
	// order: 帰りがけ順の逆順 == トポ順
	// comp: 強連結をグループ化
	vector<ll> order, comp;
	vector<bool> used;

	void dfs(ll v) {
		used[v] = true;
		for (auto nv : G[v]) {
			if (!used[nv]) dfs(nv);
		}
		order.push_back(v);
	}

	void rdfs(ll v, ll k) {
		comp[v] = k;
		for (auto nv : rG[v]) {
			if (comp[nv] < 0) rdfs(nv, k);
		}
	}

public:
	vector<vector<ll>> scc;

	SCC(vector<vector<ll>> &g) : n(g.size()), G(g), rG(g.size()), comp(g.size(), -1), used(g.size()) {
		for (ll i = 0; i < n; i++) {
			for (auto e : g[i]) {
				rG[e].emplace_back(i);
			}
		}
		for (ll i = 0; i < n; i++) if (!used[i]) dfs(i);
		reverse(all(order));
		ll k = 0;
		for (auto v : order) if (comp[v] == -1) rdfs(v, k), k++;
	}

	bool same(ll u, ll v) { return comp[u] == comp[v]; }

	void add_edge(ll a, ll b) {
		G[a].push_back(b);
		rG[b].push_back(a);
	}

	vector<vector<ll>> rebuild() {
		ll N = *max_element(all(comp)) + 1;
		vector<vector<ll>> rebuildedG(N);
		set<pll> connected;
		for (ll v = 0; v < N; v++) {
			for (auto nv : G[v]) {
				if (comp[v] != comp[nv] && !connected.count({v, nv})) {
					connected.insert({v, nv});
					rebuildedG[comp[v]].push_back(comp[nv]);
				}
			}
		}
		return rebuildedG;
	}
};