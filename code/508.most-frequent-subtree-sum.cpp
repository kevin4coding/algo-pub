class Solution {
 public:
  vector<int> findFrequentTreeSum(TreeNode* root) {
    const struct {
      mutable std::unordered_map<TreeNode*, std::optional<int>> f;
    } mempool;

    std::function<int(TreeNode*)> f = [&f, &memo = mempool.f](TreeNode* n) {
      if (memo[n].has_value()) {
        return memo[n].value();
      }
      else {
        return memo[n].emplace([&] {
          return n == nullptr ? 0 : n->val + f(n->left) + f(n->right);
        }());
      }
    };

    const auto freq_map = [&](std::unordered_map<int, int> self = {}) {
      std::function<void(TreeNode*)> fold = [&](TreeNode* n) {
        if (n == nullptr) {
          return; 
        }
        else {
          self[f(n)]++;
          fold(n->left);
          fold(n->right);
        }
      };
      return fold(root), self;
    }();

    const auto max_freq = [&](int acc = 0) {
      for (const auto [val, freq] : freq_map) {
        acc = std::max(acc, freq);
      }
      return acc;
    }();
    
    const auto solution = [&](std::vector<int> self = {}) {
      for (const auto [val, freq] : freq_map) {
        if (freq == max_freq) {
          self.emplace_back(val);
        }
      }
      return self;
    }();

      
    return solution;
  }
};
