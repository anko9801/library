#include <vector>

template <typename T>
struct Edge {
  int to;
  T cost;
};

using Graph = std::vector<std::vector<Edge<long long>>>;

template <typename T>
std::pair<T, int> dfs(const Graph &G, int u, int par) {
  auto ret = {0, u};
  for (auto &e : G) {
    if (e.to == par) continue;
    auto next = dfs<T>(G, e.to, u);
    next.first += e.cost;
    ret = std::max(ret, next);
  }
  return ret;
}

template <typename T>
T tree_diameter(const Graph &G) {
  auto p = dfs(G, 0, -1);
  auto q = dfs(G, p.second, -1);
  return q.first;
}