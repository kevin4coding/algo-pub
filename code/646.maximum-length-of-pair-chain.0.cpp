class Solution {
 public:
  int findLongestChain(vector<vector<int>>& pairs) {
    struct {
      mutable std::optional<int> f[1005] = {};
    } mempool;

    const int n = std::size(pairs);

    const auto sorted_pairs = [&](std::vector<std::vector<int>> self = {}) {
      std::copy(std::begin(pairs), std::end(pairs), std::back_inserter(self));
      std::sort(std::begin(self), std::end(self));
      return self;
    }();    

    std::function<int(int)> f = [&, memo = mempool.f](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else {
            return [&](int acc = 1) {
              for (int j = 0; j < i; ++j) {            
                if (sorted_pairs[j][1] < sorted_pairs[i][0]) {
                  acc = std::max(acc, 1 + f(j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    auto solve = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        acc = std::max(acc, f(i));
      }
      return acc;
    };

    return solve();
  }
};
