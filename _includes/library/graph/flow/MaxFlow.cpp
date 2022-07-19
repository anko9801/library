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

// O(V^2E)
struct Dinic {
	struct edge {
		ll to, cap, rev;
	};

	ll n;
	vector<vector<edge>> G;
	vector<ll> level, iter;

	// level[i] = sからiへの最短距離(Dijkstra法)
	void bfs(ll s) {
		level.assign(n, -1);
		queue<ll> q;
		q.push(s);
		level[s] = 0;
		while (!q.empty()) {
			ll v = q.front(); q.pop();
			for (ll i = 0; i < G[v].size(); i++) {
				edge &e = G[v][i];
				if (e.cap > 0 && level[e.to] < 0) {
					level[e.to] = level[v] + 1;
					q.push(e.to);
				}
			}
		}
	}

	// v -> tの増加パスを1つ見つけて流す
	ll dfs(ll v, ll t, ll f) {
		if (v == t) return f;
		for (ll i = iter[v]; i < G[v].size(); i++) {
			edge &e = G[v][i];
			if (e.cap > 0 && level[v] < level[e.to]) {
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

	Dinic(ll n) : n(n), G(n), level(n), iter(n) {}

	void add_edge(ll from, ll to, ll cap) {
		G[from].push_back({to, cap, G[to].size()});
		G[to].push_back({from, 0, G[from].size() - 1});
	}

	ll max_flow(ll s, ll t) {
		ll flow = 0;
		while (true) {
			bfs(s);
			if (level[t] < 0) return flow;
			iter.assign(n, 0);
			ll f;
			while ((f = dfs(s, t, 1e9)) > 0) {
				flow += f;
			}
		}
	}
};