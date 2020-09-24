class Solution {
 public:
  Node* inorderSuccessor(Node* node) {
    auto succ = [&](Node* target) -> std::optional<Node*> {
      auto result = std::optional<Node*>{};
      std::function<void(Node*)> fold = [&](Node* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->val > target->val) {
            result.emplace(n);
            fold(n->left);
          }
          else {
            fold(n->right);
          }
        }
      };
      return fold(target), result;
    };

    std::function<std::optional<Node*>(Node*)> first_left_child_parent = [&](Node* n) {
      if (n == nullptr or n->parent == nullptr) {
        return std::optional<Node*>{};
      }
      else if (n->parent->left == n) {
        return std::optional<Node*>{n->parent};
      }
      else {
        return first_left_child_parent(n->parent);
      }
    };
    
    const auto solution = [&](std::optional<Node*> self = {}) {
      if (node->right != nullptr) {
        self.emplace(succ(node).value());
      }
      else {
        self.emplace(first_left_child_parent(node).value_or(nullptr));
      }
      return self;
    }();

    return solution.value();
  }
};
