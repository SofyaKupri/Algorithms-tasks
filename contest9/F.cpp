#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const long long cInf = 1e18;

struct Edge {
  int v;
  int u;
  int id;
  long long f;
};

vector<vector<long long>> c;
vector<bool> used;
vector<Edge> edges;

int n;
int m;

long long Dfs(int v, int p, long long f) {
  if (v == p) {
    return f;
  }
  used[v] = true;
  for (int u = 0; u < n; u++) {
    if (!used[u] && c[v][u] > 0) {
      long long tr = Dfs(u, p, std::min(f, c[v][u]));
      if (tr > 0) {
        c[v][u] -= tr;
        c[u][v] += tr;
        return tr;
      }
    }
  }
  return 0;
}

void Dfs(int v) {
  used[v] = true;
  for (int u = 0; u < n; u++) {
    if (!used[u] && c[v][u] > 0) {
      Dfs(u);
    }
  }
}

int main() {
  cin >> n >> m;
  c.resize(n, vector<long long>(n));
  used.resize(n, false);

  for (int i = 0; i < m; i++) {
    int u;
    int v;
    long long w;
    cin >> u >> v >> w;
    u--;
    v--;
    if (u == v) {
      continue;
    }
    edges.push_back({u, v, i, w});
    c[u][v] += w;
    c[v][u] += w;
  }

  long long max_flow = 0;
  while (true) {
    used.assign(n, false);
    long long f = Dfs(0, n - 1, cInf);
    if (f == 0) {
      break;
    }
    max_flow += f;
  }

  used.assign(n, false);
  Dfs(0);

  vector<int> cut_edges;
  for (auto e : edges) {
    if (used[e.v] != used[e.u]) {
      cut_edges.push_back(e.id + 1);
    }
  }
  sort(cut_edges.begin(), cut_edges.end());
  cout << cut_edges.size() << " " << max_flow << "\n";
  for (auto id : cut_edges) {
    cout << id << " ";
  }
  cout << "\n";
}
