#include <queue>
#include <vector>

using ll = long long;
using pll = std::pair<ll, ll>;
template <class T>
using pq = std::priority_queue<T, std::vector<T>, std::greater<T>>;

const long long LINF = 0x1fffffffffffffff;

struct Edge {
  int to, cost;
};

int V;
std::vector<ll> d;
std::vector<std::vector<Edge>> G;

void dijkstra(int s) {
  pq<pll> q;
  for (int i = 0; i < V; i++) d[i] = LINF;
  d[s] = 0;
  q.push({d[s], s});

  while (!q.empty()) {
    auto [dist, p] = q.top();
    q.pop();
    if (d[p] < dist) continue;
    for (auto &e : G[p]) {
      if (d[e.to] > d[p] + e.cost) {
        d[e.to] = d[p] + e.cost;
        q.push({d[e.to], e.to});
      }
    }
  }
}
