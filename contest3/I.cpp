#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct MergeSortTree {
  int n;
  vector<vector<int>> t;
  MergeSortTree(const vector<int>& a) {
    n = a.size();
    t.resize(4 * n);
    Build(0, 0, n, a);
  }
  void Build(int v, int l, int r, const vector<int>& a) {
    if (l + 1 == r) {
      t[v].push_back(a[l]);
      return;
    }
    int m = (l + r) / 2;
    Build(2 * v + 1, l, m, a);
    Build(2 * v + 2, m, r, a);
    t[v].resize(t[2 * v + 1].size() + t[2 * v + 2].size());
    std::merge(t[2 * v + 1].begin(), t[2 * v + 1].end(), t[2 * v + 2].begin(),
               t[2 * v + 2].end(), t[v].begin());
  }
  int Get(int v, int l, int r, int ql, int qr, const std::pair<int, int>& p) {
    if (l >= qr || ql >= r) {
      return 0;
    }
    if (ql <= l && qr >= r) {
      return lower_bound(t[v].begin(), t[v].end(), p.second + 1) -
             lower_bound(t[v].begin(), t[v].end(), p.first);
    }
    int m = (l + r) / 2;
    return Get(2 * v + 1, l, m, ql, qr, p) + Get(2 * v + 2, m, r, ql, qr, p);
  }
  int Get(int ql, int qr, const std::pair<int, int>& p) {
    return Get(0, 0, n, ql, qr, p);
  }
};

int main() {
  int n;
  int q;
  cin >> n >> q;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  MergeSortTree t(a);
  while ((q--) > 0) {
    int l;
    int r;
    std::pair<int, int> p;
    cin >> l >> r >> p.first >> p.second;
    cout << t.Get(l - 1, r, p) << "\n";
  }
}
