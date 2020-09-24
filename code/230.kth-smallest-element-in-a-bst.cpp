class Solution {
 public:
  int kthSmallest(TreeNode* root, int k) {
    const auto solution = [&, time_stamp = 0](std::optional<int> self = {}) mutable {
      std::function<void(TreeNode*)> fold = [&](TreeNode* node) {
        if (self.has_value() or node == nullptr) {
          return;
        }
        else if (node->left == nullptr and node->right == nullptr) {
          if (++time_stamp == k) {
            self.emplace(node->val);
          }
        }
        else {
          fold(node->left);
          if (++time_stamp == k) {
            self.emplace(node->val);
          }
          fold(node->right);
        }
      };

      return fold(root), self;
    }();

    return solution.value();
  }
};
