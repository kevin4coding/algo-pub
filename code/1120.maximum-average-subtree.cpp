class Solution {
 public:
  double maximumAverageSubtree(TreeNode* root) {
    struct tree_info_t {
      int size;
      int sum;
    };

    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<tree_info_t>> f;
      mutable std::unordered_map<TreeNode*, std::optional<double>> g;
    } mempool;

    std::function<tree_info_t(TreeNode*)> f = [&](TreeNode* n) -> tree_info_t {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return tree_info_t{0, 0};
          }
          else {
            return tree_info_t{1 + f(n->left).size + f(n->right).size,
                               n->val + f(n->left).sum + f(n->right).sum};
          }
        }());
      }
    };

    std::function<double(TreeNode*)> g = [&](TreeNode* n) {
      auto & memo = mempool.g;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return DBL_MIN;
          }
          else {
            return std::max({double(f(n).sum) / double(f(n).size), g(n->left), g(n->right)});
          }
        }());
      }
    };

    return g(root);
  }
};
