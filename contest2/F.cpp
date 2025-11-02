#include <deque>
#include <iostream>
#include <queue>

using std::cin;
using std::cout;
using std::deque;
using std::queue;

struct MinQueue {
  deque<std::pair<int, int>> d;
  queue<int> q;
  int l = 0;
  int r = 0;
  void Enqueue(int x) {
    q.push(x);
    while (!d.empty() && d.back().first >= x) {
      d.pop_back();
    }
    d.push_back({x, r});
    r++;
  }
  int Dequeue() {
    if (q.empty()) {
      return -1;
    }
    int res = q.front();
    q.pop();
    if (d.front().second == l) {
      d.pop_front();
    }
    l++;
    return res;
  }
  int Front() {
    if (q.empty()) {
      return -1;
    }
    return q.front();
  }
  int Size() const { return r - l; }
  void Clear() {
    while (!q.empty()) {
      q.pop();
    }
    while (!d.empty()) {
      d.pop_back();
    }
    l = r = 0;
  }
  int Min() {
    if (q.empty()) {
      return -1;
    }
    return d.front().first;
  }
};

void Cout(int x) {
  if (x != -1) {
    cout << x << "\n";
  } else {
    cout << "error\n";
  }
}
int main() {
  MinQueue q;
  int n;
  cin >> n;
  std::string s;
  int x;
  while ((n--) > 0) {
    cin >> s;
    if (s == "enqueue") {
      cin >> x;
      q.Enqueue(x);
      cout << "ok\n";
    } else if (s == "dequeue") {
      Cout(q.Dequeue());
    } else if (s == "front") {
      Cout(q.Front());
    } else if (s == "size") {
      Cout(q.Size());
    } else if (s == "clear") {
      q.Clear();
      cout << "ok\n";
    } else {
      Cout(q.Min());
    }
  }
}
