#include <algorithm>
#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const long long cInf = 1e18;

struct Edge {
  int v;
  int id;
  int rid;
  long long cap;
  long long flow;
  long long cost;
};

vector<vector<Edge>> g;
vector<long long> d;
vector<int> p_v;
vector<int> p_e;
vector<long long> phi;

int n;
int m;

bool Dijkstra() {
  d.assign(n, cInf);
  vector<bool> used(n);
  d[0] = 0;
  for (int i = 0; i < n; i++) {
    int v = -1;
    for (int u = 0; u < n; u++) {
      if (!used[u] && (v == -1 || d[u] < d[v])) {
        v = u;
      }
    }
    if (v == -1 || d[v] == cInf) {
      break;
    }
    used[v] = true;
    for (int j = 0; j < (int)g[v].size(); j++) {
      Edge& e = g[v][j];
      long long w = e.cost + phi[v] - phi[e.v];
      if (e.cap > e.flow && d[e.v] > d[v] + w) {
        d[e.v] = d[v] + w;
        p_v[e.v] = v;
        p_e[e.v] = j;
      }
    }
  }
  return d[n - 1] != cInf;
}

int main() {
  cin >> n >> m;
  g.resize(n);
  d.resize(n, -1);
  p_v.resize(n, -1);
  p_e.resize(n, -1);
  phi.resize(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    long long c;
    long long w;
    cin >> u >> v >> c >> w;
    u--;
    v--;
    g[u].push_back({v, i, (int)g[v].size(), c, 0, w});
    g[v].push_back({u, -1, (int)g[u].size() - 1, 0, 0, -w});
  }

  long long ans = 0;
  while (Dijkstra()) {
    for (int v = 0; v < n; v++) {
      if (d[v] != cInf) {
        phi[v] += d[v];
      }
    }
    long long max_flow = cInf * 2;
    for (int v = n - 1; v > 0; v = p_v[v]) {
      max_flow =
          std::min(max_flow, g[p_v[v]][p_e[v]].cap - g[p_v[v]][p_e[v]].flow);
    }
    for (int v = n - 1; v > 0; v = p_v[v]) {
      Edge& e = g[p_v[v]][p_e[v]];
      e.flow += max_flow;
      g[v][e.rid].flow -= max_flow;
      ans += max_flow * e.cost;
    }
  }
  cout << ans << "\n";
}
