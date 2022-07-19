#include <vector>

std::vector<std::vector<int>> d;
int V;

void floyd_warshall() {
  for (int k = 0; k < V; k++)
    for (int i = 0; i < V; i++)
      for (int j = 0; j < V; j++) d[i][j] = std::min(d[i][j], d[i][k] + d[k][j]);
}