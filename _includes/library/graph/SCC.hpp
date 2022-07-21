#include <algorithm>
#include <set>
#include <vector>

class SCC {
  int n;
  std::vector<std::vector<int>> G, rG;
  // order: 帰りがけ順の逆順 == トポ順
  // comp: 強連結をグループ化
  std::vector<int> order, comp;
  std::vector<bool> used;

  void dfs(int v) {
    used[v] = true;
    for (auto nv : G[v]) {
      if (!used[nv]) dfs(nv);
    }
    order.push_back(v);
  }

  void rdfs(int v, int k) {
    comp[v] = k;
    for (auto nv : rG[v]) {
      if (comp[nv] < 0) rdfs(nv, k);
    }
  }

public:
  std::vector<std::vector<int>> scc;

  SCC(std::vector<std::vector<int>> &g)
      : n(g.size()), G(g), rG(g.size()), comp(g.size(), -1),
        used(g.size()) {
    for (int i = 0; i < n; i++) {
      for (auto e : g[i]) { rG[e].emplace_back(i); }
    }
    for (int i = 0; i < n; i++)
      if (!used[i]) dfs(i);
    reverse(order.begin(), order.end());
    int k = 0;
    for (auto v : order)
      if (comp[v] == -1) rdfs(v, k), k++;
  }

  bool same(int u, int v) const { return comp[u] == comp[v]; }

  void add_edge(int a, int b) {
    G[a].push_back(b);
    rG[b].push_back(a);
  }

  std::vector<std::vector<int>> rebuild() const {
    int N = *max_element(comp.begin(), comp.end()) + 1;
    std::vector<std::vector<int>> rebuildedG(N);
    std::set<std::pair<int, int>> connected;
    for (int v = 0; v < N; v++) {
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
