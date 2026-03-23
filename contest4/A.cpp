#include <iostream>

const int cMod = 1e9;

struct Node {
  int key;
  int height;
  Node *left, *right;
  Node(int x) : key(x), height(1), left(nullptr), right(nullptr) {}
};
int GetHeight(Node* t) {
  if (t == nullptr) {
    return 0;
  }
  return t->height;
}
void Update(Node* t) {
  if (t != nullptr) {
    t->height = 1 + std::max(GetHeight(t->left), GetHeight(t->right));
  }
}
int GetDiffrence(Node* t) {
  if (t != nullptr) {
    return GetHeight(t->left) - GetHeight(t->right);
  }
  return 0;
}
Node* LeftRotation(Node* a) {
  Node* b = a->right;
  Node* p = b->left;
  b->left = a;
  a->right = p;
  Update(a);
  Update(b);
  return b;
}
Node* RightRotation(Node* b) {
  Node* a = b->left;
  Node* q = a->right;
  a->right = b;
  b->left = q;
  Update(b);
  Update(a);
  return a;
}
Node* Balance(Node* t) {
  Update(t);
  int d = GetDiffrence(t);
  if (d == 2) {
    if (GetDiffrence(t->left) == -1) {
      t->left = LeftRotation(t->left);
    }
    return RightRotation(t);
  }
  if (d == -2) {
    if (GetDiffrence(t->right) == 1) {
      t->right = RightRotation(t->right);
    }
    return LeftRotation(t);
  }
  return t;
}
Node* Insert(Node* root, int key) {
  if (root == nullptr) {
    return new Node(key);
  }
  if (key == root->key) {
    return root;
  }
  if (key < root->key) {
    root->left = Insert(root->left, key);
  } else {
    root->right = Insert(root->right, key);
  }
  return Balance(root);
}
int LowerBound(Node* root, int x) {
  int res = -1;
  Node* cur = root;
  while (cur != nullptr) {
    if (cur->key >= x) {
      res = cur->key;
      cur = cur->left;
    } else {
      cur = cur->right;
    }
  }
  return res;
}
void Free(Node* t) {
  if (t == nullptr) {
    return;
  }
  Free(t->left);
  Free(t->right);
  delete t;
}
int main() {
  int q;
  std::cin >> q;
  Node* root = nullptr;
  int last_ans = 0;
  char c;
  int x;
  while ((q--) > 0) {
    std::cin >> c >> x;
    if (c == '+') {
      if (last_ans == 0) {
        root = Insert(root, x);
      } else {
        root = Insert(root, (x + last_ans) % cMod);
      }
      last_ans = 0;
    } else {
      last_ans = LowerBound(root, x);
      std::cout << last_ans << "\n";
    }
  }
  Free(root);
}
