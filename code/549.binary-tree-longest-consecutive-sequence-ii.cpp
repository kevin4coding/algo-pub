class Solution {
 public:
  int longestConsecutive(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;
    
    // increase
    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      if (mempool.f[n].has_value()) {
        return mempool.f[n].value();
      }
      else {
        return mempool.f[n].emplace([&] {
          if (n->left == nullptr and n->right == nullptr) {
            return 1;
          }
          else if (n->left == nullptr and n->right != nullptr) {
            return n->right->val == n->val + 1 ? 1 + f(n->right) : 1;
          }
          else if (n->left != nullptr and n->right == nullptr) {
            return n->left->val == n->val + 1 ? 1 + f(n->left) : 1;
          }
          else {
            return std::max({n->left->val == n->val + 1? 1 + f(n->left) : 1,
                             n->right->val == n->val + 1? 1 + f(n->right) : 1});

          }
        }());
      }
    };

    // decrease
    std::function<int(TreeNode*)> g = [&](TreeNode *n) {
      if (mempool.g[n].has_value()) {
        return mempool.g[n].value();
      }
      else {
        return mempool.g[n].emplace([&] {
          if (n->left == nullptr and n->right == nullptr) {
            return 1;
          }
          else if (n->left == nullptr and n->right != nullptr) {
            return n->right->val ==  n->val - 1? 1 + g(n->right) : 1;
          }
          else if (n->left != nullptr and n->right == nullptr) {
            return n->left->val == n->val - 1? 1 + g(n->left) : 1;
          }
          else {
            return std::max(n->right->val == n->val - 1? 1 + g(n->right) : 1,
                            n->left->val == n->val - 1? 1 + g(n->left) : 1);
          }
        }());
      }
    };

    const auto solution = [&](int acc = 0) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          acc = std::max(f(n) + g(n) - 1, acc);
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), acc;
    }();

    return solution;   
  }
};
