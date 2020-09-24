class Solution {
 public:
  vector<TreeNode*> findDuplicateSubtrees(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<std::string>> h;
    } mempool;

    std::function<std::string(TreeNode*)> h = [&](TreeNode* n) {
      auto & memo = mempool.h;
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return std::string{"null"};
          }
          else {
            return std::to_string(n->val) + ", " + h(n->left) + ", " +  h(n->right);
          }
        }());
      }
    };

    const auto freq_map = [&](std::unordered_map<std::string, std::vector<TreeNode*>> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          self[h(n)].emplace_back(n);
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    const auto solution = [&](std::vector<TreeNode*> self = {}) {
      for (const auto [h, nodes] : freq_map) {
        if (std::size(nodes) > 1) {
          std::copy(std::begin(nodes), std::begin(nodes) + 1, std::back_inserter(self));
        }
      }
      return self;
    }();
    
    return solution;
  }
};
