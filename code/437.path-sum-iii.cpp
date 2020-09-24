class Solution {
 public:
  int pathSum(TreeNode* root, int sum) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::unordered_map<int, std::optional<int>>> g;
    } mempool;

    std::function<int(TreeNode*, int)> g = [&g, &sum, &memo = mempool.g](TreeNode* n, int acc) {
      if (memo[n][acc].has_value()) {
        return memo[n][acc].value();
      }
      else {
        return memo[n][acc].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return (acc + n->val == sum ? 1 : 0) + g(n->left, acc + n->val) + g(n->right, acc + n->val);
          }
        }());
      };
    };

    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      if (n == nullptr) {
        return 0;
      }
      else {
        return g(n, 0) + f(n->left) + f(n->right);
      }
    };

    return f(root);
  }
};
