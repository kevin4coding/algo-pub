class Solution {
 public:
  bool btreeGameWinningMove(TreeNode* root, int n, int x) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;

    std::function<int(TreeNode*)> f = [&](TreeNode* node) {
      auto & memo = mempool.f;
      if (memo[node].has_value()) {
        return memo[node].value();
      }
      else {
        return memo[node].emplace([&] {
          if (node == nullptr) {
            return 0;
          }
          else {
            return 1 + f(node->left) + f(node->right);
          }
        }());
      }
    };

    const auto x_node = [&](TreeNode* self = nullptr) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* node) {
        if (node == nullptr or self != nullptr) {
          return;
        }
        else {
          if (node->val == x) {
            std::exchange(self, node);
          }
          fold(node->left);
          fold(node->right);
        }
      };
      return fold(root), self;
    }();

    return std::max({f(x_node->left), f(x_node->right), n - f(x_node->left) - f(x_node->right) - 1}) > n / 2;
  }
};
