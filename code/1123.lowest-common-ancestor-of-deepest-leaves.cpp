class Solution {
 public:
  TreeNode* lcaDeepestLeaves(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;
    
    const auto depth = [&](std::unordered_map<TreeNode*, int> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int d) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->left == nullptr and n->right == nullptr) {
            self[n] = d;
          }
          fold(n->left, d + 1);
          fold(n->right, d + 1);
        }
      };
      return fold(root, 0), self;
    }();

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
          else if (n->left == nullptr and n->right == nullptr) {
            return depth.at(n);
          }
          else {
            return std::max(f(n->left), f(n->right));
          }
        }());
      }
    };

    const auto max_d = [&](int acc = 0) {
      for (const auto [_, d] : depth) {
        acc = std::max(acc, d);
      }
      return acc;
    }();

    const auto solution = [&](TreeNode* self = nullptr) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (f(n) == max_d) {
            std::exchange(self, n);
          }
          if (n->left and n->right and f(n->left) == max_d and f(n->right) == max_d) {
            return;
          }
          fold(n->left);
          fold(n->right);          
        }
      };
      return fold(root), self;
    }();
    
    return solution;
  }
};
