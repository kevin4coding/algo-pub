class Solution {
 public:
  vector<int> rightSideView(TreeNode* root) {
    const auto candidate = [&](std::unordered_map<int, std::optional<int>> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* node, int height) {
        if (node == nullptr) {
          return;
        }
        else {
          if (not self[height].has_value())
            self[height].emplace(node->val);
          fold(node->right, height + 1);
          fold(node->left, height + 1);
        }
      };
      return fold(root, 0), self;
    }();

    const auto solution = [&](std::vector<int> self = {}) {
      self.resize(std::size(candidate));
      for (const auto [h, val] : candidate) {
        self[h] = val.value();
      }
      return self;
    }();


    return solution;
  }
};
