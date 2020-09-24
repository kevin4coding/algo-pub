xclass Solution {
 public:
  int distributeCoins(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;

    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return n->val + f(n->left) + f(n->right) - 1;
          }
        }());
      }
    };

    // doesn't have to memoize but do it anyway, LOL. 
    std::function<int(TreeNode*)> g = [&](TreeNode *n) {
      auto & memo = mempool.g;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return std::abs(f(n)) + g(n->left) + g(n->right);
          }
        }());
      }
    };

    return g(root);
  }
};
