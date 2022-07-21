#include <vector>

struct UnionFind {
  std::vector<int> rank, parents;

  UnionFind() {}
  UnionFind(int n) {
    rank.resize(n + 1, 0);
    parents.resize(n + 1, 0);
    for (int i = 0; i < n + 1; i++) makeTree(i);
  }

  void makeTree(int x) {
    parents[x] = x;
    rank[x] = 0;
  }

  bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }

  bool unite(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x == y) return false;
    if (rank[x] > rank[y]) {
      parents[y] = x;
    } else {
      parents[x] = y;
      if (rank[x] == rank[y]) rank[y]++;
    }
    return true;
  }

  int findRoot(int x) {
    if (x != parents[x]) parents[x] = findRoot(parents[x]);
    return parents[x];
  }
};