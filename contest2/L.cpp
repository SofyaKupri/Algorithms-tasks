#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::swap;
using std::vector;

struct BinaryHeap {
 private:
  vector<std::pair<int, int>> a_;
  vector<int> ind_;
  int cur_ = 1;
  void SiftUp(int v) {
    if (v == 0) {
      return;
    }
    int p = (v - 1) / 2;
    if (a_[v] < a_[p]) {
      swap(a_[v], a_[p]);
      SiftUp(p);
    }
  }
  void SiftDown(int v) {
    if (2 * v + 1 >= n) {
      return;
    }
    int u = 2 * v + 1;
    if (2 * v + 2 < n && a_[2 * v + 2] < a_[u]) {
      u = 2 * v + 2;
    }
    if (a_[u] < a_[v]) {
      swap(a_[u], a_[v]);
      SiftDown(u);
    }
  }

 public:
  int n;
  BinaryHeap(int q) {
    n = 0;
    ind_.resize(q);
  }
  void Insert(int x, int i) {
    a_.push_back({x, i});
    ind_[i] = cur_;
    n++;
    SiftUp(n - 1);
  }
  void ExtractMin() {
    swap(a_[0], a_[n - 1]);
    ind_[a_[n - 1].second] = 0;
    n--;
    a_.pop_back();
    if (!a_.empty()) {
      SiftDown(0);
    }
  }
  std::pair<int, int> GetMin() {
    while (!a_.empty() && ind_[a_[0].second] != cur_) {
      ExtractMin();
    }
    if (!a_.empty()) {
      return a_[0];
    }
    return {-1, -1};
  }
  void Delete(int i) { ind_[i] = 0; }
  void Clear() {
    n = 0;
    a_.clear();
    cur_++;
  }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  int q;
  cin >> q;
  BinaryHeap mn(q);
  BinaryHeap mx(q);
  int n = 0;
  for (int i = 0; i < q; i++) {
    char c;
    cin >> c;
    if (c == '0') {
      cout << "ok\n";
      n++;
      int x;
      cin >> x;
      mn.Insert(x, i);
      mx.Insert(-x, i);
    } else if (c == '1') {
      if (n == 0) {
        cout << "error\n";
        continue;
      }
      n--;
      auto [x, ind] = mn.GetMin();
      cout << x << "\n";
      mn.ExtractMin();
      mx.Delete(ind);
    } else if (c == '2') {
      if (n == 0) {
        cout << "error\n";
        continue;
      }
      auto [x, ind] = mn.GetMin();
      cout << x << "\n";
    } else if (c == '3') {
      if (n == 0) {
        cout << "error\n";
        continue;
      }
      n--;
      auto [x, ind] = mx.GetMin();
      cout << -x << "\n";
      mx.ExtractMin();
      mn.Delete(ind);
    } else if (c == '4') {
      if (n == 0) {
        cout << "error\n";
        continue;
      }
      auto [x, ind] = mx.GetMin();
      cout << -x << "\n";
    } else if (c == '5') {
      cout << n << "\n";
    } else {
      cout << "ok\n";
      n = 0;
      mx.Clear();
      mn.Clear();
    }
  }
}
