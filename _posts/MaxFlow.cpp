class FordFulkerson {
	struct edge {
		ll to, cap, rev;
	};
	ll n;
	vector<vector<edge>> G;
	vector<bool> used;

	ll dfs(ll s, ll t, ll f) {
		if (s == t) return f;
		used[s] = true;
		for (edge &e : G[s]) {
			if (!used[e.to] && e.cap > 0) {
				ll d = dfs(e.to, t, min(f, e.cap));
				if (d > 0) {
					e.cap -= d;
					G[e.to][e.rev].cap += d;
					return d;
				}
			}
		}
		return 0;
	}

public:
	FordFulkerson(ll n) : n(n), G(n), used(n) {}
	void add_edge(ll from, ll to, ll cap) {
		G[from].push_back({to, cap, ll(G[to].size())});
		G[to].push_back({from, 0, ll(G[from].size()) - 1});
	}

	ll max_flow(ll s, ll t) {
		ll flow = 0;
		while (true) {
			used.assign(n, 0);
			ll f = dfs(s, t, INF);
			if (f == 0) return flow;
			flow += f;
		}
	}
};