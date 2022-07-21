#include <algorithm>
#include <cassert>
#include <vector>

class DAG {
  int n;
  std::vector<std::vector<int>> adj;
  std::vector<int> visited;

  void dfs(int v) {
    // 2回目
    if (visited[v] == 2) {
      is_acyclic = false;
      return;
      // 1回目
    } else if (!visited[v]) {
      visited[v] = 2;
      for (int s : adj[v]) { dfs(s); }
      visited[v] = 1;
      sorted.push_back(v);
    }
  }

public:
  std::vector<int> sorted;
  DAG(int n) : n(n), adj(n), visited(n) {}
  bool is_acyclic = true; // isDAG

  void add_edge(int a, int b) {
    assert(0 <= a && a < n && 0 <= b && b < n);
    adj[a].push_back(b);
  }

  void tsort() {
    for (int i = 0; i < n; i++) {
      if (!visited[i]) dfs(i);
    }
    reverse(sorted.begin(), sorted.end());
  }
};
