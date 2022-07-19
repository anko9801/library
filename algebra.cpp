std::vector<Modint> fac(1, 1), inv(1, 1);
void reserve(ll a) {
    if(fac.size() >= a) return;
    if(a < fac.size() * 2) a = fac.size() * 2;
    while(fac.size() < a) fac.push_back(fac.back() * Modint(fac.size()));
    inv.resize(fac.size());
    inv.back() = fac.back().inv();
    for(ll i = inv.size() - 1; inv[i - 1] == 0; i--) inv[i - 1] = inv[i] * i;
}
Modint fact(ll n){ if(n < 0) return 0; reserve(n + 1); return fac[n]; }
Modint perm(ll n, ll r){
    if (r < 0 || n < r) return 0;
    if (n >> 24){ Modint ans = 1; for(ll i = 0; i < r; i++) ans *= n--; return ans; }
    reserve(n + 1); return fac[n] * inv[n - r];
}
Modint comb(ll n, ll r){ if(r < 0 || n < r) return 0; reserve(r + 1); return perm(n, r) * inv[r]; }
Modint Mcomb(ll n, ll r){ return comb(n + r - 1, r); } // r個をn部屋に分ける
Modint catalan(ll n){ reserve(n * 2 + 1); return fac[n * 2] * inv[n] * inv[n + 1]; }

using mint = Modint;
using vm = vector<mint>;
struct fps : vm {
#define d (*this)
#define s int(vm::size())
	template<class...Args> fps(Args...args): vm(args...) {}
	fps(initializer_list<mint> a): vm(a.begin(),a.end()) {}
	void rsz(int n) { if (s < n) vm.resize(n);}
	mint& operator[](int i) { rsz(i+1); return vm::operator[](i);}
	mint operator[](int i) const { return i<s ? vm::operator[](i) : 0;}
	fps operator-() const { fps r(d); rep(i,s) r[i] = -r[i]; return r;}
	fps& operator+=(const fps& a) { rsz(a.size()); rep(i,a.size()) d[i] += a[i]; return d;}
	fps& operator-=(const fps& a) { rsz(a.size()); rep(i,a.size()) d[i] -= a[i]; return d;}
	fps& operator*=(const fps& a) { return d = convolution(d, a);}
	fps operator+(const fps& a) const { return fps(d) += a;}
	fps operator-(const fps& a) const { return fps(d) -= a;}
	fps operator*(const fps& a) const { return fps(d) *= a;}
#undef s
#undef d
};

template<typename T>
struct Dijkstra {
  const T INF = numeric_limits<T>::max();
  using P = pair<T,int>;
  struct Edge {
    int to; T cost;
    Edge() {}
    Edge(int to, T cost=0): to(to), cost(cost) {}
  };
  int n;
  vector<vector<Edge>> g;
  Dijkstra() {}
  Dijkstra(int n): n(n), g(n) {}
  void addEdge(int a, int b, T cost) {
    g[a].emplace_back(b, cost);
    // g[b].emplace_back(a, cost);
  }

  vector<T> getDist(int sv) {
    vector<T> dist(n, INF);
    priority_queue<P, vector<P>, greater<P>> q;
    dist[sv] = 0;
    q.emplace(0, sv);
    while (!q.empty()) {
      auto [d,v] = q.top(); q.pop();
      if (dist[v] != d) continue;
      for (Edge& e : g[v]) {
        T nd = d+e.cost;
        if (dist[e.to] <= nd) continue;
        dist[e.to] = nd;
        q.emplace(nd, e.to);
      }
    }
    return dist;
  }
};