class Solution {
 public:
  int findNumberOfLIS(vector<int>& nums) {
    struct {
      mutable std::optional<int> f[2005];
      mutable std::optional<int> g[2005];
    } mempool;

    const int n = std::size(nums);

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
                if (nums[j] < nums[i]) {
                  acc = std::max(acc, 1 + f(j));
                }
              }
              return acc;
            }();
          }
        }());
      }
    };

    std::function<int(int)> g = [&, memo = mempool.g](int i) {
      if (memo[i].has_value()) {
        return memo[i].value();
      }
      else {
        return memo[i].emplace([&] {
          if (i == 0) {
            return 1;
          }
          else {
            return [&](int acc = 0) {
              for (int j = 0; j < i; ++j) {
                if (nums[j] < nums[i] and 1 + f(j) == f(i)) {
                  acc += g(j);
                }
              }
              return acc == 0 ? 1 : acc;
            }();
          }
        }());
      }
    };

    const auto lis_size = [&](int acc = INT_MIN) {
      for (int i = 0; i < n; ++i) {
        acc = std::max(acc, f(i));
      }
      return acc;
    }();


    auto solve = [&](int acc = 0) {
      for (int i = 0; i < n; ++i) {
        if (f(i) == lis_size) {
          acc += g(i);
        }
      }
      return acc;
    };

    return solve();
  }
};
