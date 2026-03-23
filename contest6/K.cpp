#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

const int cInf = 2147483647;
int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  std::cout.tie(0);
  int n;
  cin >> n;
  vector<int> a(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> a[i];
  }
  vector<int> dp(n + 1, cInf);
  vector<int> ind(n + 1, -1);
  vector<int> pr(n + 1, -1);
  dp[0] = -cInf;
  int len = 0;
  for (int i = 1; i <= n; i++) {
    int pos = lower_bound(dp.begin(), dp.end(), -a[i]) - dp.begin();
    dp[pos] = -a[i];
    ind[pos] = i;
    pr[i] = ind[pos - 1];
    len = std::max(len, pos);
  }
  cout << len << "\n";
  vector<int> ans;
  int cur = ind[len];
  while (cur != -1) {
    ans.push_back(cur);
    cur = pr[cur];
  }
  reverse(ans.begin(), ans.end());
  for (auto el : ans) {
    cout << el << " ";
  }
}
