#include <iostream>
#include <vector>

using namespace std;

int FindMin(vector<int>& a, vector<int>& b, int& x) {
  int l = -1;
  int r = a.size() - 1;
  while (l + 1 < r) {
    int m = (l + r) >> 1;
    if (a[m] + x >= b[m]) {
      r = m;
    } else {
      l = m;
    }
  }
  if (r > 0) {
    if (max(a[r - 1] + x, b[r - 1]) < max(a[r] + x, b[r])) {
      return r - 1;
    }
  }
  return r;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int n;
  cin >> n;
  vector<int> a(n);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
  }
  vector<int> b(n);
  for (int i = 0; i < n; i++) {
    cin >> b[i];
  }
  int q;
  cin >> q;
  while ((q--) > 0) {
    int x;
    cin >> x;
    cout << FindMin(a, b, x) + 1 << "\n";
  }
}
