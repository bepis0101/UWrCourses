#include <bits/stdc++.h>

using namespace std;

class Node {
  public:
    long long key;
    short height;
    Node* left;
    Node* right;
    Node(long long key) {
      this->key = key;
      this->height = 1;
      this->left = nullptr;
      this->right = nullptr;
    }
    short maks(Node* a, Node* b) {
      if(a == nullptr && b == nullptr) return 0;
      if(a == nullptr) return b->height;
      if(b == nullptr) return a->height;
      return a->height > b->height ? a->height : b->height;
    }
    Node* rotateR(Node* node) {
      cerr << "rotateR on node " << node->key <<  '\n';
      Node* x = node->left;
      Node* T = x->right;
      x->right = node;
      node->left = T;
      node->height = maks(node->left, node->right) + 1;
      x->height = maks(x->left, x->right) + 1;
      return x;
    }

    Node* rotateL(Node* node) {
      cerr << "rotateL on node " << node->key << '\n';
      Node* x = node->right;
      Node* T = x->left;
      x->left = node;
      node->right = T;
      node->height = maks(node->left, node->right) + 1;
      x->height = maks(x->left, x->right) + 1;
      return x;
    }
    void print(Node* node) {
      if(node == nullptr) return;
      print(node->left);
      cout << node->key << " ";
      print(node->right);
    }
    short getBalance(Node* node) {
      if(node == nullptr) return 0;
      if(node->left == nullptr && node->right == nullptr) return 0;
      if(node->left == nullptr) return -node->right->height;
      if(node->right == nullptr) return node->left->height;
      return node->left->height - node->right->height;
    }

    Node* find(long long val) {
      if(this->key == val) {
        return this;
      } else if(val < this->key) {
        if(this->left == nullptr) {
          return nullptr;
        } else {
          return this->left->find(val);
        }
      } else {
        if(this->right == nullptr) {
          return nullptr;
        } else {
          return this->right->find(val);
        }
      }
    }

    Node* insert(Node* node, long val) {
      if(find(val) != nullptr) {
        cerr << "Element already exists" << '\n';
        return this;
      }
      Node *newNode = new Node(val);
      if(val < node->key) {
        if(node->left == nullptr) {
          node->left = newNode;
        } else {
          node->left = insert(node->left, val);
        }
      } else if(val > node->key) {
        if(node->right == nullptr) {
          node->right = newNode;
        } else {
          node->right = insert(node->right, val);
        }
      } else {
        return node;
      }
      node->height = maks(node->left, node->right) + 1;
      short balance = getBalance(node);
      if(balance > 1 && val < node->left->key) {
        return rotateR(node);
      } else if(balance < -1 && val > node->right->key) {
        return rotateL(node);
      } else if(balance > 1 && val > node->left->key) {
        node->left = rotateL(node->left);
        return rotateR(node);
      } else if(balance < -1 && val < node->right->key) {
        node->right = (node->right);
        return rotateL(node);
      }
      return node;
    }

    Node* del(long long val) {
      val++;
      return this;
    }

    long long lower(long long x) {
      return x;
    }

    long long upper(long long x) {
      return x;
    }

};

int main() {
  // ios_base::sync_with_stdio(false);
  // cin.tie(nullptr);
  // cout.tie(nullptr);
  int n; cin >> n;
  Node* root = nullptr;
  for(int i = 0; i < n; i++) {
    char c; long long x; 
    cin >> c >>  x;
    switch (c) {
      case 'I':
        if(root == nullptr) {
          root = new Node(x);
        } else {
          root->insert(root, x);
        }
        root->print(root);
        break;
      case 'D':
        break;
      case 'U':
        break;
      case 'L':
        break;
      default:  
        throw invalid_argument("Invalid command");  
        break;
    }
  }
  return 0;
}