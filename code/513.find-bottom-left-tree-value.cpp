class Solution {
 public:
  int findBottomLeftValue(TreeNode* root) {
    const auto tree_depth = [&]() {
      std::function<int(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return 0;
        }
        else {
          return 1 + std::max(fold(n->left), fold(n->right));
        }
      };
      return fold(root);
    }();

    const auto solution = [&](std::optional<TreeNode*> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int level) {
        if (n == nullptr or self.has_value()) {
          return;
        }
        else {
          if (level == tree_depth) {
            self.emplace(n);
          }
          fold(n->left, level + 1);
          fold(n->right, level + 1);
        }
      };
      return fold(root, 1), self.value();
    }();

    return solution->val;
  }
};
