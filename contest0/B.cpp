#include <cmath>
#include <iomanip>
#include <iostream>
#include <vector>

using namespace std;

const int cSigns = 10;

int main() {
  int n;
  cin >> n;
  vector<double> a(n);
  vector<double> pref(n + 1);
  for (int i = 0; i < n; i++) {
    cin >> a[i];
    pref[i + 1] = pref[i] + log(a[i]);
  }
  int q;
  cin >> q;
  cout << setprecision(cSigns) << fixed;
  while ((q--) > 0) {
    int l;
    int r;
    cin >> l >> r;
    double res = exp((pref[r + 1] - pref[l]) / (r - l + 1));
    cout << res << "\n";
  }
}
