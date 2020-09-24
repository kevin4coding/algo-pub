class Solution {
 public:
  vector<TreeNode*> generateTrees(int n) {
    const struct {
      mutable std::optional<std::vector<TreeNode*>> f[10][10];
    } mempool;

    std::function<std::vector<TreeNode*>(int, int)> f = [&, memo = std::ref(mempool.f)](int i, int j) {
      if (memo[i][j].has_value()) {
        return memo[i][j].value();
      }
      else {
        return memo[i][j].emplace([&] {
          if (i > j or j < i) {
            return std::vector<TreeNode*>{nullptr};
          }
          else {
            return [&](std::vector<TreeNode*> self = {}) {
              for (int k = i; k <= j; ++k) {
                for (const auto ltree : f(i, k - 1)) {
                  for (const auto rtree : f(k + 1, j)) {
                    self.emplace_back(new TreeNode(k, ltree, rtree));
                  }
                }
              }
              return self;
            }();
          }
        }());
      }
    };

    return n == 0 ? std::vector<TreeNode*>{} : f(1, n);
  }
};
