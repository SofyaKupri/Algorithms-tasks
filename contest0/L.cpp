#include <iostream>
#include <string>
#include <vector>

using namespace std;

int main() {
  string s;
  string t;
  cin >> s >> t;
  int n = s.size();
  int m = t.size();
  vector<int> p(n);
  vector<int> ind(n);
  for (int i = 0; i < n; i++) {
    cin >> p[i];
    ind[p[i] - 1] = i;
  }
  int l = 0;
  int r = n;
  while (l + 1 < r) {
    int mid = (l + r) / 2;
    string curr;
    curr = "";
    for (int i = 0; i < n; i++) {
      if (ind[i] >= mid) {
        curr += s[i];
      }
    }
    int k = curr.size();
    int j = 0;
    for (int i = 0; i < k && j < m; i++) {
      if (curr[i] == t[j]) {
        j++;
      }
    }
    if (j != m) {
      r = mid;
    } else {
      l = mid;
    }
  }
  cout << l << "\n";
}
