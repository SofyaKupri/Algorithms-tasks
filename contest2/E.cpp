#include <deque>
#include <iostream>

using std::cin;
using std::cout;
using std::deque;

struct MidQueue {
  deque<int> q1;
  deque<int> q2;
  void Balance() {
    if (q1.size() < q2.size()) {
      q1.push_back(q2.front());
      q2.pop_front();
    }
  }
  void PushBack(int x) {
    q2.push_back(x);
    Balance();
  }
  void PushMiddle(int x) {
    q2.push_front(x);
    Balance();
  }
  int GetFront() {
    int res = q1.front();
    q1.pop_front();
    Balance();
    return res;
  }
};
int main() {
  MidQueue q;
  int n;
  cin >> n;
  char c;
  int x;
  for (int i = 0; i < n; i++) {
    cin >> c;
    if (c == '+') {
      cin >> x;
      q.PushBack(x);
    } else if (c == '*') {
      cin >> x;
      q.PushMiddle(x);
    } else {
      cout << q.GetFront() << "\n";
    }
  }
}
