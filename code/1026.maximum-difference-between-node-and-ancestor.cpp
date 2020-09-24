class Solution {
 public:
  int maxAncestorDiff(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;

    // max
    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return INT_MIN;
          }
          else {
            return std::max({n->val, f(n->left), f(n->right)});
          }
        }());
      }
    };

    std::function<int(TreeNode*)> g = [&](TreeNode* n) {
      auto & memo = mempool.g;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return INT_MAX;
          }
          else {
            return std::min({n->val, g(n->left), g(n->right)});
          }
        }());
      }
    };

    const auto solution = [&](int acc = INT_MIN) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return; //
        }
        else {
          if (n->left == nullptr and n->right != nullptr) {
            acc = std::max({acc,
                            std::abs(n->val - g(n->right)),
                            std::abs(f(n->right) - n->val)});
          }
          else if (n->left != nullptr and n->right == nullptr) {
            acc = std::max({acc,
                            std::abs(n->val - g(n->left)),
                            std::abs(f(n->left) - n->val)});
          }
          else if (n->left != nullptr and n->right != nullptr) {
            acc = std::max({acc,
                            std::abs(n->val - g(n->right)),
                            std::abs(f(n->right) - n->val),
                            std::abs(n->val - g(n->left)),
                            std::abs(f(n->left) - n->val)});
          }
          else if (n->left == nullptr and n->right == nullptr) {
            // do nothing
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution;
  }
};
