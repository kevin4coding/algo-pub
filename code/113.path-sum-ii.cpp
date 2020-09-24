class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, int sum) {

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      std::function<void(TreeNode*, int)> go = [&, cache = std::vector<int>{}](TreeNode* node, int acc) mutable {
        if (node == nullptr) {
          return;
        }
        else if (node->left == nullptr and node->right == nullptr) {
          if (acc + node->val == sum) {
            cache.emplace_back(node->val);
            self.emplace_back(cache);
            cache.pop_back();
          }
          return;
        }
        else {
          if (node->left != nullptr) {
            cache.emplace_back(node->val);
            go(node->left, acc + node->val);
            cache.pop_back();
          }
          if (node->right != nullptr) {
            cache.emplace_back(node->val);
            go(node->right, acc + node->val);
            cache.pop_back();
          }
        }
      };
      return go(root, 0), self;
    }();

    return solution;
  }
};
