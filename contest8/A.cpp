#include <iostream>
#include <set>
#include <vector>

using std::cin;
using std::cout;
using std::set;
using std::vector;

const long long cInf = 2009000999;

void Solve() {
  int n;
  int m;
  cin >> n >> m;
  vector<vector<std::pair<int, long long>>> g(n);
  while ((m--) != 0) {
    int u;
    int v;
    int c;
    cin >> u >> v >> c;
    g[v].push_back({u, c});
    g[u].push_back({v, c});
  }
  int s;
  cin >> s;
  vector<long long> d(n, cInf);
  set<std::pair<int, long long>> q;
  q.insert({0, s});
  d[s] = 0;
  while (!q.empty()) {
    int v = (*q.begin()).second;
    q.erase(q.begin());
    for (auto e : g[v]) {
      int u = e.first;
      long long w = e.second;
      if (d[u] > d[v] + w) {
        q.erase({d[u], u});
        d[u] = d[v] + w;
        q.insert({d[u], u});
      }
    }
  }
  for (int i = 0; i < n; i++) {
    cout << d[i] << " ";
  }
  cout << "\n";
}

int main() {
  int t;
  cin >> t;
  while ((t--) != 0) {
    Solve();
  }
}
