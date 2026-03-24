#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  std::cout.tie(0);
  int n;
  int m;
  cin >> n >> m;
  vector<int> c(n + 1);
  vector<int> w(n + 1);
  for (int i = 1; i <= n; i++) {
    cin >> w[i];
  }
  for (int i = 1; i <= n; i++) {
    cin >> c[i];
  }
  vector<vector<int>> dp(n + 1, vector<int>(m + 1));
  for (int i = 1; i <= n; i++) {
    for (int j = 0; j <= m; j++) {
      dp[i][j] = dp[i - 1][j];
      if (j >= w[i]) {
        dp[i][j] = std::max(dp[i][j], dp[i - 1][j - w[i]] + c[i]);
      }
    }
  }
  int cur = m;
  for (int i = n; i >= 1; i--) {
    if (dp[i][cur] != dp[i - 1][cur]) {
      cout << i << "\n";
      cur -= w[i];
    }
  }
}
