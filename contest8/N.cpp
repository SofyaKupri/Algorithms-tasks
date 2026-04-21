#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct Edge {
  int u;
  int v;
  int c;
  bool operator<(const Edge& e) const { return c < e.c; }
};

vector<int> p;
vector<int> sz;
vector<int> weights;
vector<Edge> edges;

int Get(int a) {
  if (p[a] == -1) {
    return a;
  }
  p[a] = Get(p[a]);
  return p[a];
}

void Merge(int a, int b) {
  a = Get(a);
  b = Get(b);
  if (sz[b] < sz[a]) {
    std::swap(a, b);
  }
  p[a] = b;
  sz[b] += sz[a];
  weights[b] += weights[a];
}

int main() {
  int n;
  int m;
  cin >> n >> m;
  p.resize(n, -1);
  sz.resize(n, 1);
  weights.resize(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    int c;
    cin >> u >> v >> c;
    edges.push_back({u - 1, v - 1, c});
  }
  sort(edges.begin(), edges.end());
  int w = 0;
  for (auto e : edges) {
    if (Get(e.u) != Get(e.v)) {
      w += e.c;
      Merge(e.u, e.v);
    }
    weights[Get(e.u)] += e.c;
  }
  cout << w << "\n";
}
