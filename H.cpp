#include <algorithm>
#include <iostream>
#include <queue>
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
};

vector<vector<Edge>> g;
vector<long long> c;
vector<long long> f;
vector<int> d;
vector<int> p;

int n;
int m;

bool Bfs() {
  d.assign(n, -1);
  d[0] = 0;
  std::queue<int> q;
  q.push(0);
  while (!q.empty()) {
    int u = q.front();
    q.pop();
    for (auto e : g[u]) {
      if (e.cap - e.flow > 0 && d[e.v] == -1) {
        d[e.v] = d[u] + 1;
        q.push(e.v);
      }
    }
  }
  return d[n - 1] != -1;
}

long long Dfs(int v, int t, long long cur_cap) {
  if (cur_cap == 0) {
    return 0;
  }
  if (v == t) {
    return cur_cap;
  }
  for (int& cid = p[v]; cid < (int)g[v].size(); cid++) {
    Edge& e = g[v][cid];
    int u = e.v;
    if (d[v] + 1 != d[u] || e.cap - e.flow == 0) {
      continue;
    }
    long long u_cap = Dfs(u, t, std::min(cur_cap, e.cap - e.flow));
    if (u_cap == 0) {
      continue;
    }
    e.flow += u_cap;
    g[u][e.rid].flow -= u_cap;
    return u_cap;
  }
  return 0;
}

int main() {
  cin >> n >> m;
  g.resize(n);
  c.resize(m);
  d.resize(n, -1);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    long long w;
    cin >> u >> v >> w;
    u--;
    v--;
    c[i] = w;
    g[u].push_back({v, i, (int)g[v].size(), w, 0});
    g[v].push_back({u, -1, (int)g[u].size() - 1, 0, 0});
  }

  long long max_flow = 0;
  while (Bfs()) {
    p.assign(n, 0);
    while (long long cur_cap = Dfs(0, n - 1, cInf)) {
      max_flow += cur_cap;
    }
  }
  cout << max_flow << "\n";
  vector<long long> edge_flow(m, 0);
  for (int i = 0; i < n; i++) {
    for (const auto& e : g[i]) {
      if (e.id != -1) {
        edge_flow[e.id] = e.flow;
      }
    }
  }
  for (int i = 0; i < m; i++) {
    cout << edge_flow[i] << "\n";
  }
}
