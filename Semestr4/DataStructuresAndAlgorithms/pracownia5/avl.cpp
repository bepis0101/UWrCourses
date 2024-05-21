#include <bits/stdc++.h>

using namespace std;

class Node {
  public:
    long long key;
    short height;
    Node* left;
    Node* right;
};

short height(Node* N) {
  if(N == nullptr) {
    return 0;
  }
  return N->height;
}

Node* createNode(long long key) {
  Node* node = new Node();
  node->key = key;
  node->left = nullptr;
  node->right = nullptr;
  node->height = 1;
  return (node);
}

Node* rotateR(Node* node) {
  Node* x = node->left;
  Node* T2 = x->right;
  x->right = node;
  node->left = T2;
  node->height = max(height(node->left), height(node->right)) + 1;
  x->height = max(height(x->left), height(x->right)) + 1;
  return x;
}

Node* rotateL(Node* node) {
  Node* y = node->right;
  Node* T2 = y->left;
  y->left = node;
  node->right = T2;
  node->height = max(height(node->left), height(node->right)) + 1;
  y->height = max(height(y->left), height(y->right)) + 1;
  return y;
}

int getBalance(Node* N) {
  if(N == nullptr) {
    return 0;
  }
  return height(N->left) - height(N->right);
}

Node* insert(Node* node, long long key) {
  if(node == nullptr) {
    return createNode(key);
  }
  if(key < node->key) {
    node->left = insert(node->left, key);
  } else if(key > node->key) {
    node->right = insert(node->right, key);
  } else {
    return node;
  }
  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);
  if(balance > 1 && key < node->left->key) {
    return rotateR(node);
  }
  if(balance < -1 && key > node->right->key) {
    return rotateL(node);
  }
  if(balance > 1 && key > node->left->key) {
    node->left = rotateL(node->left);
    return rotateR(node);
  }
  if(balance < -1 && key < node->right->key) {
    node->right = rotateR(node->right);
    return rotateL(node);
  }
  return node;
}

Node* deleteNode(Node* node, long long key, bool& deleted) {
  if(node == nullptr) {
    return node;
  }
  if(key < node->key) {
    node->left = deleteNode(node->left, key, deleted);
  } else if(key > node->key) {
    node->right = deleteNode(node->right, key, deleted);
  } else {
    deleted = true;
    if(node->left == nullptr || node->right == nullptr) {
      Node* temp = node->left ? node->left : node->right;
      if(temp == nullptr) {
        temp = node;
        node = nullptr;
      } else {
        *node = *temp;
      }
      delete temp;
    } else {
      Node* temp = node->right;
      while(temp->left != nullptr) {
        temp = temp->left;
      }
      node->key = temp->key;
      node->right = deleteNode(node->right, temp->key, deleted);
    }
  }

  if(node == nullptr) {
    return node;
  }
  node->height = 1 + max(height(node->left), height(node->right));
  int balance = getBalance(node);
  if(balance > 1 && getBalance(node->left) >= 0) {
    return rotateR(node);
  }
  if(balance > 1 && getBalance(node->left) < 0) {
    node->left = rotateL(node->left);
    return rotateR(node);
  }
  if(balance < -1 && getBalance(node->right) <= 0) {
    return rotateL(node);
  }
  if(balance < -1 && getBalance(node->right) > 0) {
    node->right = rotateR(node->right);
    return rotateL(node);
  }
  return node;
}

void printAvl(Node* node) {
  if(node != nullptr) {
    printAvl(node->left);
    cout << node->key << " ";
    printAvl(node->right);
  }
}
Node* upper(Node* root, long long x) {
  Node* curr = root;
  Node* succ = nullptr;
  while(curr != nullptr) {
    if(curr->key > x) {
      succ = curr;
      curr = curr->left;
    } else if(curr->key == x) {
      return curr;
    }
     else {
      curr = curr->right;
    }
  }
  return succ;
}

Node* lower(Node* root, long long x) {
  Node* curr = root;
  Node* pred = nullptr;
  while(curr != nullptr) {
    if(curr->key < x) {
      pred = curr;
      curr = curr->right;
    } else if(curr->key == x) {
      return curr;
    }
    else {
      curr = curr->left;
    }
  }
  return pred;
}

int main() {
  ios_base::sync_with_stdio(false);
  cin.tie(nullptr);
  cout.tie(nullptr);
  int n; cin >> n;
  Node* root = nullptr;
  for(int i = 0; i < n; i++) {
    char c; long long x; 
    cin >> c >>  x;
    if(c == 'I') {
      if(root == nullptr) {
          root = createNode(x);
        } else {
          root = insert(root, x);
        }
    } else if(c == 'D') {
      bool deleted = false;
      root = deleteNode(root, x, deleted);
      if(!deleted) {
        cout << "BRAK\n";
      } else {
        cout << "OK\n";
      }
    } else if(c == 'U') {
      Node* res = upper(root, x);
      if(res == nullptr) {
        cout << "BRAK\n";
      } else {
        cout << res->key << "\n";
      }
    } else if(c == 'L') {
      Node* res = lower(root, x);
      if(res == nullptr) {
        cout << "BRAK\n";
      } else {
        cout << res->key << "\n";
      }
    } 
  }
  return 0;
}
