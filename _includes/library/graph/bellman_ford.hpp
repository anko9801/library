#include <vector>

const long long LINF = 0x1fffffffffffffff;

struct Edge {
  int from, to, cost;
};

class BellmanFord {
  std::vector<Edge> edges;
  std::vector<long long> d;
  int V, E;

  BellmanFord(int v) : V(v), E(0) {}

  void add_edge(int from, int to, int cost) {
    edges.push_back({from, to, cost});
    E++;
  }
  void add_edge(std::vector<Edge> &es) {
    for (auto &edge : es) edges.push_back(edge);
    E += es.size();
  }

  bool shortest_path(int s) {
    for (int i = 0; i < V; i++) d[i] = LINF;
    d[s] = 0;
    for (int v = 0; v < V; v++) {
      bool update = false;
      for (int i = 0; i < E; i++) {
        auto e = edges[i];
        if (d[e.from] != LINF && d[e.to] > d[e.from] + e.cost) {
          d[e.to] = d[e.from] + e.cost;
          update = true;
        }
      }
      // negative loop
      if (v == V - 1 && update) return false;
      if (!update) break;
    }
    return true;
  }
};
