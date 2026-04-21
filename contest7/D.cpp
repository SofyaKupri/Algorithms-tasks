#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int n;
int m;
vector<vector<int>> g;
vector<vector<int>> gr;
vector<int> used;
vector<int> comp;
vector<int> top_sort;
int c = 0;
void Dfs(int v) {
  used[v] = 1;
  for (auto u : g[v]) {
    if (used[u] == 0) {
      Dfs(u);
    }
  }
  top_sort.push_back(v);
}
void Dfs1(int v) {
  used[v] = 1;
  comp[v] = c;
  for (auto u : gr[v]) {
    if (used[u] == 0) {
      Dfs1(u);
    }
  }
}

int main() {
  cin >> n >> m;
  g.resize(n);
  gr.resize(n);
  used.resize(n);
  comp.resize(n);
  for (int i = 0; i < m; i++) {
    int u;
    int v;
    cin >> u >> v;
    u--;
    v--;
    g[u].push_back(v);
    gr[v].push_back(u);
  }
  for (int v = 0; v < n; v++) {
    if (used[v] == 0) {
      Dfs(v);
    }
  }
  used.assign(n, 0);
  reverse(top_sort.begin(), top_sort.end());
  for (auto v : top_sort) {
    if (used[v] == 0) {
      c++;
      Dfs1(v);
    }
  }
  cout << c << "\n";
  for (int v = 0; v < n; v++) {
    cout << comp[v] << " ";
  }
}
