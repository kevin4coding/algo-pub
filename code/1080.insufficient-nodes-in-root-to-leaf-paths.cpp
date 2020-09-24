class Solution {
 public:
  TreeNode* sufficientSubset(TreeNode* root, int limit) {
    struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;
    
    const auto g = [&](std::unordered_map<TreeNode*, int> self = {}) {
      std::function<void(TreeNode*, int)> fold = [&](TreeNode* n, int acc) {
        if (n == nullptr) {
          return;
        }
        else {
          self[n] = acc;
          fold(n->left, acc + n->val);
          fold(n->right, acc + n->val);
        }
      };
      return fold(root, 0), self;
    }();

    std::function<int(TreeNode*)> f = [&](TreeNode* n) {
      auto& memo = mempool.f;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return INT_MIN;
          }
          else if (n->left == nullptr and n->right == nullptr) {
            return n->val;
          }
          else {
            return n->val + std::max(f(n->left), f(n->right));
          }
        }());
      }
    };

    // not memory safe though
    std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
      if (n == nullptr) {
        return;
      }
      else {
        if (n == root and f(n) < limit)  {
          root = nullptr;
        }
        if (n->left and g.at(n->left) + f(n->left) < limit) {
          n->left = nullptr;
        }
        if (n->right and g.at(n->right) + f(n->right) < limit) {
          n->right = nullptr;
        }
        fold(n->left);
        fold(n->right);
      }
    };

    return fold(root), root;
  }
};
