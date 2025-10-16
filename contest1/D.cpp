#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

const uint64_t cSize = 256;
const uint64_t cBite = 8;

uint64_t Digit(uint64_t x, uint64_t i) { return (x >> (i * cBite)) % cSize; }

void LSD(vector<uint64_t>& a, uint64_t n) {
  vector<uint64_t> cnt(cSize);
  vector<uint64_t> cur(n);
  for (uint64_t i = 0; i < cBite; i++) {
    for (uint64_t j = 0; j < cSize; j++) {
      cnt[j] = 0;
    }
    for (uint64_t j = 0; j < n; j++) {
      cnt[Digit(a[j], i)]++;
    }
    uint64_t size = 0;
    for (uint64_t j = 0; j < cSize; j++) {
      size += cnt[j];
      cnt[j] = size - cnt[j];
    }
    for (uint64_t j = 0; j < n; j++) {
      cur[cnt[Digit(a[j], i)]] = a[j];
      cnt[Digit(a[j], i)]++;
    }
    for (uint64_t j = 0; j < n; j++) {
      a[j] = cur[j];
    }
  }
}

int main() {
  uint64_t n;
  cin >> n;
  vector<uint64_t> a(n);
  for (uint64_t i = 0; i < n; i++) {
    cin >> a[i];
  }
  LSD(a, n);
  for (uint64_t i = 0; i < n; i++) {
    cout << a[i] << " ";
  }
  cout << "\n";
}
