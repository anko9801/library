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
