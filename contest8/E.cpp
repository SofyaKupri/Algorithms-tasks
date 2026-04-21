#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const int cInf = 1e9;
const int cMax = 1e5;

void Solve() {
  int n;
  cin >> n;
  vector<vector<int>> g(n, vector<int>(n));
  for (int u = 0; u < n; u++) {
    for (int v = 0; v < n; v++) {
      cin >> g[u][v];
    }
  }
  vector<int> d(n, cInf);
  vector<int> p(n, -1);
  d[0] = 0;
  int last = -1;
  for (int k = 0; k < n; k++) {
    last = -1;
    for (int u = 0; u < n; u++) {
      for (int v = 0; v < n; v++) {
        if (g[u][v] != cMax && d[v] > d[u] + g[u][v]) {
          d[v] = d[u] + g[u][v];
          p[v] = u;
          last = v;
        }
      }
    }
  }
  if (last == -1) {
    cout << "NO\n";
  } else {
    cout << "YES\n";
    int v = last;
    for (int k = 0; k < n; k++) {
      v = p[v];
    }
    vector<int> cycle;
    for (int cur = v;; cur = p[cur]) {
      cycle.push_back(cur);
      if (cur == v && cycle.size() > 1) {
        break;
      }
    }
    std::reverse(cycle.begin(), cycle.end());
    cout << cycle.size() << "\n";
    for (auto u : cycle) {
      cout << u + 1 << " ";
    }
    cout << "\n";
  }
}

int main() { Solve(); }
