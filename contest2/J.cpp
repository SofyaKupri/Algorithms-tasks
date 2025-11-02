#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::string;
using std::swap;
using std::vector;

struct BinaryHeap {
 private:
  vector<std::pair<long long, size_t>> a_;
  vector<size_t> pos_;
  size_t n_;
  void SiftUp(size_t v) {
    if (v == 0) {
      return;
    }
    size_t p = (v - 1) / 2;
    if (a_[v] < a_[p]) {
      swap(a_[v], a_[p]);
      pos_[a_[v].second] = v;
      pos_[a_[p].second] = p;
      SiftUp(p);
    }
  }
  void SiftDown(size_t v) {
    if (2 * v + 1 >= n_) {
      return;
    }
    size_t u = 2 * v + 1;
    if (2 * v + 2 < n_ && a_[2 * v + 2] < a_[u]) {
      u = 2 * v + 2;
    }
    if (a_[u] < a_[v]) {
      swap(a_[u], a_[v]);
      pos_[a_[v].second] = v;
      pos_[a_[u].second] = u;
      SiftDown(u);
    }
  }

 public:
  BinaryHeap(size_t q) {
    n_ = 0;
    pos_.resize(q, -1);
  }
  void Insert(size_t x, size_t i) {
    a_.push_back({x, i});
    n_++;
    pos_[i] = n_ - 1;
    SiftUp(n_ - 1);
  }
  void DecreaseKey(size_t v, long long d) {
    a_[v].first -= d;
    SiftUp(v);
  }
  void ExtractMin() {
    swap(a_[0], a_[n_ - 1]);
    pos_[a_[0].second] = 0;
    pos_[a_[n_ - 1].second] = n_ - 1;
    n_--;
    a_.pop_back();
    if (!a_.empty()) {
      SiftDown(0);
    }
  }
  long long GetMin() { return a_[0].first; }
  long long GetPos(long long i) { return pos_[i]; }
};

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(0);
  cout.tie(0);
  long long q;
  cin >> q;
  BinaryHeap h(q);
  string s;
  for (long long i = 0; i < q; i++) {
    cin >> s;
    if (s == "insert") {
      long long x;
      cin >> x;
      h.Insert(x, i);
    } else if (s == "getMin") {
      cout << h.GetMin() << "\n";
    } else if (s == "extractMin") {
      h.ExtractMin();
    } else if (s == "decreaseKey") {
      size_t ind;
      long long d;
      cin >> ind >> d;
      h.DecreaseKey(h.GetPos(ind - 1), d);
    }
  }
}
