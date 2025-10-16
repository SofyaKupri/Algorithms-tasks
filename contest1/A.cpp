#include <iostream>
#include <vector>

using namespace std;

void Merge(vector<pair<int, int>>& v, int l, int m, int r) {
  int i = 0;
  int j = 0;
  vector<pair<int, int>> res(r - l);
  while (l + i < m && m + j < r) {
    if (v[l + i] <= v[m + j]) {
      res[i + j] = v[l + i];
      i++;
    } else {
      res[i + j] = v[m + j];
      j++;
    }
  }
  while (l + i < m) {
    res[i + j] = v[l + i];
    i++;
  }
  while (m + j < r) {
    res[i + j] = v[m + j];
    j++;
  }
  for (int k = 0; k < r - l; k++) {
    v[l + k] = res[k];
  }
}

void MergeSort(vector<pair<int, int>>& v, int l, int r) {
  if (l + 1 >= r) {
    return;
  }
  int m = (l + r) / 2;
  MergeSort(v, l, m);
  MergeSort(v, m, r);
  Merge(v, l, m, r);
}

int main() {
  int n;
  cin >> n;
  vector<pair<int, int>> v(2 * n);
  for (int i = 0; i < n; i++) {
    int l;
    int r;
    cin >> l >> r;
    v[2 * i] = {l, 1};
    v[2 * i + 1] = {r + 1, -1};
  }
  MergeSort(v, 0, 2 * n);
  vector<pair<int, int>> segments;
  int st = -1;
  int bal = 0;
  for (int i = 0; i < 2 * n; i++) {
    if (bal == 0) {
      st = v[i].first;
    }
    bal += v[i].second;
    if (bal == 0) {
      segments.push_back({st, v[i].first - 1});
      st = -1;
    }
  }
  cout << segments.size() << "\n";
  for (size_t i = 0; i < segments.size(); i++) {
    cout << segments[i].first << " " << segments[i].second << "\n";
  }
}
