class Solution {
 public:
  Node* connect(Node* root) {
    std::function<void(Node*)> go = [&](Node* node) {
      if (node == nullptr) {
        return;
      }
      else {
        if (node->left != nullptr) {
          node->left->next = node->right;
        }
        if (node->right != nullptr) {
          if (node->next != nullptr) {
            node->right->next = node->next->left;
          }
          else {
            node->right->next = nullptr;
          }
        }
        go(node->left);
        go(node->right);
      }
    };

    return go(root), root;
  }
};
