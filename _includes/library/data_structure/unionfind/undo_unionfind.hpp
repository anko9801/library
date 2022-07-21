#include <vector>

struct UnionFindUndo {
  std::vector<long long> data;
  std::stack<std::pair<long long>> history;
};
