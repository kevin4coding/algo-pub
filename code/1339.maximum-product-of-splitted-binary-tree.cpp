class Solution {
 public:
  int maxProduct(TreeNode* root) {
    using int64 = long long;

    static constexpr int mod = 1e9 + 7;
    
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int64>> f;
    } mempool;

    std::function<int64(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return int64(0);
          }
          else {
            return n->val + f(n->left) +  f(n->right);
          }
        }());
      }
    };

    const auto solution = [&](int64 acc = 1) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n != root) {x
            acc = std::max(acc, f(n) * (f(root) - f(n)));
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution % mod;
    
  }
};
