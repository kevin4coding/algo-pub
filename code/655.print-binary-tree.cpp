class Solution {
 public:
  vector<vector<string>> printTree(TreeNode* root) {
    const auto h = [&]() {
      std::function<int(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == 0) {
          return 0;
        }
        else {
          return 1 + std::max(fold(n->left), fold(n->right));
        }
      };
      return fold(root);
    }();

    const auto column_width = static_cast<int>(std::pow(2, h)) - 1;
    
    const auto solution = [&](std::vector<std::vector<std::string>> self = {}) {
      self.resize(h, std::vector<std::string>(column_width, std::string{}));
      std::function<void(TreeNode*, int, int, int)> fold = [&](TreeNode* n, int level, int ll, int rr) {
        if (n == nullptr) {
          return;
        }
        else {
          const int mid = ll + (rr - ll) / 2;
          std::exchange(self[level][mid], std::to_string(n->val));
          fold(n->left, level + 1, ll, mid - 1);
          fold(n->right, level + 1, mid + 1, rr);
        }
      };
      return fold(root, 0, 0, column_width - 1), self;
    }();

    return solution;
  }
};
