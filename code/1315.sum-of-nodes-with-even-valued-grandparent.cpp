class Solution {
 public:
  int sumEvenGrandparent(TreeNode* root) {
    const auto parent = [&](std::unordered_map<TreeNode*, TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->left != nullptr) {
            self[n->left] = n;
          }
          if (n->right != nullptr) {
            self[n->right] = n;
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    auto grandparent = [&](TreeNode *n) -> std::optional<TreeNode*> {
      if (parent.count(n) and parent.count(parent.at(n))) {
        return std::make_optional(parent.at(parent.at(n)));
      }
      else {
        return std::nullopt;
      }
    };

    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (grandparent(n).has_value() and (grandparent(n).value())->val % 2 == 0) {
            acc += n->val;
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution;
      
  }
};
