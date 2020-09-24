class Solution {
 public:
  vector<vector<int>> findLeaves(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;

    std::function<int(TreeNode*)> f = [&f, &memo = mempool.f](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          if (n == nullptr) {
            return -1;
          }
          else {
            return 1 + std::max(f(n->left), f(n->right));
          }
        }());
      }
    };

    const auto candidate = [&](std::unordered_map<int, std::vector<int>> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return;
        }
        else {
          self[f(n)].emplace_back(n->val);
          fold(n->left);
          fold(n->right);
        }
      };

      return fold(root), self;
    }();

    const auto solution = [&](std::vector<std::vector<int>> self = {}) {
      self.resize(std::size(candidate));
      for (const auto & [level, nodes] : candidate) {
        std::copy(std::begin(nodes), std::end(nodes), std::back_inserter(self[level]));
      }
      return self;
    }();

    return solution;
  }
};
