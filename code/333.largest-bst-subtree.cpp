class Solution {
 public:
  int largestBSTSubtree(TreeNode* root) {
    struct tree_info_t {
      int max;
      int min;
      int size;
      bool is_bst;   
    };
    
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<tree_info_t>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;

    std::function<tree_info_t(TreeNode*)> f = [&f, &memo = mempool.f](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return tree_info_t{.max = INT_MIN, .min = INT_MAX, .size = 0, .is_bst = true};
          }
          else {
            return tree_info_t {
              .max = std::max({n->val, f(n->left).max, f(n->right).max}),
              .min = std::min({n->val, f(n->left).min, f(n->right).min}),
              .size = 1 + f(n->left).size + f(n->right).size,
              .is_bst = f(n->left).max < n->val and f(n->right).min > n->val and f(n->left).is_bst and f(n->right).is_bst
              };
          };
        }());
      };
    };

    std::function<int(TreeNode*)> g = [&g, &f, &memo = mempool.g](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return 0;
          }
          else {
            return f(n).is_bst ? f(n).size : std::max(g(n->left), g(n->right));
          }

        }());
      }
    };
    return g(root);
  }
};
