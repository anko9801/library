#include <memory>

class Treap {
  struct Node {
    int value;
    std::unique_ptr<Node> child[2];
    int priority;
    int size;
    int sum;

    Node(int v, double p) {
      value = v;
      priority = p;
      size = 1;
      sum = v;
    }
  };
  int count(std::unique_ptr<Node> t) { return !t ? 0 : t->size; }
  int sum(std::unique_ptr<Node> t) { return !t ? 0 : t->sum; }
  std::unique_ptr<Node> update(std::unique_ptr<Node> t) { t->size = count(t); }
};