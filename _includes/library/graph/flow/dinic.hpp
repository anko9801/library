#include <queue>
#include <vector>

// O(V^2E)
struct Dinic {
  struct edge {
    long long to, cap, rev;
  };

  long long n;
  std::vector<std::vector<edge>> G;
  std::vector<long long> level, iter;

  // level[i] = sからiへの最短距離(Dijkstra法)
  void bfs(long long s) {
    level.assign(n, -1);
    std::queue<long long> q;
    q.push(s);
    level[s] = 0;
    while (!q.empty()) {
      long long v = q.front();
      q.pop();
      for (long long i = 0; i < G[v].size(); i++) {
        edge &e = G[v][i];
        if (e.cap > 0 && level[e.to] < 0) {
          level[e.to] = level[v] + 1;
          q.push(e.to);
        }
      }
    }
  }

  // v -> tの増加パスを1つ見つけて流す
  long long dfs(long long v, long long t, long long f) {
    if (v == t) return f;
    for (long long i = iter[v]; i < G[v].size(); i++) {
      edge &e = G[v][i];
      if (e.cap > 0 && level[v] < level[e.to]) {
        long long d = dfs(e.to, t, std::min(f, e.cap));
        if (d > 0) {
          e.cap -= d;
          G[e.to][e.rev].cap += d;
          return d;
        }
      }
    }
    return 0;
  }

  Dinic(long long n) : n(n), G(n), level(n), iter(n) {}

  void add_edge(long long from, long long to, long long cap) {
    G[from].push_back({to, cap, (long long)G[to].size()});
    G[to].push_back({from, 0, (long long)G[from].size() - 1});
  }

  long long max_flow(long long s, long long t) {
    long long flow = 0;
    while (true) {
      bfs(s);
      if (level[t] < 0) return flow;
      iter.assign(n, 0);
      long long f;
      while ((f = dfs(s, t, 1e9)) > 0) { flow += f; }
    }
  }
};
