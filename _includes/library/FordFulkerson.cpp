#include <vector>

class FordFulkerson {
  struct edge {
    long long to, cap, rev;
  };
  const long long INF = 1 << 60;
  long long n;
  std::vector<std::vector<edge>> G;
  std::vector<bool> used;

  long long dfs(long long s, long long t, long long f) {
    if (s == t)
      return f;
    used[s] = true;
    for (edge &e : G[s]) {
      if (!used[e.to] && e.cap > 0) {
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

public:
  FordFulkerson(long long n) : n(n), G(n), used(n) {}
  void add_edge(long long from, long long to, long long cap) {
    G[from].push_back({to, cap, (long long)(G[to].size())});
    G[to].push_back({from, 0, (long long)(G[from].size()) - 1});
  }

  long long max_flow(long long s, long long t) {
    long long flow = 0;
    while (true) {
      used.assign(n, 0);
      long long f = dfs(s, t, INF);
      if (f == 0)
        return flow;
      flow += f;
    }
  }
};