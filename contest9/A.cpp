#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int n;
int m;
vector<vector<int>> g;
vector<int> mt;
vector<int> used;

bool Kuhn(int v) {
  if (used[v] != 0) {
    return false;
  }
  used[v] = 1;
  for (auto u : g[v]) {
    if (mt[u] == -1 || Kuhn(mt[u])) {
      mt[u] = v;
      return true;
    }
  }
  return false;
}

int main() {
  cin >> n >> m;
  g.resize(n);
  mt.resize(m, -1);
  for (int i = 0; i < n; i++) {
    int k;
    cin >> k;
    while (k != 0) {
      k--;
      g[i].push_back(k);
      cin >> k;
    }
  }
  for (int v = 0; v < n; v++) {
    used.assign(n, 0);
    Kuhn(v);
  }
  vector<std::pair<int, int>> ans;
  for (int u = 0; u < m; u++) {
    if (mt[u] != -1) {
      ans.push_back({mt[u] + 1, u + 1});
    }
  }
  cout << ans.size() << "\n";
  for (auto [u1, u2] : ans) {
    cout << u1 << " " << u2 << "\n";
  }
}
