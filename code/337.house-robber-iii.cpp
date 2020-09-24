fclass Solution {
 public:
  int rob(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
      mutable std::unordered_map<TreeNode*, std::optional<int>> h;
    } mempool;

    std::function<int(TreeNode*)> f, g;
    // take
    f = [&f, &g, &memo = mempool.f](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return n->val + g(n->left) + g(n->right);
          }
        }());
      }
    };

    // not take 
    g = [&f, &g, &memo = mempool.g](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return std::max(g(n->left), f(n->left)) + std::max(f(n->right), g(n->right));
          }
        }());
      }
    };

    std::function<int(TreeNode*)> h = [&f, &g, &h, &memo = mempool.h](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return std::max(g(n), f(n));
          }
        }());
      }
    };

    return h(root);
  }
};
