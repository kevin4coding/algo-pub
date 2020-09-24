class Solution {
 public:
  TreeNode* subtreeWithAllDeepest(TreeNode* root) {
      
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
      mutable std::unordered_map<TreeNode*, std::optional<int>> g;
    } mempool;

    const auto parent = [&](std::unordered_map<TreeNode*, TreeNode*> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          if (n->left != nullptr) {
            std::exchange(self[n->left], n);
          }
          if (n->right != nullptr) {
            std::exchange(self[n->right], n);
          }
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();
    
    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      auto & memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == root) {
            return 0;
          }
          else {
            return 1 + f(parent.at(n));
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
            return INT_MIN;
          }
          else {
            return std::max({f(n), g(n->left), g(n->right)});
          }
        }());
      }
    };

    const auto solution = [&](TreeNode* self = nullptr) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr or self != nullptr) {
          return;
        }
        else {
          if (n->left != nullptr and n->right != nullptr and g(n->left) == g(root) and g(n->right) == g(root)) {
            std::exchange(self, n);
          }
          else if (n->left != nullptr and g(n->left) == g(root)) {
            fold(n->left);
          }
          else if (n->right != nullptr and g(n->right) == g(root)) {
            fold(n->right);
          }
          else if (n->right == nullptr and n->left == nullptr and g(n) == g(root)) {
            std::exchange(self, n);
          }
        }
      };
      return fold(root), self;
    }();

    return solution;    
  }
};
