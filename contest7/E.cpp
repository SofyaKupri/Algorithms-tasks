#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int n;
int m;
vector<vector<std::pair<int, int>>> g;
vector<bool> used;
vector<int> tin;
vector<int> up;
vector<int> ans;
int t = 0;
void Dfs(int v, int p) {
  used[v] = true;
  tin[v] = up[v] = t++;
  for (auto [u, i] : g[v]) {
    if (i == p) {
      continue;
    }
    if (used[u]) {
      up[v] = std::min(up[v], tin[u]);
    } else {
      Dfs(u, i);
      up[v] = std::min(up[v], up[u]);
      if (up[u] > tin[v]) {
        ans.push_back(i + 1);
      }
    }
  }
}

int main() {
  cin >> n >> m;
  g.resize(n);
  used.resize(n);
  tin.resize(n);
  up.resize(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back({v, i});
    g[v].push_back({u, i});
  }
  for (int u = 0; u < n; u++) {
    if (!used[u]) {
      Dfs(u, -1);
    }
  }
  cout << ans.size() << "\n";
  std::sort(ans.begin(), ans.end());
  for (auto edge : ans) {
    cout << edge << "\n";
  }
}
