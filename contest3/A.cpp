#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::pair;
using std::vector;

const int cInf = 1e9 + 1;

struct SparseTable {
  int n;
  int l;
  vector<vector<pair<int, int>>> sparse;
  vector<int> v;
  vector<int> log;
  pair<int, int> GetPair(pair<int, int>& a, pair<int, int>& b) {
    vector<int> cur = {a.first, a.second, b.first, b.second};
    for (int k = 0; k < 4; k++) {
      for (int t = 0; t + 1 < 4; t++) {
        if (v[cur[t]] > v[cur[t + 1]]) {
          std::swap(cur[t], cur[t + 1]);
        }
      }
    }
    pair<int, int> res = {cur[0], n};
    if (cur[0] == cur[1]) {
      res.second = cur[2];
    } else {
      res.second = cur[1];
    }
    return res;
  }
  SparseTable(vector<int>& a) {
    n = a.size();
    log.resize(n + 1);
    for (int i = 2; i <= n; i++) {
      log[i] = log[i / 2] + 1;
    }
    l = log[n];
    sparse.resize(l + 1, vector<pair<int, int>>(n));
    v.resize(n + 1);
    v[n] = cInf;
    for (int i = 0; i < n; i++) {
      sparse[0][i] = {i, n};
      v[i] = a[i];
    }
    for (int j = 1; j <= l; j++) {
      for (int i = 0; i + (1 << j) <= n; i++) {
        sparse[j][i] =
            GetPair(sparse[j - 1][i], sparse[j - 1][i + (1 << (j - 1))]);
      }
    }
  }
  int Get2Min(int l, int r) {
    int lg = log[r - l];
    return v[GetPair(sparse[lg][l], sparse[lg][r - (1 << lg)]).second];
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
  SparseTable s(a);
  while ((q--) > 0) {
    int l;
    int r;
    cin >> l >> r;
    cout << s.Get2Min(l - 1, r) << "\n";
  }
}
