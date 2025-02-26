#include <iostream>
#include <memory>
#include <set>
#include <stack>
#include <vector>
template <class T> struct Node {
  T value;
  std::shared_ptr<Node<T>> left;
  std::shared_ptr<Node<T>> right;
  Node(T val) : value(val), left(nullptr), right(nullptr) {}
};

template <class T> std::vector<T> flatten_tree(Node<T> *root) {
  std::vector<T> values;
  std::stack<Node<T> *> stack;
  stack.push(root);
  std::set<Node<T> *> visited;
  while (!stack.empty()) {
    Node<T> *n = stack.top();
    stack.pop();

    if (visited.find(n) == visited.end()) {
      visited.insert(n);
      values.push_back(n->value);
    }

    if (n->right != nullptr && visited.find(n->right.get()) == visited.end()) {
      stack.push(n->right.get());
    }

    if (n->left != nullptr && visited.find(n->left.get()) == visited.end()) {
      stack.push(n->left.get());
    }
  }
  return values;
}

int main(int argc, char *argv[]) {
  std::shared_ptr<Node<int>> root{std::make_shared<Node<int>>(1)};
  Node<int> n1{2};
  Node<int> n2{3};
  Node<int> n3{4};
  Node<int> n4{5};
  Node<int> n5{6};
  Node<int> n6{7};
  root->left = std::make_shared<Node<int>>(n1);
  root->right = std::make_shared<Node<int>>(n2);
  n1.left = std::make_shared<Node<int>>(n3);
  n1.right = std::make_shared<Node<int>>(n4);
  n2.left = std::make_shared<Node<int>>(n5);
  n2.right = std::make_shared<Node<int>>(n6);
  const auto &flattened_tree = flatten_tree(root.get());
  for (const auto &v : flattened_tree) {
    std::cout << v << ",";
  };
  std::cout << std::endl;
  return 0;
}
