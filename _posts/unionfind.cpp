struct UnionFind { // The range of node number is from 0 to n-1
  //'rank[x]' is a rank of the union find tree the root of which is x.
  //'parents[x]' is the parent of x
  vector<int> rank, parents;
  // constructor
  UnionFind() {}
  UnionFind(int n) { // make n trees.
    rank.resize(n, 0);
    parents.resize(n, 0);
    for (int i = 0; i < n; i++) {
      makeTree(i);
    }
  }
  // make a union find tree
  void makeTree(int x) {
    parents[x] = x; // the parent of x is x
    rank[x] = 0;
  }
  // check whether the root of x is the same as that of y
  bool isSame(int x, int y) { return findRoot(x) == findRoot(y); }
  // unite two tree
  bool unite(int x, int y) {
    x = findRoot(x);
    y = findRoot(y);
    if (x == y)
      return false;
    if (rank[x] > rank[y]) {
      parents[y] = x;
    } else {
      parents[x] = y;
      if (rank[x] == rank[y]) {
        rank[y]++;
      }
    }
    return true;
  }
  // travel the parents of tree recursivily to find root
  int findRoot(int x) {
    if (x != parents[x]) {
      parents[x] =
          findRoot(parents[x]); // change the x's parent to the root of tree.
    }
    return parents[x];
  }
};