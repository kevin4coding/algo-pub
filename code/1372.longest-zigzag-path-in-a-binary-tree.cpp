class Solution {
 public:
  int longestZigZag(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;

    std::function<int(TreeNode*)> f, g;
    
    f = [&](TreeNode* n) {
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
            return 1 + g(n->right);
          }
        }());
      }
    };

    g = [&](TreeNode* n) {
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
            return 1 + f(n->left);
          }
        }());
      }
    };

    const auto solution = [&](int acc = INT_MIN) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          acc = std::max({acc, f(n), g(n)});
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc - 1;
    }();

    return solution;
    
  }
};
