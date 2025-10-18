#include <iostream>
#include <vector>

using namespace std;

const int c0 = 123;
const int c1 = 45;
const int c2 = 1e7 + 4321;
const int cMid = 10;

int GetMedian(vector<int>& a, int l, int r) {
  for (int i = l + 1; i <= r; i++) {
    for (int j = i; j > l; j--) {
      if (a[j] < a[j - 1]) {
        swap(a[j], a[j - 1]);
      }
    }
  }
  return l + (r - l) / 2;
}

int QuickSelect(vector<int>& a, int l, int r, int k);

int GetPivot(vector<int>& a, int l, int r) {
  if (r - l < 5) {
    return GetMedian(a, l, r);
  }
  for (int i = l; i <= r; i += 5) {
    swap(a[GetMedian(a, i, min(i + 4, r))], a[l + (i - l) / 5]);
  }
  int mid = (r - l) / cMid + l + 1;
  return QuickSelect(a, l, l + (r - l) / 5, mid);
}

int Partition(vector<int>& a, int l, int r, int pivot, int k) {
  int pivot_value = a[pivot];
  swap(a[pivot], a[r]);
  int ind_l = l;
  for (int i = l; i < r; i++) {
    if (a[i] < pivot_value) {
      swap(a[ind_l], a[i]);
      ind_l++;
    }
  }
  int ind_m = ind_l;
  for (int i = ind_l; i < r; i++) {
    if (a[i] == pivot_value) {
      swap(a[ind_m], a[i]);
      ind_m++;
    }
  }
  swap(a[r], a[ind_m]);
  if (k < ind_l) {
    return ind_l;
  }
  if (k <= ind_m) {
    return k;
  }
  return ind_m;
}

int QuickSelect(vector<int>& a, int l, int r, int k) {
  while (true) {
    if (l == r) {
      return l;
    }
    int pivot = Partition(a, l, r, GetPivot(a, l, r), k);
    if (k == pivot) {
      return k;
    }
    if (k < pivot) {
      r = pivot - 1;
    } else {
      l = pivot + 1;
    }
  }
}

int main() {
  int n;
  int k;
  cin >> n >> k;
  vector<int> a(n);
  cin >> a[0] >> a[1];
  for (int i = 2; i < n; i++) {
    a[i] = (a[i - 1] * c0 + a[i - 2] * c1) % c2;
  }
  cout << a[QuickSelect(a, 0, n - 1, k - 1)] << "\n";
}
