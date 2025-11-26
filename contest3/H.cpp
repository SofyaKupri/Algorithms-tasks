#include <algorithm>
#include <iostream>
#include <vector>

using std::cin;
using std::cout;
using std::vector;

struct SegmentTree {
  struct Node {
    long long mn;
    long long cnt;
  };
  Node static Merge(Node a, Node b) {
    if (a.mn == b.mn) {
      return {a.mn, a.cnt + b.cnt};
    }
    if (a.mn < b.mn) {
      return a;
    }
    return b;
  }
  vector<long long> add;
  vector<Node> t;
  int n;
  SegmentTree(int sz) {
    n = sz;
    t.resize(4 * n);
    add.resize(4 * n);
  }
  SegmentTree(const vector<long long>& a) {
    n = a.size();
    t.resize(4 * n);
    add.resize(4 * n);
    Build(0, 0, n, a);
  }
  void Build(int v, int l, int r, const vector<long long>& a) {
    if (l + 1 == r) {
      t[v] = {0, a[l]};
      return;
    }
    int m = (l + r) / 2;
    Build(2 * v + 1, l, m, a);
    Build(2 * v + 2, m, r, a);
    t[v] = Merge(t[2 * v + 1], t[2 * v + 2]);
  }
  void Push(int v, int l, int r) {
    if (l + 1 != r) {
      add[2 * v + 1] += add[v];
      add[2 * v + 2] += add[v];
    }
    t[v].mn += add[v];
    add[v] = 0;
  }
  long long GetMin() { return t[0].mn; }
  long long GetCnt() { return t[0].cnt; }
  void Update(int v, int l, int r, int ql, int qr, long long val) {
    Push(v, l, r);
    if (l >= qr || ql >= r) {
      return;
    }
    if (ql <= l && qr >= r) {
      add[v] += val;
      Push(v, l, r);
      return;
    }
    int m = (l + r) / 2;
    Update(2 * v + 1, l, m, ql, qr, val);
    Update(2 * v + 2, m, r, ql, qr, val);
    t[v] = Merge(t[2 * v + 1], t[2 * v + 2]);
  }
  void Update(int ql, int qr, long long val) { Update(0, 0, n, ql, qr, val); }
};

struct Event {
  long long x, y1, y2, t;
};
bool Compare(Event a, Event b) {
  return a.x < b.x || (a.x == b.x && a.t < b.t);
}

int main() {
  std::ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n;
  cin >> n;
  vector<long long> y;
  vector<Event> p;
  for (int i = 0; i < n; i++) {
    int x1;
    int y1;
    int x2;
    int y2;
    cin >> x1 >> y1 >> x2 >> y2;
    p.push_back({x1, y1, y2, 1});
    p.push_back({x2, y1, y2, -1});
    y.push_back(y1);
    y.push_back(y2);
  }
  sort(y.begin(), y.end());
  sort(p.begin(), p.end(), Compare);
  y.resize(unique(y.begin(), y.end()) - y.begin());
  int m = y.size() - 1;
  vector<long long> d(m, 1);
  for (int i = 0; i + 1 <= m; i++) {
    d[i] = y[i + 1] - y[i];
  }
  SegmentTree t(d);
  long long s = (y.back() - y.front()) * (p.back().x - p.front().x);
  for (int i = 0; i < 2 * n; i++) {
    int l = lower_bound(y.begin(), y.end(), p[i].y1) - y.begin();
    int r = lower_bound(y.begin(), y.end(), p[i].y2) - y.begin();
    long long val = p[i].t;
    t.Update(l, r, val);
    if (i + 1 < 2 * n && p[i].x != p[i + 1].x) {
      t.Push(0, 0, m);
      if (t.GetMin() == 0) {
        s -= t.GetCnt() * (p[i + 1].x - p[i].x);
      }
    }
  }
  cout << s << "\n";
}
