class Solution {
 public:
  vector<int> largestValues(TreeNode* root) {
    const auto candidate = [&](std::unordered_map<int, std::optional<int>> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int level) {
        if (n == nullptr) {
          return;
        }
        else {
          self[level] = std::make_optional(std::max(self[level].value_or(INT_MIN), n->val));
          fold(n->left, level + 1);
          fold(n->right, level + 1);
        }
      };
      return fold(root, 0), self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(std::size(candidate));
      for (const auto [level, val] : candidate) {
        self[level] = val.value();
      }
      return self;
    }();

    return solution;
  }
};
