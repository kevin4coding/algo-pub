class Solution {
 public:
  vector<TreeNode*> allPossibleFBT(int N) {
    const struct {
      mutable std::optional<std::vector<TreeNode*>> f[21];
    } mempool;

    std::function<std::vector<TreeNode*>(int)> f = [&](int i) -> std::vector<TreeNode*> {
      auto & memo = mempool.f;
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i % 2 == 0) {
            return std::vector<TreeNode*>{};
          }
          else if (i == 1) {
            return std::vector<TreeNode*>{new TreeNode(0)};
          }
          else {
            return [&](std::vector<TreeNode*> self = {}) {
              for (int j = 1; j < i; j += 1) {
                for (const auto ltree : f(j)) {
                  for (const auto rtree : f(i - 1 - j)) {
                    self.emplace_back(new TreeNode{0, ltree, rtree});
                  }
                }
              }
              return self;
            }();
          }
        }());
      }
    };

    return f(N);
  }
};
